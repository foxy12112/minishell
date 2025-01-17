/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:23 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/17 15:21:38 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "builtins.h"

int	delete_node_by_key(t_env_list **head, const char *key)
{
	t_env_list	*current;

	if (!head || !*head || !key)
		return (1);
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
			return (0);
		}
		current = current->next;
	}
	return (0);
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
	int	exit_code;

	if (!valid_key(key))
	{
		exit_code = handle_invalid_env_key(key);
	}
	else
	{
		exit_code = delete_node_by_key(&shell->variables, key);
		exit_code = delete_node_by_key(&shell->env, key);
	}
	return (exit_code);
}

int	parse_launch_unset(t_shell_data *shell, char **command)
{
	int	args_count;

	args_count = 0;
	while (command[args_count])
		args_count++;
	if (args_count < 2)
	{
		return (1);
	}
	args_count = 1;
	while (command[args_count])
	{
		shell->last_exit_code = ft_unset(shell, command[args_count]);
		args_count++;
	}
	return (shell->last_exit_code);
}
