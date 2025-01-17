/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 00:56:03 by macbook           #+#    #+#             */
/*   Updated: 2025/01/17 09:53:52 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_length(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

bool	is_digits_only(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

void	handle_simple_exit(t_shell_data *shell)
{
	ft_putstr_fd("exit", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	clear_shell_data(shell);
	exit(0);
}

static void	handle_exit_with_code(t_shell_data *shell, char *arg)
{
	int	exit_code;

	exit_code = ft_atoi(arg) % 256;
	shell->last_exit_code = exit_code;
	ft_putendl_fd("exit", STDERR_FILENO);
	clear_shell_data(shell);
	exit(exit_code);
}

int	ft_exit(t_shell_data *shell, char **command)
{
	int	args_count;
	int	exit_code;

	args_count = args_length(command);
	if (args_count > 2)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->last_exit_code = 255;
		exit(255);
	}
	else if (command[1] && !is_digits_only(command[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		clear_shell_data(shell);
		exit_code = 255;
		exit(exit_code);
	}
	else if (command[1])
		handle_exit_with_code(shell, command[1]);
	else
		handle_simple_exit(shell);
	return (EXIT_SUCCESS);
}
