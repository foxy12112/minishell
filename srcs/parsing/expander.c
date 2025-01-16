/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:02:13 by macbook           #+#    #+#             */
/*   Updated: 2025/01/16 21:03:41 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_single_expansion(t_shell_data *shell, char **args_ar,
		bool in_double_quotes, int i)
{
	char	*expanded;

	expanded = NULL;
	if (args_ar[i][1] == '\0' && (in_double_quotes || args_ar[i + 1] == NULL))
	{
		free(args_ar[i]);
		args_ar[i] = NULL;
		args_ar[i] = ft_strdup("$");
	}
	else
	{
		expanded = get_variable_value(shell, args_ar[i]);
		free(args_ar[i]);
		args_ar[i] = NULL;
		if (expanded)
		{
			args_ar[i] = ft_strdup(expanded);
			free(expanded);
		}
		else
		{
			args_ar[i] = ft_strdup("");
		}
	}
}

void	expand_single_arg(t_shell_data *shell, char **args_ar)
{
	int		i;
	bool	in_single_quotes;
	bool	in_double_quotes;

	(void)shell;
	in_single_quotes = false;
	in_double_quotes = false;
	i = 0;
	while (args_ar[i])
	{
		select_final_qupte_type(args_ar[i], &in_single_quotes,
			&in_double_quotes);
		if (args_ar[i][0] == '$' && !in_single_quotes)
		{
			handle_single_expansion(shell, args_ar, in_double_quotes, i);
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

char	**remove_extra_quotes(char **array)
{
	int		i;
	char	**splitted_commands;
	char	**quote_removed_array;

	i = 0;
	while (array[i])
		i++;
	quote_removed_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!quote_removed_array)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		splitted_commands = ft_split_delimiters(array[i]);
		remove_quotes(splitted_commands);
		quote_removed_array[i] = join_subarrays(splitted_commands);
		free_string_array(splitted_commands);
		i++;
	}
	quote_removed_array[i] = NULL;
	return (quote_removed_array);
}

char	**expand_command(t_shell_data *shell, char **commands_array)
{
	char	**splitted_commands;
	char	**expanded_commands;
	char	**parsed_commands;
	int		arr_length;
	int		i;

	i = 0;
	arr_length = 0;
	while (commands_array[arr_length])
		arr_length++;
	expanded_commands = (char **)malloc(sizeof(char *) * (arr_length + 1));
	if (!expanded_commands)
		return (NULL);
	while (commands_array[i])
	{
		splitted_commands = ft_split_delimiters(commands_array[i]);
		expand_single_arg(shell, splitted_commands);
		expanded_commands[i] = join_subarrays(splitted_commands);
		free_string_array(splitted_commands);
		i++;
	}
	expanded_commands[i] = NULL;
	parsed_commands = remove_extra_quotes(expanded_commands);
	free_string_array(expanded_commands);
	return (parsed_commands);
}
