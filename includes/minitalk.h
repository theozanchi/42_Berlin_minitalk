/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:45:05 by tzanchi           #+#    #+#             */
/*   Updated: 2023/08/22 11:56:47 by tzanchi          ###   ########.fr       */
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

/*constants*/
# ifndef BLOCK_SIZE
#  define BLOCK_SIZE 1024
# endif

/*data_model*/
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_str_info
{
	char	*str;
	int		str_size;
	int		str_capacity;
}	t_str_info;

#endif 
