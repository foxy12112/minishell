/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:05:10 by ldick             #+#    #+#             */
/*   Updated: 2025/01/16 08:12:01 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	select_final_qupte_type(char *arr, bool *in_single_quotes,
		bool *in_double_quotes)
{
	if (arr == NULL || *arr == '\0')
		return ;
	if (arr[0] == '\'' && !*in_double_quotes)
		*in_single_quotes = !*in_single_quotes;
	if (arr[0] == '\"' && !*in_single_quotes)
		*in_double_quotes = !*in_double_quotes;
}

void	set_quotes(char *arr, bool *in_single_quotes, bool *in_double_quotes)
{
	if (arr == NULL || *arr == '\0')
		return ;
	if (arr[0] == '\'' && !*in_double_quotes)
	{
		*in_single_quotes = !*in_single_quotes;
	}
	if (arr[0] == '\"' && !*in_single_quotes)
	{
		*in_double_quotes = !*in_double_quotes;
	}
}

bool	unclosed_quotes(char *input)
{
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;

	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	while (input[i])
	{
		set_quotes(&input[i], &in_single_quote, &in_double_quote);
		i++;
	}
	if (in_single_quote)
	{
		return (false);
	}
	if (in_double_quote)
	{
		return (false);
	}
	return (true);
}
