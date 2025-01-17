/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:32:25 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/17 10:54:35 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

static char	**init_exec_env(void)
{
	char	**env;

	env = ft_split(getenv("PATH"), ':');
	return (env);
}

void	display(t_shell_data *shell)
{
	char *input;

	setup_signals();
	while (1)
	{
		if (isatty(fileno(stdin)))
			input = readline("minishell:");
		else
		{
			char	*line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		handle_exit(shell, input);
		if (handle_empty_input(input))
			continue ;
		add_permanent_history(input);
		add_history(input);
		if (handle_unclosed_quotes(shell, input))
			continue ;
		parse_readline(shell, input);
		if (handle_command_validation(shell))
			continue ;
		if (handle_parse_errors(shell))
			continue ;
		execute_script(shell);
		cleanup(shell);
	}
	if (input)
		free(input);
	restore_control_echo();
}

int	main(int argc, char **argv, char **env)
{
	t_shell_data	*shell;
	int				exit_code;

	(void)argv;
	(void)argc;
	shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell)
		return (1);
	initialize_shell(shell, env);
	shell->enviroment = env;
	init_history();
	shell->exec_env = init_exec_env();
	// disable_control_echo(shell);
	display(shell);
	exit_code = shell->last_exit_code;
	clear_shell_data(shell);
	return (exit_code);
}
