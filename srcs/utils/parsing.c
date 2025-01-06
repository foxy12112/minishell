/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:04 by ldick             #+#    #+#             */
/*   Updated: 2025/01/06 16:35:01 by ldick            ###   ########.fr       */
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

// static void cleanup(t_shell_data *shell)
// {
// 	// shell->env = initialize_env();
// 	// shell->variables = initialize_env();
// 	shell->pipes_count = 0;
// 	shell->heredoc_launched = false;
// 	shell->pipe_list = NULL;
// }

static int	check_command(t_shell_data *shell)
{
	char	*command;

	command = find_cmd(shell->exec_env,
			remove_quotes_from_array(shell->pipe_list->cmd->command)[0]);
	if (!access(command, 0)
		&& command_is_builtin(remove_quotes_from_array
			(shell->pipe_list->cmd->command)[0]) == NULL)
	{
		printf("\ncommand: %s : not found\n",
			shell->pipe_list->cmd->command[0]);
		free(command);
		return (1);
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
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		add_permanent_history(input);
		add_history(input);
		if (unclosed_quotes(input))
		{
			printf("unclosed quotes present\n");
			continue ;
		}
		expanded = ft_expand_variables(shell, input);
		parse_readline(shell, expanded);
		if (check_command(shell))
		{
			// cleanup(shell);
			continue ;
		}
		execute_script(shell);
		// free(expanded);
		// cleanup(shell);
		// free(input);
	}
	if (input)
		free(input);
	restore_control_echo(shell);
	rl_clear_history();
}
