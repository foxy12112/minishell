/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:18:21 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/05 18:54:17 by macbook          ###   ########.fr       */
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

	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
		return (perror("cd failed"), 1);
	path = getcwd(NULL, 0);
	if (!path)
		return (perror("cd failed"), 1);
	change_pwd_env(&shell->variables, "OLD_PWD", old_pwd);
	change_pwd_env(&shell->variables, "PWD", path);
	change_pwd_env(&shell->env, "OLD_PWD", old_pwd);
	change_pwd_env(&shell->env, "PWD", path);
	free(path);
	free(old_pwd);
	return (0);
}

int	parse_launch_cd(t_shell_data *shell, char **command)
{
	int		args_count;
	int		exit_code;
	char	*parsed_path;

	args_count = 0;
	exit_code = 0;
	while (command[args_count])
		args_count++;
	if (args_count > 2)
	{
		perror("Too many arguments");
		return (1);
	}
	if (string_in_doublequotes(command[1])
		|| string_in_singlequotes(command[1]))
		parsed_path = remove_quotes(command[1]);
	else
		parsed_path = ft_strdup(command[1]);
	exit_code = fd_cd(shell, parsed_path);
	free(parsed_path);
	return (exit_code);
}
