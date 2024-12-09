/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:05 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/09 03:07:56 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **args, int fd, bool n_option)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
		{
			ft_putchar_fd(' ', fd);
		}
		else if (!n_option)
		{
			ft_putchar_fd('\n', fd);
		}
		free(args[i]);
		i++;
	}
	free(args);
	return (0);
}