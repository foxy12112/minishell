/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:18:21 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/09 03:08:35 by macbook          ###   ########.fr       */
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
		return (perror("cd failed"), -1);
	path = getcwd(NULL, 0);
	if (!path)
		return (perror("cd failed"), -1);
	change_pwd_env(&shell->variables, "OLD_PWD", old_pwd);
	change_pwd_env(&shell->variables, "PWD", path);
	change_pwd_env(&shell->env, "OLD_PWD", old_pwd);
	change_pwd_env(&shell->env, "PWD", path);
	free(path);
	free(old_pwd);
	return (0);
}
