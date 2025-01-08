/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:18:21 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/08 18:05:15 by ldick            ###   ########.fr       */
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
static char	*get_home(char *path)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (NULL);
	if (path == NULL)
		return (ft_strdup(home));
	else if (ft_strncmp(path, "~", 1) == 0)
		return (ft_strjoin(home, path + 1));
	return (ft_strdup(path));
}

int	fd_cd(t_shell_data *shell, char *path)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	path = get_home(path);
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

	args_count = 0;
	exit_code = 0;
	while (command[args_count])
		args_count++;
	if (args_count > 2)
	{
		perror("Too many arguments");
		return (1);
	}
	exit_code = fd_cd(shell, command[1]);
	return (exit_code);
}
