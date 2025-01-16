/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:20 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/16 21:06:11 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(int fd)
{
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
	(void)command;
	shell->last_exit_code = ft_pwd(1);
	return (0);
}
