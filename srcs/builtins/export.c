/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:17 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/16 15:04:46 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_variables(t_shell_data *shell, char **variables)
{
	int		i;
	char	**key_value;

	i = 1;
	while (variables[i])
	{
		key_value = ft_split_by_first_equal(variables[i]);
		if(!valid_key(key_value[0]))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(key_value[0], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			shell->last_exit_code = 1;
			return (shell->last_exit_code);
		}
		add_to_variables_list(&shell->env, key_value);
		add_to_variables_list(&shell->variables, key_value);
		free_string_array(key_value);
		i++;
	}
	shell->last_exit_code = 0;
	return (shell->last_exit_code);
}

void	swap_nodes(t_env_list *a, t_env_list *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	sort_env_list(t_env_list *head)
{
	int			swapped;
	t_env_list	*ptr1;
	t_env_list	*ptr2;

	ptr2 = NULL;
	if (head == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != ptr2)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		ptr2 = ptr1;
	}
}

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

static char	*remove_after_equal(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(str);
	while(tmp[i])
	{
		if (tmp[i] == '=')
			tmp[i] = '\0';
		i++;
	}
	return (tmp);
}

static int	add_variable_ex(t_shell_data *shell, char **variables)
{
	int		i;
	char	**key_value;

	i = 1;
	while (variables[i])
	{
		if (is_dup(shell->variables, remove_after_equal(variables[i])))
			ft_unset(shell, remove_after_equal(variables[i]));
		if (!is_dup(shell->variables, remove_after_equal(variables[i])))
		{
			key_value = ft_split_by_first_equal(variables[i]);
			add_to_variables_list(&shell->env, key_value);
			add_to_variables_list(&shell->variables, key_value);
			free_string_array(key_value);
		}
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
		// exit_code = export_variables(shell, variables);
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
