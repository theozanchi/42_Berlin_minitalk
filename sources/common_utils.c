/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:40:15 by tzanchi           #+#    #+#             */
/*   Updated: 2023/08/30 11:51:54 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*Sends the signal 'signu;' to the process whith ID 'PID' and prints the errno
and exits the process in case of failure of kill() function*/
void	send_signal(pid_t pid, int signum)
{
	if (kill(pid, signum) == -1)
	{
		ft_printf_colour(RED_BOLD, KILL_FAIL, errno);
		exit (EXIT_FAILURE);
	}
}
