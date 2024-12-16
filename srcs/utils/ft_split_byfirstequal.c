/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_byfirstequal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:55:37 by macbook           #+#    #+#             */
/*   Updated: 2024/12/16 13:00:31 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*allocate_and_copy_by_first_equal(const char *s, int startindex,
		int count)
{
	char	*subarray;

	subarray = (char *)malloc(sizeof(char) * (count + 1));
	if (subarray == NULL)
		return (NULL);
	ft_memcpy(subarray, &s[startindex], count);
	subarray[count] = '\0';
	return (subarray);
}

char	**ft_split_by_first_equal(const char *s)
{
	char	**result;
	int		i;
	int		len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	result = (char **)malloc(sizeof(char *) * 3);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	result[0] = allocate_and_copy_by_first_equal(s, 0, i);
	if (result[0] == NULL)
	{
		free(result);
		return (NULL);
	}
	if (s[i] == '=')
		result[1] = allocate_and_copy_by_first_equal(s, i + 1, len - i - 1);
	else
		result[1] = NULL;
	result[2] = NULL;
	return (result);
}
