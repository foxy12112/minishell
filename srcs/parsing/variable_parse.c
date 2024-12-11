/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 03:32:40 by macbook           #+#    #+#             */
/*   Updated: 2024/12/11 19:22:18 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

bool	string_in_quotes(char *value)
{
	int	last_index;

	last_index = ft_strlen(value) - 1;
	if (value[0] == '\'' || value[0] == '\"')
	{
		if (value[last_index] == '\'' || value[last_index] == '\"')
		{
			return (true);
		}
	}
	return (false);
}

bool	string_in_singlequotes(char *value)
{
	int	last_index;

	last_index = ft_strlen(value) - 1;
	if (value[0] == '\'')
	{
		if (value[last_index] == '\'')
		{
			return (true);
		}
	}
	return (false);
}

bool	string_in_doublequotes(char *value)
{
	int	last_index;

	last_index = ft_strlen(value) - 1;
	if (value[0] == '\"')
	{
		if (value[last_index] == '\"')
		{
			return (true);
		}
	}
	return (false);
}

bool	contains_valid_chars(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (false);
	if (!(('a' <= str[0] && str[0] <= 'z') || ('A' <= str[0] && str[0] <= 'Z')
			|| (str[0] == '_')))
	{
		return (false);
	}
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

// not in quotes

bool	is_valid_char(char c, char *invalid_chars)
{
	int	i;

	i = 0;
	while (invalid_chars[i] != '\0')
	{
		if (c == invalid_chars[i])
		{
			return (false);
		}
		i++;
	}
	return (true);
}

char	*remove_quotes(char *value)
{
	char	*parsed;
	int		size;
	int		i;
	int		j;

	i = 1;
	j = 0;
	size = ft_strlen(value);
	if (size == 2)
		return (ft_strdup(""));
	parsed = (char *)malloc(sizeof(char) * (size - 1));
	if (!parsed)
		return (NULL);
	while (value[i + 1])
	{
		parsed[j] = value[i];
		i++;
		j++;
	}
	return (parsed);
}

bool	check_for_doublequotes(char *value)
{
	int		i;
	char	*value_to_check;

	i = 0;
	value_to_check = remove_quotes(value);
	if (!value_to_check)
		return (NULL);
	while (value_to_check[i])
	{
		if ((value_to_check[i - 1] != '\'' && !is_valid_char(value_to_check[i],
				"\"'`")) || (i == 0 && value_to_check[i - 1] != '\''
				&& !is_valid_char(value_to_check[i], "\"'`")))
			return (false);
		if ((value[i - 1] != '\'' && !is_valid_char(value[i], "|&;<(>)!")
				&& (!ft_is_whitespace(value[i + 1]) || value[i + 1] != '\0'))
				|| ((i == 0 && value[i - 1] != '\'' && !is_valid_char(value[i],
					"|&;<(>)!")) && (!ft_is_whitespace(value[i + 1]) || value[i
				+ 1] != '\0')))
			return (false);
		i++;
	}
	free(value_to_check);
	return (true);
}

bool	check_for_no_quotes(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if ((value[i - 1] != '\'' && !is_valid_char(value[i], "|&;<(>)!\"'`"))
				|| (i == 0 && value[i - 1] != '\'' && !is_valid_char(value[i],
				"|&;<(>)!\"'`")))
			return (false);
		if ((value[i - 1] != '\'' && ft_is_whitespace(value[i])) || (i == 0
				&& ft_is_whitespace(value[i])))
			return (false);
		i++;
	}
	return (true);
}

bool	check_key(char *key)
{
	if (string_in_quotes(key))
	{
		return (false);
	}
	if (!contains_valid_chars(key))
	{
		return (false);
	}
	return (true);
}

char	*retrieve_key_value(t_shell_data *shell, char *value, int i)
{
	int		start;
	int		end;
	char	*key;
	char	*variable;

	start = i;
	end = i;
	while (value[end] && !ft_is_whitespace(value[end]))
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

int	get_current_key_size(char *value, int i)
{
	int	size;

	size = i;
	while (value[size])
	{
		if (ft_is_whitespace(value[size]))
		{
			break ;
		}
		size++;
	}
	return (size - i);
}
// char	*check_value_for_var(t_shell_data *shell, char *value)
// {
// 	int		i;

// 	i = 0;
// 	while (value[i])
// 	{
// 		if (value[i - 1] != '\'' && value[i] == '$')
// 		{
//             printf("Var Value: %s\n", retrieve_key_value(shell, value, i));
// 		}
// 		i++;
// 	}
//     return (NULL);
// }

int	count_memory_for_value(t_shell_data *shell, char *value)
{
	int		i;
	int		j;
	int		var_memory;
	int		in_var;
	char	*var_value;

	i = 0;
	j = 0;
	in_var = 0;
	var_memory = 0;
	var_value = NULL;
	while (value[i])
	{
		if ((i > 0 && value[i - 1] != '\'' && value[i] == '$') || (i == 0
				&& value[i] == '$'))
		{
			var_value = retrieve_key_value(shell, value, i);
			var_memory = var_memory + ft_strlen(var_value);
			in_var = 1;
		}
		if (ft_is_whitespace(value[i]))
		{
			in_var = 0;
		}
		if (in_var)
		{
			j++;
		}
		i++;
	}
	return (i - j + var_memory);
}

char	*parse_value(t_shell_data *shell, char *value)
{
	int		i;
	int		j;
	int		k;
	char	*var_value;
	char	*parsed_variable;

	i = 0;
	var_value = NULL;
	j = count_memory_for_value(shell, value);
	parsed_variable = (char *)malloc(sizeof(char) * (j + 1));
	if (!parsed_variable)
		return (NULL);
	j = 0;
	k = 0;
	while (value[i])
	{
		if ((i > 0 && value[i - 1] != '\'' && value[i] == '$') || (i == 0
				&& value[i] == '$'))
		{
			k = 0;
			var_value = retrieve_key_value(shell, value, i);
			i = i + get_current_key_size(value, i);
			while (var_value && var_value[k])
			{
				parsed_variable[j++] = var_value[k++];
			}
		}
		parsed_variable[j++] = value[i++];
	}
	parsed_variable[j] = '\0';
	return (parsed_variable);
}

bool	check_value(char *value)
{
	if (string_in_singlequotes(value))
		return (true);
	else if (string_in_doublequotes(value))
		return (check_for_doublequotes(value));
	else
		return (check_for_no_quotes(value));
}

char *join_key_value(char *key, char *value)
{
    int i;
    int j;
    char *joined;

    i = 0;
    j = 0;
    while(key[i])
        i++;
    while(value[j])
        j++;
    joined = (char *)malloc(sizeof(char)*(i + j + 2));
    if(!joined)
        return (NULL);
    i = 0;
    j = 0;
    while(key[i])
    {
        joined[i] = key[i];
        i++;
    }
    joined[i] = '=';
    i++;
    while(value[j])
    {
        joined[i] = value[j];
        i++;
        j++;
    }
    joined[i] = '\0';
    return (joined);
}

char	*parse_variable(t_shell_data *shell, char *variable)
{
	char **key_value;
	// char *parsed;
	char *value;
	char *var_with_no_quotes;

	key_value = ft_split_by_first_equal(variable);
	if (!key_value)
		return (false);

	if (!check_key(key_value[0]) || !check_value(key_value[1]))
	{
		perror("Invalid KeyValue\n");
		return (NULL);
	}
	// printf("TES: %d\n", check_key(key_value[0]));
	// printf("VAL: %d\n", check_value(key_value[1]));
	// value_to_check = remove_quotes(value);
	var_with_no_quotes = remove_quotes(key_value[1]);
	if (string_in_quotes(key_value[1]))
		value = parse_value(shell, var_with_no_quotes);
	else
		value = parse_value(shell, key_value[1]);
	printf("%s\n", join_key_value(key_value[0], value));
	free(key_value[0]);
	free(key_value[1]);
	free(var_with_no_quotes);
	free(key_value);
	free(value);
	return (NULL);
}