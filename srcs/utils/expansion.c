/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:05:10 by ldick             #+#    #+#             */
/*   Updated: 2025/01/09 08:58:36 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static bool	has_posible_variables(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char	*get_variable_value(t_shell_data *shell, char *var)
{
	// printf("--%d--\n",ft_strncmp(var, "$?", 2));
	if (ft_strncmp(var, "$?", 2) == 0)
		return (ft_itoa(shell->last_exit_code));
	return (retrieve_variable(shell, var));
}

char	*expand_variable(t_shell_data *shell, char *input, int start, int end)
{
	char	var[7000];
	char	*expanded;
	char	*result;

	ft_strncpy(var, input + start, end - start);
	var[end - start] = '\0';
	expanded = get_variable_value(shell, var);
	// printf("expanded = %s\n", expanded);
	// if (expanded == NULL)
	// 	return(NULL);
	result = malloc(ft_strlen(input) - (end - start) + ft_strlen(expanded) + 1);
	ft_strncpy(result, input, start);
	result[start] = '\0';
	if (expanded)
	{
		ft_strcat(result, expanded);
		ft_strcat(result, input + end);
	}
	// expanded = NULL;
	return (result);
}

static int	var_counter(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*ft_expand_variables(t_shell_data *shell, char *input)
{
	int		i;
	int		var_start;
	int		pos_var;

	pos_var = var_counter(input);
	i = 0;
	var_start = 0;
	if (has_posible_variables(input) == false)
		return (input);
	while (input[i] && pos_var > 0)
	{
		if (!input[i])
			break ;
		if (input[i] == '$' && input[i + 1])
		{
			var_start = i;
			while (input[i] && !ft_is_whitespace(input[i]) && input[i] != '\"' && input[i] != '\'')
				i++;
			// printf("Var_start: %d\n", var_start);
			// printf("Index: %d\n", i);
			input = expand_variable(shell, input, var_start, i);
			// printf("Input: %s\n", input);
			pos_var--;
		}
		if (!pos_var)
			return (input);
		i++;
	}
	return (input);
}