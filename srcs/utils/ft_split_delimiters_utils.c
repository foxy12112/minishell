/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delimiters_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:46:44 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/16 20:52:26 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*process_delimiter(const char *s, int *i, char **parentarray,
		int *ar_index)
{
	parentarray[*ar_index] = allocate_and_copy_delimiters(s, *i, 1);
	if (parentarray[*ar_index] == NULL)
		return (*free_all_delimiters(parentarray, *ar_index));
	(*ar_index)++;
	(*i)++;
	return (NULL);
}

char	*process_dollar(const char *s, int *i, char **parentarray,
		int *ar_index)
{
	int	startindex;
	int	count;

	startindex = *i;
	(*i)++;
	while (s[*i] != '\0' && s[*i] != '$' && !is_delimiter(s[*i]))
		(*i)++;
	count = *i - startindex;
	parentarray[*ar_index] = allocate_and_copy_delimiters(s, startindex, count);
	if (parentarray[*ar_index] == NULL)
		return (*free_all_delimiters(parentarray, *ar_index));
	(*ar_index)++;
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

char	*process_regular(const char *s, int *i, char **parentarray,
		int *ar_index)
{
	int	startindex;
	int	count;

	startindex = *i;
	while (s[*i] != '\0' && s[*i] != '$' && !is_delimiter(s[*i]))
		(*i)++;
	count = *i - startindex;
	parentarray[*ar_index] = allocate_and_copy_delimiters(s, startindex, count);
	if (parentarray[*ar_index] == NULL)
		return (*free_all_delimiters(parentarray, *ar_index));
	(*ar_index)++;
	return (NULL);
}
