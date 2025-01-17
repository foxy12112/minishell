/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:17 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/17 10:43:09 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_dup(t_env_list *head, char *key)
{
	t_env_list	*current;

	current = head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

static int	add_variable_ex(t_shell_data *shell, char **variables)
{
	int		i;
	char	**key_value;

	i = 1;
	while (variables[i])
	{
		key_value = ft_split_by_first_equal(variables[i]);
		if (is_dup(shell->variables, key_value[0]))
			ft_unset(shell, key_value[0]);
		if (!is_dup(shell->variables, key_value[0]))
		{
			add_to_variables_list(&shell->env, key_value);
			add_to_variables_list(&shell->variables, key_value);
		}
		free_string_array(key_value);
		i++;
	}
	return (0);
}

int	ft_export(t_shell_data *shell, char **variables)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (variables[i])
	{
		i++;
	}
	if (i < 2)
	{
		sort_env_list(shell->variables);
		exit_code = print_variables_list(shell->variables);
	}
	else
	{
		exit_code = add_variable_ex(shell, variables);
		sort_env_list(shell->variables);
	}
	return (exit_code);
}

int	parse_launch_export(t_shell_data *shell, char **command)
{
	int	exit_code;

	exit_code = ft_export(shell, command);
	return (exit_code);
}
