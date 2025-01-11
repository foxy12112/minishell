/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:04 by ldick             #+#    #+#             */
/*   Updated: 2025/01/11 06:20:40 by auplisas         ###   ########.fr       */
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

void	print_two_d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

static void	cleanup(t_shell_data *shell)
{
	// shell->env = initialize_env();
	// shell->variables = initialize_env();
	redirect_to_terminal();
	shell->pipes_count = 0;
	shell->heredoc_launched = false;
	shell->pipe_list = NULL;
}

static int	check_command(t_shell_data *shell)
{
	char	*command;

	command = find_cmd(shell->exec_env,
			true_quote_removal_from_array(shell->pipe_list->cmd->command)[0]);
	if (!command
		&& command_is_builtin(shell->pipe_list->cmd->command[0]) == NULL)
	{
		printf("\ncommand: %s : not found\n",
			shell->pipe_list->cmd->command[0]);
		free(command);
		return (127);
	}
	free(command);
	return (0);
}

void	display(t_shell_data *shell)
{
	char	*input;
	char	*expanded;

	setup_signals();
	while (1)
	{
		input = readline("waiting for input:");
		if (input == NULL)
		{
  			printf("%s", CTRL_D);
			break ;
		}
		if (*input == '\0')
			continue ;
		add_permanent_history(input);
		add_history(input);
		if (!unclosed_quotes(input))
		{
			printf("unclosed quotes present\n");
			continue ;
		}
		expanded = input;
		parse_readline(shell, expanded);
		process_pipe_list(shell->pipe_list);
		if (!command_is_builtin(shell->pipe_list->cmd->command[0])
			&& check_command(shell))
		{
			cleanup(shell);
			continue ;
		}
		// print_pipe_list(shell->pipe_list);
		execute_script(shell);
		cleanup(shell);
	}
	if (input)
		free(input);
	restore_control_echo(shell);
}
