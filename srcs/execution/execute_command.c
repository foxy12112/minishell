/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:21:53 by macbook           #+#    #+#             */
/*   Updated: 2025/01/14 07:43:24 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	launch_single_command(t_shell_data *shell, char **command)
{
	char	*builtin_command_type;

	builtin_command_type = command_is_builtin(command[0]);
	if (builtin_command_type)
	{
		select_launch_builtin(shell, command);
		free(builtin_command_type);
		return (1);
	}
	else
	{
		shell->last_exit_code = cell_launch(shell, command);
		return (0);
	}
	return (0);
}

int	execute_single_cmd(t_shell_data *shell, t_var_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->redirect_count > 0)
		{
			setup_redirects(shell, cmd, cmd->redirects);
			launch_single_command(shell, cmd->command);
		}
		else
		{
			launch_single_command(shell, cmd->command);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	execute_single_process_cmd(t_shell_data *shell)
{
	int	pid;
	int	status;

	prepare_heredoc(shell, shell->pipe_list->cmd);
	pid = fork();
	if (pid < 0)
		cleanup(shell);
	if (pid == 0)
	{
		execute_single_cmd(shell, shell->pipe_list->cmd);
		exit(shell->last_exit_code);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		shell->last_exit_code = WEXITSTATUS(status);
	}
	return (0);
}

int	execute_script(t_shell_data *shell)
{
	if (shell->pipes_count > 0)
	{
		pipe_multiple_commands(shell, shell->pipe_list, shell->pipes_count);
	}
	else
	{
		if (command_is_builtin(shell->pipe_list->cmd->command[0]))
			execute_single_cmd(shell, shell->pipe_list->cmd);
		else
			execute_single_process_cmd(shell);
	}
	return (0);
}
