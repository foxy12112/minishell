/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 00:56:03 by macbook           #+#    #+#             */
/*   Updated: 2025/01/15 01:57:46 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_shell_data(t_shell_data *shell)
{
	free_var_pipe_list(shell->pipe_list);
	free_env_list(shell->env);
	free_env_list(shell->variables);
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
		shell->last_exit_code = 1;
		return (1);
	}
	else if (command[1] && !is_digits_only(command[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(command[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		clear_shell_data(shell);
		exit_code = 255;
		exit(exit_code);
	}
	else
	{
		ft_putstr_fd("exit\n", STDIN_FILENO);
		exit_code = 0;
		clear_shell_data(shell);
		exit(0);
	}
	return (EXIT_SUCCESS);
}
