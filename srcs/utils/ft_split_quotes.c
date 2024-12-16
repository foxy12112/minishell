/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:14:10 by macbook           #+#    #+#             */
/*   Updated: 2024/12/16 13:14:50 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	countrows_quotes(char *src, char delimiter)
{
	int	count;
	int	inrow;
	int	i;

	count = 0;
	inrow = 0;
	i = 0;
	while (src[i] != '\0')
	{
		if (src[i] == delimiter && !quote_check(src, i))
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

char	*allocate_and_copy_quotes(char *s, int startindex, int count)
{
	char	*subarray;

	subarray = (char *)malloc(sizeof(char) * (count + 1));
	if (subarray == NULL)
		return (NULL);
	ft_memcpy(subarray, &s[startindex], count);
	subarray[count] = '\0';
	return (subarray);
}

char	**create_subar(char **parentarray, char *s, int ar_index,
		int *start_count)
{
	parentarray[ar_index] = allocate_and_copy_quotes(s, start_count[0],
			start_count[1]);
	if (parentarray[ar_index] == NULL)
		return (free_all(parentarray, ar_index));
	ar_index++;
	return (parentarray);
}

char	**str_div_logic_quotes(char **parentarray, char *s, char delimiter,
		int ar_index)
{
	int	i;
	int	start_count[2];

	i = 0;
	start_count[0] = 0;
	start_count[1] = 0;
	while (s[i] != '\0')
	{
		if (s[i] != delimiter || quote_check(s, i))
		{
			if (start_count[1] == 0)
				start_count[0] = i;
			start_count[1]++;
		}
		else if (start_count[1] > 0)
		{
			parentarray = create_subar(parentarray, s, ar_index, start_count);
			ar_index++;
			start_count[1] = 0;
		}
		i++;
	}
	if (start_count[1] > 0)
		parentarray = create_subar(parentarray, s, ar_index, start_count);
	return (parentarray);
}

char	**ft_split_quotes(char *s, char delimiter)
{
	char	**parentarray;
	int		ar_index;

	if (s == NULL)
	{
		return (NULL);
	}
	ar_index = 0;
	parentarray = (char **)malloc(sizeof(char *) * (countrows_quotes(s,
					delimiter) + 1));
	if (parentarray == NULL)
	{
		return (NULL);
	}
	if (str_div_logic_quotes(parentarray, s, delimiter, ar_index) == NULL)
	{
		return (NULL);
	}
	parentarray[countrows_quotes(s, delimiter)] = NULL;
	return (parentarray);
}
