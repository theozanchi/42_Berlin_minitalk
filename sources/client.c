/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:44:16 by tzanchi           #+#    #+#             */
/*   Updated: 2023/08/17 18:31:12 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_bool	argument_is_valid(int argc)
{
	if (argc != 3)
	{
		ft_printf("%s", ERR_ARG_NR);
		return (FALSE);
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	if (!argument_is_valid(argc))
		return (0);
	ft_printf("%s", argv[2]);
}
