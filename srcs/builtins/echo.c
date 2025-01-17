/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:05 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/17 15:16:02 by macbook          ###   ########.fr       */
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

bool	is_newline_option(char *str)
{
	int	i;

	if (str[0] != '-')
	{
		return (false);
	}
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	has_anything(char **command)
{
	if (!command[1])
		return (false);
	return (true);
}

char	*true_quote_removal(char *str)
{
	return (str);
}

int	parse_launch_echo(t_shell_data *shell, char **command)
{
	bool	has_n_option;
	char	*echo_string;
	int		prompt_start_index;

	has_n_option = false;
	prompt_start_index = 1;
	if (has_anything(command) == false)
		return (ft_putchar_fd('\n', 1), 1);
	while (command[prompt_start_index])
	{
		if (!is_newline_option(command[prompt_start_index]))
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
	shell->last_exit_code = 0;
	return (shell->last_exit_code);
}
