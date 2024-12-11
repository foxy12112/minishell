/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 03:32:40 by macbook           #+#    #+#             */
/*   Updated: 2024/12/11 10:14:14 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool	is_valid_char(char c)
{
	char	*invalid_chars;
	int		i;

	invalid_chars = ft_strdup("|&;<(>)!\"'`");
	if (!invalid_chars)
		return (false);
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

bool	check_value(char *value)
{
	int	i;

	i = 0;
	if (string_in_quotes(value))
	{
		return (true);
	}
	while (value[i])
	{
		if (value[i - 1] != '\'' && !is_valid_char(value[i]))
		{
			return (false);
		}
		if (value[i - 1] != '\'' && ft_is_whitespace(value[i]))
		{
			return (false);
		}
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

bool	check_valid_variable(char *variable)
{
	char	**key_value;
	char	*key;
	char	*value;
	bool	valid;
	// int		i;

	// i = 0;
	valid = false;
	key_value = ft_split_by_first_equal(variable);
	if (!key_value)
		return (false);
	key = key_value[0];
	value = key_value[1];
	if (check_value(value) && check_key(key))
	{
		valid = true;
	}
	// printf("Key: %s\n", key);
	// printf("Value: %s\n", value);
	free(key_value);
	free(key);
	free(value);
	return (valid);
}

// NOTE - WHEN DIVIDING KEY VALUE, ONLY FIRST = SHOULD BE SPLIT

// const	test_valid_key(void)
// {
// 	int i;
// 	i = 0;
//  VALID KEYS
// 	char *keys[] = {
// 		"VAR",
// 		"_VAR",
// 		"VAR123",
// 		"VAR_123",
// 		"__VAR__",
// 		"k",
// 		"VAR_WITH_UNDERSCORES",
// 		"VAR123VARR",
// 		"VARNAME",
// 		"_123VAR",
// 		"value",
// 		"vsa",
// 		"a",
// 	};
//  Invalid Keys
// 	char *keys[] = {
// 		"1key",
// 		"key-name",
// 		"key name",
// 		"key@value",
// 		"key!value",
// 		"#key",
// 		"key*",
// 		"#VAR",
// 		"VAR.NAME",
// 		"VAR@123",
// 		"=value",
// 		"va?as",
// 		"'asd'",
// 	};
// 	while (keys[i])
// 	{
// 		printf("Valid Key: %d\n", check_key(keys[i]));
// 		i++;
// 	}
// }