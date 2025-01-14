/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:20 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/14 02:55:20 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(int fd)
{
	// int		i;
	// char	cwd[PATH_MAX];
	// i = 0;
	// if (getcwd(cwd, sizeof(cwd)) != NULL)
	// {
	// 	while (cwd[i])
	// 	{
	// 		ft_putchar_fd(cwd[i], fd);
	// 		i++;
	// 	}
	// }
	// else
	// 	perror("Pwd error");
	// return (0);

	char	cwd[PATH_MAX];
	char	*directory;

	(void)fd;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		directory = ft_strdup(cwd);
		ft_echo(directory, STDOUT_FILENO, false);
	}
	else
	{
		perror("Pwd error");
	}
	return (0);
}

int	parse_launch_pwd(t_shell_data *shell, char **command)
{
	// int	args_count;

	// args_count = 0;
	// while (command[args_count])
	// 	args_count++;
	// if (args_count > 1)
	// {
	// 	perror("Too many arguments");
	// 	shell->last_exit_code = 1;
	// 	return (1);
	// }
	(void)command;
	shell->last_exit_code = ft_pwd(1);
	// redirect_to_terminal();
	return (0);
}

