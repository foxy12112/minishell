/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:02:13 by macbook           #+#    #+#             */
/*   Updated: 2025/01/14 16:04:16 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_delimiter(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

void	ft_toggle_quotes(char *arr, bool *in_single_quotes,
		bool *in_double_quotes)
{
	if (arr == NULL || *arr == '\0')
		return ;
	if (arr[0] == '\'' && !*in_double_quotes)
		*in_single_quotes = !*in_single_quotes;
	if (arr[0] == '\"' && !*in_single_quotes)
		*in_double_quotes = !*in_double_quotes;
}

void	expand_single_arg(t_shell_data *shell, char **args_ar)
{
	int		i;
	bool	in_single_quotes;
	bool	in_double_quotes;
	char	*expanded;

	in_single_quotes = false;
	in_double_quotes = false;
	i = 0;
	while (args_ar[i])
	{
		ft_toggle_quotes(args_ar[i], &in_single_quotes, &in_double_quotes);
		if (args_ar[i][0] == '$' && !in_single_quotes)
		{
			expanded = get_variable_value(shell, args_ar[i]);
			free(args_ar[i]);
			args_ar[i] = NULL;
			if (expanded)
				args_ar[i] = ft_strdup(expanded);
			else
				args_ar[i] = ft_strdup("");
		}
		i++;
	}
}

void	remove_quotes(char **args)
{
	bool	in_single_quotes;
	bool	in_double_quotes;
	int		i;

	in_single_quotes = false;
	in_double_quotes = false;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			args[i][0] = '\0';
		}
		else if (args[i][0] == '\"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			args[i][0] = '\0';
		}
		i++;
	}
}

// void	remove_extra_quotes(char ***arr)
// {
// 	int		i;
// 	char	**splited_args;

// 	i = 0;
// 	while ((*arr)[i] != NULL)
// 	{
// 		splited_args = ft_split_delimiters((*arr)[i], &is_delimiter);
// 		remove_quotes(splited_args);
// 		(*arr)[i] = join_subarrays(splited_args);
// 		i++;
// 	}
// }

void remove_extra_quotes(char ***arr)
{
    int i;
    char **splitted_commands;
    char **array;

    array = *arr;
    i = 0;
    while (array[i] != NULL)
    {
        splitted_commands = ft_split_delimiters(array[i], &is_delimiter);
        remove_quotes(splitted_commands);
        array[i] = join_subarrays(splitted_commands);
		free_string_array(splitted_commands);
        i++;
    }
}

char	**expand_command(t_shell_data *shell, char **commands_array)
{
	char **splitted_commands;
	int arr_length;
	int i;

	i = 0;
	arr_length = 0;
	while (commands_array[arr_length])
		arr_length++;
	while (commands_array[i])
	{
		splitted_commands = ft_split_delimiters(commands_array[i], &is_delimiter);
		expand_single_arg(shell, splitted_commands);
		free(commands_array[i]);
		commands_array[i] = join_subarrays(splitted_commands);
		free_string_array(splitted_commands);
		i++;
	}
	remove_extra_quotes(&commands_array);
	return (commands_array);
}