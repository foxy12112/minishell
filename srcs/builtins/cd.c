/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:18:21 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/15 02:41:31 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_pwd_env(t_env_list **head, const char *key, const char *value)
{
	t_env_list	*current;

	if (!head || !*head || !key)
		return ;
	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

int	fd_cd(t_shell_data *shell, char *path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		return (ft_putstr_fd("minishell: cd: ", STDERR_FILENO),
			ft_putstr_fd(path, STDERR_FILENO), perror(" "), 2);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		return (ft_putstr_fd("minishell: ", STDERR_FILENO),
			ft_putstr_fd(new_pwd, STDERR_FILENO), perror(" "), 2);
	}
	change_pwd_env(&shell->variables, "OLD_PWD", old_pwd);
	change_pwd_env(&shell->variables, "PWD", new_pwd);
	change_pwd_env(&shell->env, "OLD_PWD", old_pwd);
	change_pwd_env(&shell->env, "PWD", new_pwd);
	free(new_pwd);
	free(old_pwd);
	return (0);
}

int	parse_launch_cd(t_shell_data *shell, char **command)
{
	int		args_count;
	int		exit_code;
	char	*path;

	args_count = 0;
	exit_code = 0;
	while (command[args_count])
		args_count++;
	if (args_count < 2)
	{
		path = ft_strdup(getenv("HOME"));
	}
	else if (args_count > 2)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else
	{
		path = ft_strdup(command[1]);
	}

	exit_code = fd_cd(shell, path);
	if(path)
		free(path);
	return (exit_code);
}
