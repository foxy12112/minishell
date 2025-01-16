/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:04 by ldick             #+#    #+#             */
/*   Updated: 2025/01/16 21:24:46 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_command(t_shell_data *shell)
{
	char	*command;
	char	**cmd_nquotes;
	bool	found;

	found = true;
	cmd_nquotes = true_quote_removal_from_array(shell->pipe_list->cmd->command);
	if (!cmd_nquotes)
		return (false);
	command = find_cmd(shell->exec_env, cmd_nquotes[0]);
	shell->last_exit_code = 0;
	if (!command && shell->pipe_list->cmd->command[0])
	{
		shell->last_exit_code = 2;
		ft_putstr_fd("command: ", STDERR_FILENO);
		ft_putstr_fd(shell->pipe_list->cmd->command[0], STDERR_FILENO);
		ft_putstr_fd(": not found\n", STDERR_FILENO);
		found = false;
	}
	free(command);
	free_string_array(cmd_nquotes);
	return (found);
}

int	handle_empty_input(char *input)
{
	if (*input == '\0')
		return (1);
	return (0);
}

int	handle_unclosed_quotes(t_shell_data *shell, char *input)
{
	if (!unclosed_quotes(input))
	{
		free(input);
		shell->last_exit_code = 1;
		printf("unclosed quotes present\n");
		return (1);
	}
	return (0);
}

int	handle_command_validation(t_shell_data *shell)
{
	char	*builtin_type;

	builtin_type = command_is_builtin(shell->pipe_list->cmd->command[0]);
	if (!builtin_type && !check_command(shell))
	{
		cleanup(shell);
		shell->last_exit_code = 127;
		return (1);
	}
	if (builtin_type)
		free(builtin_type);
	return (0);
}

int	handle_parse_errors(t_shell_data *shell)
{
	if (!check_for_parse_errors(shell->pipe_list))
	{
		shell->last_exit_code = 2;
		cleanup(shell);
		return (1);
	}
	return (0);
}
