/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 03:32:40 by macbook           #+#    #+#             */
/*   Updated: 2024/12/16 12:36:27 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_for_no_quotes(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (ft_is_whitespace(value[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_value(char *value)
{
	if (!string_in_doublequotes(value) && !string_in_singlequotes(value))
		return (check_for_no_quotes(value));
	else
		return (true);
}

char	*join_key_value(char *key, char *value)
{
	int		i;
	int		j;
	char	*joined;

	i = 0;
	j = 0;
	while (key[i])
		i++;
	while (value[j])
		j++;
	joined = (char *)malloc(sizeof(char) * (i + j + 2));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (key[i])
	{
		joined[i] = key[i];
		i++;
	}
	joined[i++] = '=';
	while (value[j])
		joined[i++] = value[j++];
	joined[i] = '\0';
	return (joined);
}

char	*parse_variable(t_shell_data *shell, char *variable)
{
	char	**key_value;
	char	*value;
	char	*var_with_no_quotes;
	char	*parsed_key_value;

	key_value = ft_split_by_first_equal(variable);
	if (!key_value)
		return (false);
	if (!check_key(key_value[0]) || !check_value(key_value[1]))
		return (free_string_array(key_value), perror("Invalid KeyValue\n"),
			NULL);
	var_with_no_quotes = remove_quotes(key_value[1]);
	if (string_in_doublequotes(key_value[1]))
		value = parse_value(shell, var_with_no_quotes);
	else if (string_in_singlequotes(key_value[1]))
		value = ft_strdup(var_with_no_quotes);
	else
		value = parse_value(shell, key_value[1]);
	parsed_key_value = join_key_value(key_value[0], value);
	free_string_array(key_value);
	free(var_with_no_quotes);
	free(value);
	return (parsed_key_value);
}

char	*parse_string(t_shell_data *shell, char *string)
{
	char	*var_with_no_quotes;
	char	*value;

	var_with_no_quotes = remove_quotes(string);
	if (string_in_doublequotes(string))
		value = parse_value(shell, var_with_no_quotes);
	else if (string_in_singlequotes(string))
		value = ft_strdup(var_with_no_quotes);
	else
		value = parse_value(shell, string);
	if (!value)
		return (NULL);
	free(var_with_no_quotes);
	return (value);
}
