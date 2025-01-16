/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:17:23 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/16 01:19:33 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*retrieve_variable(t_shell_data *shell, char *key)
{
	t_env_list	*variables;
	char		*key_parsed;
	char		*var_value;

	variables = shell->variables;
	if (key[0] == '$')
		key_parsed = key + 1;
	else
		key_parsed = NULL;
	while (variables)
	{
		if (ft_strcmp(variables->key, key_parsed) == 0)
		{
			var_value = ft_strdup(variables->value);
			return (var_value);
		}
		variables = variables->next;
	}
	return (NULL);
}

int	add_variables(t_shell_data *shell, char **variables)
{
	int		i;
	char	**key_value;

	i = 1;
	while (variables[i])
	{
		key_value = ft_split_by_first_equal(variables[i]);
		add_to_variables_list(&shell->env, key_value);
		add_to_variables_list(&shell->variables, key_value);
		free_string_array(key_value);
		i++;
	}
	return (0);
}

char	*get_variable_value(t_shell_data *shell, char *var)
{
	if (ft_strncmp(var, "$?", 2) == 0)
		return (ft_itoa(shell->last_exit_code));
	return (retrieve_variable(shell, var));
}
