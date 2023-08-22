/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:44:16 by tzanchi           #+#    #+#             */
/*   Updated: 2023/08/22 18:52:46 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*Checks that the arguments of the program are valid:
• Two arguments to the 'client' program
• First argument is numeric (PID of the 'server')
• Second argument is a not empty string*/
t_bool	argument_is_valid(int argc, char **argv)
{
	int	i;

	if (argc != 3)
	{
		ft_printf("%s", ERR_ARG_NR);
		return (FALSE);
	}
	i = 0;
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i++]))
		{
			ft_printf("%s", ERR_NON_NUM_PID);
			return (FALSE);
		}
	}
	if (!ft_strlen(argv[2]))
	{
		ft_printf("%s", ERR_EMPT_STR);
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
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

void	handle_sigusr(int signum)
{
	if (signum == SIGUSR1)
	{
		ft_printf("\033[0;32m");
		ft_printf("Message has been received by server");
		ft_printf("\033[0m");
	}
}

/*Checks that the program arguments are valids and sends message to the server*/
int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (!argument_is_valid(argc, argv))
		return (1);
	sa.sa_handler = handle_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	send_message(ft_atoi(argv[1]), argv[2]);
	usleep(100);
	return (0);
}
