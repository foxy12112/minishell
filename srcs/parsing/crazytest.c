/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazytest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:02:13 by macbook           #+#    #+#             */
/*   Updated: 2025/01/13 06:29:04 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_toggle_quotes(char *arr, bool *in_s_quotes, bool *in_d_quotes)
{
	if (arr == NULL || *arr == '\0')
		return ;
	if (arr[0] == '\'' && !*in_d_quotes)
	{
		*in_s_quotes = !*in_s_quotes;
	}
	if (arr[0] == '\"' && !*in_s_quotes)
	{
		*in_d_quotes = !*in_d_quotes;
	}
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
			args_ar[i] = ft_strdup(expanded);
		}
		i++;
	}
}

char	*arofars_join(char **arr)
{
	int		total_length;
	char	**temp;
	char	*result;

	if (arr == NULL)
		return (NULL);
	total_length = 1;
	temp = arr;
	while (*temp)
		total_length += ft_strlen(*temp++);
	result = (char *)malloc(total_length);
	if (result == NULL)
		return (NULL);
	*result = '\0';
	temp = arr;
	while (*temp)
		ft_strlcat(result, *temp++, total_length);
	if (total_length)
		free_string_array(arr);
	return (result);
}

void	remove_quotes(char **arr)
{
	bool	in_s_quotes;
	bool	in_d_quotes;
	int		i;

	in_s_quotes = false;
	in_d_quotes = false;
	i = 0;
	while (arr[i])
	{
		if (arr[i][0] == '\'' && !in_d_quotes)
		{
			in_s_quotes = !in_s_quotes;
			arr[i][0] = '\0';
		}
		else if (arr[i][0] == '\"' && !in_s_quotes)
		{
			in_d_quotes = !in_d_quotes;
			arr[i][0] = '\0';
		}
		i++;
	}
}

void	remove_extra_quotes(char ***arr)
{
	int		i;
	char	**splited_args;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		splited_args = ft_split_delimiters((*arr)[i], &is_delimiter);
		//splited_args = ft_split_multidelimiter((*arr)[i], &is_delimiter1);
		remove_quotes(splited_args);
		(*arr)[i] = arofars_join(splited_args);
		i++;
	}
}

char	**expand_arguments_in_ar(t_shell_data *shell, char **arr)
{
	char **splited_args;
	int arr_size;
	int i;

	i = 0;
	arr_size = 0;
	while (arr[arr_size])
		arr_size++;
	while (arr[i])
	{
		splited_args = ft_split_delimiters(arr[i], &is_delimiter);
		//splited_args = ft_split_multidelimiter(arr[i], &is_delimiter1);
		expand_single_arg(shell, splited_args);
		free(arr[i]);
		arr[i] = arofars_join(splited_args);
		i++;
	}
	remove_extra_quotes(&arr);
	return (arr);
}