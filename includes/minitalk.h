/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:45:05 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/04 11:14:53 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <signal.h>
# include <errno.h>

/*errors*/
# define ERR_ARG_NR "Wrong number of arguments\n"
# define ERR_EMPT_STR "Empty string to send to server\n"
# define ERR_NON_NUM_PID "Process ID argument is not numeric\n"
# define ERR_MALLOC "Error while allocating memory for the str_info buffer\n"
# define TIME_OUT "Timeout: no response from the server, process interrupted\n"
# define ERR_SIGAC "Sigaction error, process interrupted\n"
# define PROTECTED_PID "Process ID is protected and should be above 1050\n"
# define KILL_FAIL "Error sending signal, process interrupted with errno %d\n"

/*constants*/
# ifndef BLOCK_SIZE
#  define BLOCK_SIZE 64
# endif

/*colours*/
# define RED_BOLD "\033[1;31m"
# define GREEN_LIGHT "\033[0;32m"
# define YELLOW_BOLD "\033[1;33m"

/*data_model*/
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_type
{
	MESSAGE_LENGTH,
	MESSAGE
}	t_type;

/*common_utils*/
void	send_signal(pid_t pid, int signum);

#endif
