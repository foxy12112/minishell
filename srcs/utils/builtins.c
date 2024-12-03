/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:13:40 by macbook           #+#    #+#             */
/*   Updated: 2024/12/03 23:30:59 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **args, int fd)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
		{
			ft_putchar_fd(' ', fd);
		}
		else
		{
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
	return (0);
}
