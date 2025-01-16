/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:05 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/16 21:27:55 by auplisas         ###   ########.fr       */
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

int	ft_echo2(char *args, int fd, bool n_option)
{
	int	i;

	i = 0;
	if (args)
	{
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
	}
	return (0);
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
	ft_echo2(echo_string, STDOUT_FILENO, has_n_option);
	shell->last_exit_code = 0;
	return (shell->last_exit_code);
}
