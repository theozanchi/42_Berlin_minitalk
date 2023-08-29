/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:44:16 by tzanchi           #+#    #+#             */
/*   Updated: 2023/08/29 14:25:51 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

/*Waits for a acknowledgment rom the server before processing the next signal.
If no acknowledgment has been received after one second, '\1' is sent to the
server so that server resources are properly freed and the server can receive a
new message*/
void	wait_for_server_ack(int pid)
{
	int	timeout;
	int	i;

	timeout = 0;
	while (!g_ack_received)
	{
		usleep(100);
		if (++timeout > 10000)
		{
			i = 0;
			while (i--)
			{
				if ('\1' >> i & 1)
					kill(pid, SIGUSR2);
				else
					kill(pid, SIGUSR1);
				usleep(100);
			}
			exit(ft_printf_colour(RED_BOLD, TIME_OUT));
		}
	}
}

/*Checks that the arguments of the program are valid:
• Two arguments to the 'client' program
• First argument is numeric (PID of the 'server')
• Second argument is a not empty string*/
t_bool	argument_is_valid(int argc, char **argv)
{
	int	i;

	if (argc != 3)
	{
		ft_printf_colour(RED_BOLD, ERR_ARG_NR);
		return (FALSE);
	}
	i = 0;
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i++]))
		{
			ft_printf_colour(RED_BOLD, ERR_NON_NUM_PID);
			return (FALSE);
		}
	}
	if (ft_atoi(argv[1]) < 1050)
	{
		ft_printf_colour(RED_BOLD, PROTECTED_PID);
		return (FALSE);
	}
	if (!ft_strlen(argv[2]))
	{
		ft_printf_colour(RED_BOLD, ERR_EMPT_STR);
		return (FALSE);
	}
	return (TRUE);
}

/*Sends a bit encoded message to the server whose PID is 'pid' with SIGUSR1 to
represent 0 and SIGUSR2 to represent 1
Once the message is sent, 11111111 (bit representation of the NULL terminator) is
sent to the server to indicate message is over*/
void	send_message(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			g_ack_received = 0;
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			wait_for_server_ack(pid);
		}
	}
	i = 8;
	while (i--)
	{
		g_ack_received = 0;
		kill(pid, SIGUSR1);
		wait_for_server_ack(pid);
	}
}

/*Displays a message from the client side to assess that the server did
receive the message properly*/
void	handle_sigusr_client(int signum)
{
	static int	bit_count = 0;

	if (signum == SIGUSR1)
	{
		bit_count++;
		g_ack_received = 1;
	}
	if (signum == SIGUSR2)
		ft_printf_colour(GREEN_LIGHT,
			"Done, %d characters received by server", bit_count / 8);
}

/*Checks that the program arguments are valids and sends message to the server.
Expects a signal from the server once the message has been received*/
int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (!argument_is_valid(argc, argv))
		return (1);
	sa.sa_handler = handle_sigusr_client;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf(RED_BOLD, ERR_SIGAC);
		return (1);
	}
	send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
