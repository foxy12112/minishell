/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_parse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:33:41 by macbook           #+#    #+#             */
/*   Updated: 2024/12/12 13:45:44 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool	check_key(char *key)
{
	if (string_in_doublequotes(key))
	{
		return (false);
	}
	if (string_in_singlequotes(key))
	{
		return (false);
	}
	if (!contains_valid_chars(key))
	{
		return (false);
	}
	return (true);
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
