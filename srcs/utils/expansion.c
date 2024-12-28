/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:05:10 by ldick             #+#    #+#             */
/*   Updated: 2024/12/28 20:09:41 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quotes(char *input)
{
	int	i;
	int	sing;
	int	doub;

	i = 0;
	sing = 0;
	doub = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			sing++;
		if (input[i] == '\"')
			doub++;
		i++;
	}
	if (sing % 2 != 0 || doub % 2 != 0)
		return (true);
	return (false);
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
	if (ft_strcmp(var, "$?") == 0)
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
	result = malloc(ft_strlen(input) - (end - start) + ft_strlen(expanded) + 1);
	ft_strncpy(result, input, start);
	result[start] = '\0';
	ft_strcat(result, expanded);
	ft_strcat(result, input + end);
	// expanded = NULL;
	// printf("stopped here, wtf\n");
	return (result);
}

char	*ft_expand_variables(t_shell_data *shell, char *input)
{
	int		i = 0;
	int		doub_quote = 0;
	int		var_start;
	// char	*expanded;

	if (has_posible_variables(input) == false)
		return (input);
	while (input[i])
	{
		if (input[i] == '\"')
			doub_quote = !doub_quote;
		if (input[i] == '$')
		{
			var_start = i;
			while (input[i] && !ft_is_whitespace(input[i]) && input[i] != '\"'
				&& input[i] != '\'')
				i++;
			input = expand_variable(shell, input, var_start, i);
			// i = ft_strlen(get_variable_value(shell, input + var_start)) - 1;
		}
		i++;
	}
	return (input);
}
