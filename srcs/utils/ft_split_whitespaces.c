/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:28:57 by macbook           #+#    #+#             */
/*   Updated: 2024/12/16 12:10:49 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	countrows_whitespace(char const *src)
{
	int	count;
	int	inrow;
	int	i;

	count = 0;
	inrow = 0;
	i = 0;
	while (src[i] != '\0')
	{
		if (ft_is_whitespace(src[i]))
		{
			if (inrow)
			{
				count++;
				inrow = 0;
			}
		}
		else
			inrow = 1;
		i++;
	}
	if (inrow)
		count++;
	return (count);
}

char	*allocate_and_copy_whitespace(const char *s, int startindex, int count)
{
	char	*subarray;

	subarray = (char *)malloc(sizeof(char) * (count + 1));
	if (subarray == NULL)
		return (NULL);
	ft_memcpy(subarray, &s[startindex], count);
	subarray[count] = '\0';
	return (subarray);
}

char	**free_all_whitespace(char **parentarray, int arrayindex)
{
	int	j;

	j = 0;
	while (j < arrayindex)
	{
		free(parentarray[j]);
		j++;
	}
	free(parentarray);
	return (NULL);
}

char	**str_div_logic_whitespace(char **parentarray, const char *s,
		int ar_index)
{
	int	i;
	int	count;
	int	startindex;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (!ft_is_whitespace(s[i]))
		{
			startindex = i;
			while (s[i] != '\0' && !ft_is_whitespace(s[i++]))
				count++;
			parentarray[ar_index] = allocate_and_copy_whitespace(s, startindex,
					count);
			if (parentarray[ar_index++] == NULL)
				return (free_all_whitespace(parentarray, ar_index));
			count = 0;
		}
		else
			i++;
	}
	return (parentarray);
}

char	**ft_split_whitespace(char const *s)
{
	char	**parentarray;
	int		ar_index;

	if (s == NULL)
	{
		return (NULL);
	}
	ar_index = 0;
	parentarray = (char **)malloc(sizeof(char *) * (countrows_whitespace(s)
				+ 1));
	if (parentarray == NULL)
	{
		return (NULL);
	}
	if (str_div_logic_whitespace(parentarray, s, ar_index) == NULL)
	{
		return (NULL);
	}
	parentarray[countrows_whitespace(s)] = NULL;
	return (parentarray);
}
