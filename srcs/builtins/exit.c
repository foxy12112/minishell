/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 00:56:03 by macbook           #+#    #+#             */
/*   Updated: 2025/01/16 08:37:47 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_shell_data(t_shell_data *shell)
{
	if (shell->env)
	{
		free_env_list(shell->env);
		shell->env = NULL;
	}
	if (shell->variables)
	{
		free_env_list(shell->variables);
		shell->variables = NULL;
	}
	free_var_pipe_list(shell->pipe_list);
	free_string_array(shell->exec_env);
	restore_control_echo();
	free(shell);
}

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

int	ft_exit(t_shell_data *shell, char **command)
{
	int	args_count;
	int	exit_code;

	args_count = args_length(command);
	if (args_count > 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
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
	{
		shell->last_exit_code = ft_atoi(command[1]);
		shell->last_exit_code = shell->last_exit_code % 256;
		exit_code = shell->last_exit_code;
		ft_putendl_fd("exit", STDERR_FILENO);
		clear_shell_data(shell);
		exit(exit_code);
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		clear_shell_data(shell);
		exit_code = 0;
		shell->last_exit_code = 0;
		exit(0);
	}
	return (EXIT_SUCCESS);
}
