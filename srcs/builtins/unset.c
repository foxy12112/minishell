/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:23 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/14 00:03:05 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node_by_key(t_env_list **head, const char *key)
{
	t_env_list	*current;

	if (!head || !*head || !key)
		return ;
	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			if (current == *head)
				*head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		current = current->next;
	}
}

bool	valid_key(const char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	handle_invalid_env_key(char *key)
{
	int	exit_code;

	exit_code = 1;
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	if (key[0] == '-')
		exit_code = 2;
	return (exit_code);
}

int	ft_unset(t_shell_data *shell, char *key)
{
	if (!valid_key(key))
	{
		shell->last_exit_code = handle_invalid_env_key(key);
	}
	else
	{
		delete_node_by_key(&shell->variables, key);
		delete_node_by_key(&shell->env, key);
		shell->last_exit_code = 0;
	}
	return (shell->last_exit_code);
}

int	parse_launch_unset(t_shell_data *shell, char **command)
{
	int	args_count;

	args_count = 0;
	while (command[args_count])
		args_count++;
	if (args_count < 2)
	{
		perror("not enough arguments");
		return (1);
	}
	args_count = 1;
	while (command[args_count])
	{
		ft_unset(shell, command[args_count]);
		args_count++;
	}
	return (0);
}
