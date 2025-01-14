/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:05 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/14 00:11:35 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char *args, int fd, bool n_option)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putchar_fd(args[i], fd);
		i++;
	}
	if (!n_option)
	{
		ft_putchar_fd('\n', fd);
	}
	free(args);
	return (0);
}

static bool	has_anything(char **command)
{
	if (!command[1])
		return (false);
	return (true);
}

// char	*true_quote_removal(char *str)
// {
// 	char	*ret;
// 	int		i;
// 	int		j;
// 	int		size;

// 	i = 0;
// 	j = 0;
// 	size = ft_strlen_s(str, '\"') + 1;
// 	ret = malloc(size + 1);
// 	if (!ret)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i] == '"' && !str[i + 1])
// 			break ;
// 		if (str[i] == '"')
// 		{
// 			i++;
// 			continue ;
// 		}
// 		ret[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	ret[j] = '\0';
// 	return (ret);
// }

char	*true_quote_removal(char *str)
{
	return (str);
}

int	parse_launch_echo(char **command)
{
	bool	has_n_option;
	char	*echo_string;
	int		prompt_start_index;

	has_n_option = false;
	prompt_start_index = 1;
	if (has_anything(command) == false)
		return (ft_putchar_fd('\n', 1), 1);
	// if (ft_strcmp(command[1], "-n") == 0)
	// 	has_n_option = true;
	while (command[prompt_start_index])
	{
		if (ft_strcmp(command[prompt_start_index], "-n") != 0)
			break ;
		has_n_option = true;
		prompt_start_index++;
	}
	if (has_n_option)
		echo_string = join_arof_ars(command, prompt_start_index);
	else
		echo_string = join_arof_ars(command, 1);
	echo_string = true_quote_removal(echo_string);
	ft_echo(echo_string, STDOUT_FILENO, has_n_option);
	return (0);
}

// int	ft_echo(char *args, bool n_option)
// {
// 	printf("%s", args);
// 	if (!n_option)
// 	{
// 		printf("\n");
// 	}
// 	free(args);
// 	return (0);
// }

// static bool	has_anything(char **command)
// {
// 	if (!command[1])
// 		return (false);
// 	return (true);
// }

// // char	*true_quote_removal(char *str)
// // {
// // 	char	*ret;
// // 	int		i;
// // 	int		j;
// // 	int		size;

// // 	i = 0;
// // 	j = 0;
// // 	size = ft_strlen_s(str, '\"') + 1;
// // 	ret = malloc(size + 1);
// // 	if (!ret)
// // 		return (NULL);
// // 	while (str[i])
// // 	{
// // 		if (str[i] == '"' && !str[i + 1])
// // 			break ;
// // 		if (str[i] == '"')
// // 		{
// // 			i++;
// // 			continue ;
// // 		}
// // 		ret[j] = str[i];
// // 		i++;
// // 		j++;
// // 	}
// // 	ret[j] = '\0';
// // 	return (ret);
// // }

// char	*true_quote_removal(char *str)
// {
// 	return (str);
// }

// int	parse_launch_echo(char **command)
// {
// 	bool	has_n_option;
// 	char	*echo_string;
// 	int		prompt_start_index;

// 	has_n_option = false;
// 	prompt_start_index = 1;
// 	if (has_anything(command) == false)
// 		return (ft_putchar_fd('\n', 1), 1);
// 	if (command[1] && ft_strcmp(command[1], "-n") == 0)
// 	{
// 		has_n_option = true;
// 		prompt_start_index++;
// 	}
// 	while (command[prompt_start_index])
// 	{
// 		if (ft_strcmp(command[prompt_start_index], "-n") != 0)
// 			break ;
// 		prompt_start_index++;
// 	}
// 	if (command[prompt_start_index])
// 	{
// 		if (has_n_option)
// 			echo_string = join_arof_ars(command, prompt_start_index);
// 		else
// 			echo_string = join_arof_ars(command, 1);
// 	}
// 	else
// 		echo_string = ft_strdup("");
// 	ft_echo(echo_string, has_n_option);
// 	return (0);
// }
