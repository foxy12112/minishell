/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_value_get.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 07:05:53 by macbook           #+#    #+#             */
/*   Updated: 2024/12/12 13:44:52 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*retrieve_key_value(t_shell_data *shell, char *value, int i)
{
	int		start;
	char	*key;
	char	*variable;
	int		end;

	start = i;
	end = i + 1;
	while (value[end] && (ft_isalnum(value[end]) || value[end] == '_'))
	{
		end++;
	}
	key = ft_substr(value, start + 1, end - start - 1);
	if (!key)
		return (NULL);
	variable = retrieve_variable(shell, key);
	free(key);
	return (variable);
}

int	count_memory_for_value(t_shell_data *shell, char *value)
{
	int		i;
	int		j;
	int		var_memory;
	char	*var_value;

	i = 0;
	j = 0;
	var_memory = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			var_value = retrieve_key_value(shell, value, i);
			if (var_value)
				var_memory += ft_strlen(var_value);
			while (value[i + 1] && (ft_isalnum(value[i + 1]) || value[i
						+ 1] == '_'))
				i++;
		}
		else
			j++;
		i++;
	}
	return (j + var_memory);
}

char	*process_variable(t_shell_data *shell, char *value, int *indexes,
		char *parsed_variable)
{
	char	*var_value;
	int		k;

	var_value = retrieve_key_value(shell, value, indexes[0]);
	if (var_value)
	{
		k = 0;
		while (var_value[k])
			parsed_variable[(indexes[1])++] = var_value[k++];
	}
	while (value[indexes[0] + 1] && (ft_isalnum(value[indexes[0] + 1])
			|| value[indexes[0] + 1] == '_'))
		indexes[0]++;
	return (parsed_variable);
}

char	*parse_value(t_shell_data *shell, char *value)
{
	int		i;
	int		indexes[2];
	char	*parsed_variable;

	i = count_memory_for_value(shell, value);
	parsed_variable = (char *)malloc(sizeof(char) * (i + 1));
	if (!parsed_variable)
		return (NULL);
	indexes[0] = 0;
	indexes[1] = 0;
	while (value[indexes[0]])
	{
		if (value[indexes[0]] == '$')
		{
			parsed_variable = process_variable(shell, value, indexes,
					parsed_variable);
		}
		else
			parsed_variable[indexes[1]++] = value[indexes[0]];
		indexes[0]++;
	}
	parsed_variable[indexes[1]] = '\0';
	return (parsed_variable);
}
