/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:08:48 by macbook           #+#    #+#             */
/*   Updated: 2025/01/14 06:12:55 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_if_in_singlequotes(char *value, int start)
{
	int	end;
	int	quote_before;
	int	quote_after;

	end = start;
	quote_before = 0;
	quote_after = 0;
	while (value[end])
	{
		if (value[end] == '\'')
			quote_after++;
		end++;
	}
	while (start > -1)
	{
		if (value[start] == '\'')
			quote_before++;
		start--;
	}
	if (quote_before && quote_after && quote_before % 2 == 1)
		return (true);
	else
		return (false);
}

bool	check_if_in_doublequotes(char *value, int start)
{
	int	end;
	int	quote_before;
	int	quote_after;

	end = start;
	quote_before = 0;
	quote_after = 0;
	while (value[end])
	{
		if (value[end] == '"')
			quote_after++;
		end++;
	}
	while (start > -1)
	{
		if (value[start] == '"')
			quote_before++;
		start--;
	}
	if (quote_before && quote_after && quote_before % 2 == 1)
		return (true);
	else
		return (false);
}

bool	quote_check(char *value, int start)
{
	if (!check_if_in_doublequotes(value, start)
		&& !check_if_in_singlequotes(value, start))
	{
		return (false);
	}
	else
	{
		return (true);
	}
}

bool	string_in_singlequotes(char *value)
{
	int	last_index;

	last_index = ft_strlen(value) - 1;
	if (value[0] == '\'')
	{
		if (value[last_index] == '\'')
		{
			return (true);
		}
	}
	return (false);
}

bool	string_in_doublequotes(char *value)
{
	int	last_index;

	last_index = ft_strlen(value) - 1;
	if (value[0] == '\"')
	{
		if (value[last_index] == '\"')
		{
			return (true);
		}
	}
	return (false);
}
