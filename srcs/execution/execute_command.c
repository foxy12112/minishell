/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:21:53 by macbook           #+#    #+#             */
/*   Updated: 2025/01/09 16:03:48 by ldick            ###   ########.fr       */
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

int	execute_single_cmd(t_shell_data *shell, t_var_cmd *cmd, char *line)
{
	while (cmd)
	{
		if (cmd->redirect_count > 0)
		{
			setup_redirects(shell, cmd->redirects, line);
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

int	execute_script(t_shell_data *shell, char *line)
{
	if (shell->pipes_count > 0)
	{
		pipe_multiple_commands(shell, shell->pipe_list);
		return (0);
	}
	else
	{
		execute_single_cmd(shell, shell->pipe_list->cmd, line);
	}
	return (0);
}
