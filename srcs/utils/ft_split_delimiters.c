/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delimiters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 04:39:27 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/13 04:52:43 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	countrows_delimiters(char const *src, char delimiter)
{
	int	count;
	int	inrow;
	int	i;

	count = 0;
	inrow = 0;
	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == delimiter)
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

char	**free_all_delimiters(char **parentarray, int arrayindex)
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

char	*allocate_and_copy_delimiters(const char *s, int startindex, int count)
{
	char	*subarray;

	subarray = (char *)malloc(sizeof(char) * (count + 1));
	if (subarray == NULL)
		return (NULL);
	ft_memcpy(subarray, &s[startindex], count);
	subarray[count] = '\0';
	return (subarray);
}

char	**str_div_logic_delimiters(char **parentarray, const char *s, char c, int ar_index)
{
	int	i;
	int	count;
	int	startindex;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			startindex = i;
			while (s[i] != '\0' && s[i++] != c)
				count++;
			parentarray[ar_index] = allocate_and_copy_delimiters(s, startindex, count);
			if (parentarray[ar_index++] == NULL)
				return (free_all_delimiters(parentarray, ar_index));
			count = 0;
		}
		else
			i++;
	}
	return (parentarray);
}

char	**ft_split_delimiters(char const *s, char c)
{
	char	**parentarray;
	int		ar_index;

	if (s == NULL)
	{
		return (NULL);
	}
	ar_index = 0;
	parentarray = (char **)malloc(sizeof(char *) * (countrows_delimiters(s, c) + 1));
	if (parentarray == NULL)
	{
		return (NULL);
	}
	if (str_div_logic_delimiters(parentarray, s, c, ar_index) == NULL)
	{
		return (NULL);
	}
	parentarray[countrows_delimiters(s, c)] = NULL;
	return (parentarray);
}