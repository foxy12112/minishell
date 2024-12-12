/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:26:29 by macbook           #+#    #+#             */
/*   Updated: 2024/12/12 11:29:03 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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