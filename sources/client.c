/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:44:16 by tzanchi           #+#    #+#             */
/*   Updated: 2023/08/21 18:35:29 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void	send_message(int pid, char *str)
{
	int	i;

	while (*str)
	{
		i = 8;
		while (i--)
		{
			if (*str++ >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}
	}
	i = 8;
	while (i--)
	{
		if (4 >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	if (!argument_is_valid(argc, argv))
		return (1);
	send_message(ft_atoi(argv[1]), argv[2]);
}
