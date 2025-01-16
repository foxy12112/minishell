/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delimiters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 04:39:27 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/16 20:52:51 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_delimiter(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	if (c == ' ')
		return (true);
	return (false);
}

// bool	check_special_delim(char const *src, int i)
// {
// 	if (src[i] == '\0' || src[i] == ' ' || src[i] == '\'' || src[i] == '"'
// 		|| src[i] == '$')
// 	{
// 		return (true);
// 	}
// 	return (false);
// }

// int	countrows_delimiters(char const *src)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		if (src[i] == ' ' || src[i] == '\'' || src[i++] == '"')
// 			count++;
// 		else if (src[i] == '$')
// 		{
// 			count++;
// 			i++;
// 			while (check_special_delim(src, i) == false)
// 				i++;
// 		}
// 		else
// 		{
// 			count++;
// 			while (check_special_delim(src, i) == false)
// 				i++;
// 		}
// 	}
// 	return (count);
// }

int	countrows_delimiters(char const *src)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == ' ' || src[i] == '\'' || src[i] == '"')
		{
			count++;
			i++;
		}
		else
		{
			if (src[i] == '$')
				i++;
			count++;
			while (src[i] != '\0' && src[i] != ' ' && src[i] != '\''
				&& src[i] != '"' && src[i] != '$')
				i++;
		}
	}
	return (count);
}

char	**str_div_logic_delimiters(char **parentarray, const char *s,
		int ar_index)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (is_delimiter(s[i]))
		{
			if (process_delimiter(s, &i, parentarray, &ar_index) != NULL)
				return (NULL);
		}
		else if (s[i] == '$')
		{
			if (process_dollar(s, &i, parentarray, &ar_index) != NULL)
				return (NULL);
		}
		else
		{
			if (process_regular(s, &i, parentarray, &ar_index) != NULL)
				return (NULL);
		}
	}
	return (parentarray);
}

char	**ft_split_delimiters(const char *s)
{
	char	**parentarray;
	int		ar_index;

	if (s == NULL)
	{
		return (NULL);
	}
	ar_index = 0;
	parentarray = (char **)malloc(sizeof(char *) * (countrows_delimiters(s)
				+ 1));
	if (parentarray == NULL)
		return (NULL);
	if (str_div_logic_delimiters(parentarray, s, ar_index) == NULL)
		return (NULL);
	parentarray[countrows_delimiters(s)] = NULL;
	return (parentarray);
}
