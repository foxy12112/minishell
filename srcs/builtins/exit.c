/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 00:56:03 by macbook           #+#    #+#             */
/*   Updated: 2025/01/07 04:59:05 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_shell_data(t_shell_data *shell)
{
	int	exit_code;

	exit_code = shell->last_exit_code;
	free_env_list(shell->env);
	free_env_list(shell->variables);
	free_var_pipe_list(shell->pipe_list);
	restore_control_echo(shell);
	free(shell);
	exit(exit_code);
}

void	ft_exit(t_shell_data *shell)
{
	(void)shell;
	if (isatty(STDIN_FILENO))
	{
		ft_putstr_fd("exit", STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("exit", STDIN_FILENO);
		ft_putchar_fd('\n', STDIN_FILENO);
	}
	clear_shell_data(shell);
}
