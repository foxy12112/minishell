/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:05 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/15 20:00:24 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char *args, int fd, bool n_option)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putchar_fd(args[i], fd);
		i++;
	}
	if (!n_option)
	{
		ft_putchar_fd('\n', fd);
	}
	free(args);
	return (0);
}

int	parse_launch_echo(char **command)
{
	bool	has_n_option;
	char	*echo_string;

	has_n_option = false;
	if (ft_strcmp(command[1], "-n") == 0)
		has_n_option = true;
	if (has_n_option)
		echo_string = join_arof_ars(command, 2);
	else
		echo_string = join_arof_ars(command, 1);
	ft_echo(echo_string, STDOUT_FILENO, has_n_option);
	return (0);
}
