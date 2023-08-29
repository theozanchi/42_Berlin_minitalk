/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:44:26 by tzanchi           #+#    #+#             */
/*   Updated: 2023/08/29 13:05:40 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	free_resources(char **message)
{
	if (*message)
	{
		free(*message);
		*message = NULL;
	}
}

/*Adds the character 'c' at the end of the string pointed by 'str'. If 'str' is
not big enough to receive the new character, memory is reallocated to increase
the capacity of 'str' by BLOCK_SIZE
add_char_to_str ensures that 'str' is NULL terminated*/
void	add_char_to_str(char c, char **str)
{
	static int	capacity = BLOCK_SIZE;
	static int	size = 0;
	char		*new_str;

	if (!(*str))
	{
		capacity = BLOCK_SIZE;
		size = 0;
		*str = (char *)malloc(capacity * sizeof(char));
		if (!(*str))
			exit(ft_printf_colour(RED_BOLD, "%s", ERR_MALLOC));
	}
	if (size + 2 > capacity)
	{
		capacity += BLOCK_SIZE;
		new_str = (char *)malloc(capacity * sizeof(char));
		if (!new_str)
			exit(ft_printf_colour(RED_BOLD, "%s", ERR_MALLOC));
		ft_memmove(new_str, *str, size);
		free(*str);
		*str = new_str;
	}
	(*str)[size] = c;
	(*str)[++size] = '\0';
}

/*Functions checks that only SIGUSR1 and SIGUSR2 are processed by the server.
It accumulates bits received by the client in a buffer int before storing each
byte in a static char * 'message'
Once a NULL terninator is received by the client, 'message' is displayed on the
standard output and memory is properly freed*/
void	handle_sigusr_server(int signum, siginfo_t *info, void *context)
{
	static int	buffer = 0;
	static int	bits_received = 0;
	static char	*message = NULL;

	(void)context;
	if (signum == SIGINT && message)
	{
		free(message);
		message = NULL;
	}
	buffer = (buffer << 1 | (signum == SIGUSR2));
	if (++bits_received == 8)
	{
		if ((char)buffer != '\0')
			add_char_to_str((char)buffer, &message);
		else if ((char)buffer == '\1' && message)
		{
			free(message);
			message = NULL;
		}
		else
		{
			ft_printf("%s\n", message);
			free(message);
			message = NULL;
			kill(info->si_pid, SIGUSR2);
		}
		buffer = 0;
		bits_received = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

/*Displays the PID of the server once it is launched and then waits for SIGUSR1
and SIGUSR2 from the client to display the encoded message*/
int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_sigusr_server;
	ft_printf_colour(YELLOW_BOLD, "Server PID: %i\n\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
