/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:20 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/15 20:01:59 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("Pwd error");
	}
	return (0);
}

int	parse_launch_pwd(t_shell_data *shell, char **command)
{
	int	args_count;

	args_count = 0;
	(void)shell;
	while (command[args_count])
		args_count++;
	if (args_count > 1)
	{
		perror("Too many arguments");
		return (1);
	}
	ft_pwd();
	return (0);
}