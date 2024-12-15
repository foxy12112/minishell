/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:32:25 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/15 06:37:02 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

void	print_redirects(t_redirects *redirect)
{
	while (redirect)
	{
		printf("\tRedirect Type: %d\n", redirect->redirect_type);
		printf("\tFilename: %s\n", redirect->filename);
		printf("\tDelimiter: %s\n", redirect->delimiter);
		printf("\n");
		redirect = redirect->next;
	}
}

void	print_arofars(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("[%s]", str[i]);
		i++;
	}
}
void	print_commands(t_var_cmd *cmd)
{
	while (cmd)
	{
		printf("Command:");
		print_arofars(cmd->command);
		printf("\n");
		printf("Redirect Count: %d\n", cmd->redirect_count);
		if (cmd->redirects)
		{
			printf("Redirects:\n");
			print_redirects(cmd->redirects);
		}
		cmd = cmd->next;
	}
}

void	print_pipe_list(t_var_pipe_list *pipe_list)
{
	while (pipe_list)
	{
		if (pipe_list->cmd)
		{
			print_commands(pipe_list->cmd);
		}
		else
		{
			printf("No commands in this pipe.\n");
		}
		printf("\n\n");
		pipe_list = pipe_list->next;
	}
}

void	test_multi_redirect(t_shell_data *shell)
{
	// char	*args[] = {"cat", NULL};
	(void)shell;
	redirect_input_heredoc(shell, "EOF");
	redirect_output(shell, "output.txt");
	redirect_output_append("append.txt");
	// redirect_input(shell, "input.txt");
	// redirect_input_heredoc(shell, "EOF");
	// redirect_output(shell, "output.txt");
	// cell_launch(args);
	test_echo(ft_split("xarfruit apple zebanana cherry", ' '), STDOUT_FILENO);
}

int	execute_script(t_shell_data *shell)
{
	if (shell->pipes_count > 0)
	{
		//launch pipes
	}
	else if
	{

	}
}

// WHEN HEREDOC IS USED REDIRECT_IN HAS TO BE DISABLED --- IMPORTANT NOTICE TO DO
int	main(int argc, char **argv)
{
	t_shell_data	*shell;

	(void)argv;
	(void)argc;
	// atexit(leaks);
	shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell)
		return (1);
	initialize_shell(shell);
	// test_multi_redirect(shell);
	parse_readline(shell, "echo \"Hello World\" | grep >> 'Hello' | wc -c > output.txt");
	// parse_readline(shell, "echo -n \"Hello World and Sun\" ");
	// parse_readline(shell,
	// 	"echo 'Hello World' >> test < zaza >> output.txt <<EOF > test.txt < wow | cat >> LALAL > outpas.c << EOF");
	process_pipe_list(shell->pipe_list);
	// parse_readline(shell,"echo 'Hello World' > output.txt < EOF < test.txt > wow");
	printf("\nPipes Count: %d\n\n", shell->pipes_count);
	print_pipe_list(shell->pipe_list);
	free_env_list(shell->env);
	free_env_list(shell->variables);
	free_var_pipe_list(shell->pipe_list);
	free(shell);
	return (0);
}

// VARIABLE TEST
// printf("%s\n", test_get_variable(shell, "USER"));

// BUILTIN TESTS
// test_cd(shell);
// test_export(shell);
// test_echo();
// test_env(shell);
// test_pwd();
// test_unset(shell);

// EXEC FUNCTION TESTS
// cell_launch(ft_split("cat test", ' '));
// launch_program();

// REDIRECT TESTS
// (>) test_redirect_output(shell, "file.txt");
// (<) test_redirect_input(shell, "file.txt", "cat");
// (>>) test_redirect_append_output("file.txt");
// (<<) test_redirect_in_heredoc(shell);

// PIPE TESTS
// test_pipes();

// PARSING KEY VALUE
// parse_variable(shell, "TEST=$USER,$HOME-IS-BEST");
