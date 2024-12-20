/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:26:29 by macbook           #+#    #+#             */
/*   Updated: 2024/12/20 11:52:01 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	ft_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
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

char	*ft_strtoupper(char *str)
{
	int		i;
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		new_str[i] = ft_toupper(str[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
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
