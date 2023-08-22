/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:44:26 by tzanchi           #+#    #+#             */
/*   Updated: 2023/08/22 12:11:19 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_str_info	str_info = {NULL, 0, 1};

void	action(int signum)
{
	static int	buffer = 0;
	static int	bits_received = 0;
	char		*new_str;

	if (signum != SIGUSR1 && signum != SIGUSR2)
		return ;
	buffer = (buffer << 1 | (signum == SIGUSR2));
	bits_received++;
	ft_printf("%s\n", bits_received);
	if (bits_received == 8)
	{
		if ((char)buffer == 4)
		{
			ft_printf("%s\n", str_info.str);
			free(str_info.str);
			str_info.str = NULL;
			str_info.str_size = 0;
			str_info.str_capacity = 1;
			return ;
		}
		if (str_info.str_capacity < str_info.str_size + 1)
		{
			str_info.str_capacity += BLOCK_SIZE;
			new_str = malloc(str_info.str_capacity * sizeof(char));
			if (!new_str)
			{
				ft_printf("%s", ERR_MALLOC);
				return ;
			}
			if (str_info.str)
			{
				ft_memmove(new_str, str_info.str, str_info.str_size);
				free(str_info.str);
			}
			str_info.str = new_str;
		}
		str_info.str[str_info.str_size] = (char)buffer;
		str_info.str_size++;
		str_info.str[++str_info.str_size] = '\0';
		buffer = 0;
		bits_received = 0;
	}
}

int	main(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_handler = action;
	s_sigaction.sa_flags = 0;
	ft_printf("Server PID: %i\n\n", getpid());
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	while (1)
		pause();
}
