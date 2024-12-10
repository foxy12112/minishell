/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:17:23 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/06 03:40:18 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Function to Get variable 
char *retrieve_variable(t_shell_data *shell, char *key) {
    t_env_list *variables;

    variables = shell->variables;
    while (variables) {
        if (ft_strcmp(variables->key, key) == 0) {
            return variables->value;
        }
        variables = variables->next;
    }
    return NULL;
}

int	add_variables(t_shell_data *shell, char **variables)
{
	int		i;
	char	**key_value;

	i = 0;
	(void)shell;
	while (variables[i])
	{
		key_value = ft_split(variables[i], '=');
		add_to_variables_list(&shell->env, key_value);
		add_to_variables_list(&shell->variables, key_value);
		free_char_string(key_value);
		i++;
	}
	return (0);
}
