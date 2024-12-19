/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:32:25 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/19 19:58:16 by macbook          ###   ########.fr       */
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

//VARIABLE EXPANSION NEEDS TO BE ADDED
//RIGHT NOW ft_split_quotes inside get_simple_cmd checks only for " " but i think it needs to check for all whitespaces
//!!!!ALSO VERY IMPORTANT TO CHECK FOR FAILIING WEIRD QUOTES IN THE BEGINNING OF PROGRAM, for example echo "'"hi' - should be handled somehow

// WE NEEED TO ADD VARIABLE EXPANSION EITHER IN MAIN COMMAND OR IN EXPORT
// ALSO IN HEREDOC IT NEEDS TO FIX VARIABLE EXPANSION INSIDE DOUBLE QUOTES

// EDGE CASES NEEDED TO BE HANDLES
// EXIT STATUS AND ERROR HANDLING NEEDED
int	main(int argc, char **argv)
{
	t_shell_data	*shell;

	// char *test;
	(void)argv;
	(void)argc;
	// atexit(leaks);
	shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell)
		return (1);
	initialize_shell(shell);
	// parse_readline(shell,"cat << EOF");
	printf("%s\n", retrieve_variable(shell, "$USER"));
	parse_readline(shell, "echo hi > output.txt | echo bye");
	process_pipe_list(shell->pipe_list);
	// printf("\nPipes Count: %d\n\n", shell->pipes_count);
	// print_pipe_list(shell->pipe_list);
	execute_script(shell);
	free_env_list(shell->env);
	free_env_list(shell->variables);
	free_var_pipe_list(shell->pipe_list);
	free(shell);
	return (0);
}

// parse_readline(shell, "cat << EOF > output.txt");
/// parse_readline(shell, "cat << EOF > output.txt");
// print_variables_list(shell->variables);
// parse_readline(shell, "unset USER SHELLasd");
// parse_readline(shell,"echo 'Hello World' > output.txt < EOF < test.txt > wow");
// ft_putstr_fd("HIHIHI\n\n", 1);
// printf("%s\n", test_get_variable(shell, "PWD"));
// print_variables_list(shell->variables);
// test = parse_string(shell, "&This is cool $'USER 'FROG");
// printf("Var: %s\n", test);

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
// (>>) test_redirect_append_output(shell, "file.txt");
// (<<) test_redirect_in_heredoc(shell);

// PIPE TESTS
// test_pipes();

// PARSING KEY VALUE
// parse_variable(shell, "TEST=$USER,$HOME-IS-BEST");
