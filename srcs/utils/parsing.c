/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:04 by ldick             #+#    #+#             */
/*   Updated: 2025/01/16 08:31:35 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_history(void)
{
	int		fd;
	char	*line;

	fd = open(".git/permanent_history/history.log", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		free(line);
		line = NULL;
	}
	close(fd);
}

void	add_permanent_history(char *str)
{
	int		fd;
	char	*file;

	file = ".git/permanent_history/history.log";
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*str == '\0')
	{
		ft_putchar_fd('\n', fd);
		close(fd);
		return ;
	}
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}

void	cleanup(t_shell_data *shell)
{
	redirect_to_terminal();
	// if(shell->heredoc_launched == false)
	free_var_pipe_list(shell->pipe_list);
	shell->pipe_list = NULL;
	shell->pipes_count = 0;
	shell->heredoc_launched = false;
	shell->pipe_list = NULL;
}

bool	check_command(t_shell_data *shell)
{
	char	*command;
	char	**command_noquotes;
	bool	found;

	found = true;
	command_noquotes = true_quote_removal_from_array(shell->pipe_list->cmd->command);
	if (!command_noquotes)
		return (false);
	command = find_cmd(shell->exec_env, command_noquotes[0]);
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
	// print_pipe_list(shell->pipe_list);
	free_string_array(command_noquotes);
	return (found);
}

void	display(t_shell_data *shell)
{
	char *input;
	char *builtin_command_type;

	setup_signals();
	while (1)
	{
		if (isatty(fileno(stdin)))
			input = readline("minishell:");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			cleanup(shell);
			exit(shell->last_exit_code);
		}
		if (*input == '\0')
		{
			continue ;
		}
		add_permanent_history(input);
		add_history(input);
		if (!unclosed_quotes(input))
		{
			free(input);
			printf("unclosed quotes present\n");
			continue ;
		}
		parse_readline(shell, input);
		// print_pipe_list(shell->pipe_list);
		builtin_command_type = command_is_builtin(shell->pipe_list->cmd->command[0]);
		if (!builtin_command_type && !check_command(shell))
		{
			cleanup(shell);
			shell->last_exit_code = 127;
			continue ;
		}
		if (builtin_command_type)
			free(builtin_command_type);
		if (!check_for_parse_errors(shell->pipe_list))
		{
			shell->last_exit_code = 2;
			cleanup(shell);
			continue ;
		}
		execute_script(shell);
		cleanup(shell);
	}
	if (input)
		free(input);
	restore_control_echo();
}