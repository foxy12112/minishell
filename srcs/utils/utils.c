/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:26:29 by macbook           #+#    #+#             */
/*   Updated: 2025/01/16 16:35:02 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	ft_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

char	*ft_trim_whitespaces(char *str)
{
	int	start;
	int	end;

	if (!str)
		return (NULL);
	start = 0;
	while (ft_is_whitespace(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && ft_is_whitespace(str[end]))
		end--;
	str[end + 1] = '\0';
	return (ft_strdup(str + start));
}

char	*join_arof_ars(char **array, int start)
{
	char	*result;
	char	*temp;
	int		i;

	result = NULL;
	i = 0;
	while (i < start && array[i] != NULL)
		i++;
	while (array[i] != NULL)
	{
		if (result == NULL)
		{
			result = ft_strjoin("", array[i]);
		}
		else
		{
			temp = ft_strjoin(result, " ");
			free(result);
			result = ft_strjoin(temp, array[i]);
			free(temp);
		}
		i++;
	}
	return (result);
}

char	*join_subarrays(char **array)
{
	int		total_length;
	char	*result;
	char	**temp;

	total_length = 1;
	if (array == NULL)
		return (NULL);
	temp = array;
	while (*temp)
		total_length += ft_strlen(*temp++);
	result = (char *)malloc(total_length);
	if (result == NULL)
		return (NULL);
	*result = '\0';
	temp = array;
	while (*temp)
		ft_strlcat(result, *temp++, total_length);
	return (result);
}
