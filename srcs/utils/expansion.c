/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:05:10 by ldick             #+#    #+#             */
/*   Updated: 2024/12/26 17:29:55 by ldick            ###   ########.fr       */
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

void	insert_word(char *original, char *word, int pos, char *result)
{
	int	origin_len;
	int	word_len;

	origin_len = ft_strlen(original);
	if (word == NULL)
		word = "";
	word_len = ft_strlen(word);
	ft_strncpy(result, original, pos);
	result[pos] = '\0';
	ft_strcat(result, word);
	result[pos + word_len] = '\0';
}

// static int	var_double_quotes(const char *str, int dollar_pos)
// {
// 	int	i;
// 	int	double_quote_count;
// 	int	single_quote_count;

// 	i = 0;
// 	double_quote_count = 0;
// 	single_quote_count = 0;
// 	while (i < dollar_pos)
// 	{
// 		if (str[i] == '"' && single_quote_count % 2 == 0)
// 			double_quote_count++;
// 		else if (str[i] == '\'' && double_quote_count % 2 == 0)
// 			single_quote_count++;
// 		i++;
// 	}
// 	return (double_quote_count % 2 == 1);
// }

char	*replace_var_expanded(t_shell_data *shell, char *var, char *input,
		int i)
{
	char	*expanded;

	expanded = malloc((sizeof(char) * ft_strlen(input)
				+ ft_strlen(retrieve_variable(shell, var))));
	// if (!var_double_quotes(input, i))
	// 	return (expanded);
	if (ft_strcmp(var, "$?") == 0)
		insert_word(input, ft_itoa(shell->last_exit_code), i, expanded); //TODO
	else
		insert_word(input, retrieve_variable(shell, var), i, expanded);
	return (expanded);
}

char	*ft_expand_variables(t_shell_data *shell, char *input)
{
	int		i;
	int		sing_quote;
	char	var[7000];
	int		j;

	j = 0;
	i = 0;
	(void)shell;
	sing_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			sing_quote++;
		if (input[i] == '$' && sing_quote % 2 == 0)
		{
			while (!ft_is_whitespace(input[i]) && input[i] && input[i] != '"'
				&& input[i] != '\'')
			{
				var[j] = input[i];
				i++;
				j++;
			}
			var[j] = '\0';
			j = 0;
			printf("%s\n", var);
			input = replace_var_expanded(shell, var, input, i - ft_strlen(var));
			printf("%s\n", input);
			ft_bzero(var, ft_strlen(var));
		}
		i++;
	}
	return (input);
}