/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:13:40 by macbook           #+#    #+#             */
/*   Updated: 2024/12/05 16:47:38 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	fd_cd(char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd failed");
		return (-1);
	}
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("cd failed");
		return (-1);
	}
	// printf("%s\n", path);
	// printf("%s\n", getenv("PATH"));
	return (0);
}

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

int	add_variables(t_shell_data *shell, char **variables)
{
	int	i;

	i = 0;
	while (variables[i])
	{
		add_to_variables_list(&shell->env, ft_split(variables[i], '='));
		add_to_variables_list(&shell->variables, ft_split(variables[i], '='));
		i++;
	}
	return (0);
}

int	ft_export(t_shell_data *shell, char **variables)
{
	int i;

	i = 0;
	while (variables[i])
	{
		i++;
	}
	if (i < 1)
	{
		print_variables_list(shell->variables);
	}
	else
	{
		add_variables(shell, variables);
	}
	return (0);
}