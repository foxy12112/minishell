/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:17:23 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/19 19:56:32 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*retrieve_variable(t_shell_data *shell, char *key)
{
	t_env_list	*variables;
	char		*key_parsed;

	variables = shell->variables;
	if (key[0] == '$')
		key_parsed = key + 1;
	else
		key_parsed = key;
	while (variables)
	{
		if (ft_strcmp(variables->key, key_parsed) == 0)
		{
			return (variables->value);
		}
		variables = variables->next;
	}
	return (NULL);
}

int	add_variables(t_shell_data *shell, char **variables)
{
	int		i;
	char	**key_value;

	i = 0;
	(void)shell;
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
