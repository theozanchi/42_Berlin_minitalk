/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:45:05 by tzanchi           #+#    #+#             */
/*   Updated: 2023/08/28 16:07:48 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/libft.h"
# include <signal.h>

/*errors*/
# define ERR_ARG_NR "Wrong number of arguments\n"
# define ERR_EMPT_STR "Empty string to send to server\n"
# define ERR_NON_NUM_PID "Process ID argument is not numeric\n"
# define ERR_MALLOC "Error while allocating memory for the str_info buffer\n"
# define TIME_OUT "Timeout: no response from the server, process interrupted\n"

/*constants*/
# ifndef BLOCK_SIZE
#  define BLOCK_SIZE 2048
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

#endif 
