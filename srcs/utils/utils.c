/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:26:29 by macbook           #+#    #+#             */
/*   Updated: 2024/12/15 08:05:20 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int i;
	char *new_str;

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