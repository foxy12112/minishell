/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:32:25 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/15 17:03:31 by auplisas         ###   ########.fr       */
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

// void	test_multi_redirect(t_shell_data *shell)
// {
// 	// char	*args[] = {"cat", NULL};
// 	(void)shell;
// 	redirect_input_heredoc(shell, "EOF");
// 	redirect_output(shell, "output.txt");
// 	redirect_output_append(shell, "append.txt");
// 	// redirect_input(shell, "input.txt");
// 	// redirect_input_heredoc(shell, "EOF");
// 	// redirect_output(shell, "output.txt");
// 	// cell_launch(args);
// 	test_echo(ft_split("xarfruit apple zebanana cherry", ' '), STDOUT_FILENO);
// }

int	execute_redirects(t_redirects *redirect)
{
	while (redirect)
	{
		redirect = redirect->next;
	}
	return (0);
}

char	*command_is_builtin(char *command)
{
	char	*command_toupper;

	command_toupper = ft_strtoupper(command);
	if (!command_toupper)
		return (NULL);
	if (ft_strcmp(command_toupper, "ECHO") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "CD") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "ENV") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "EXIT") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "EXPORT") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "PWD") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "UNSET") == 0)
		return (command_toupper);
	else
		return (free(command_toupper), NULL);
}

char	*join_arof_ars(char **array, int start)
{
	char	*result;
	char	*temp;
	int		i;

	result = NULL;
	i = 0;
	while (i < start && array[i] != NULL)
	{
		i++;
	}
	while (array[i] != NULL)
	{
		if (result == NULL)
		{
			result = ft_strjoin("", array[i]);
		}
		else
		{
			temp = ft_strjoin(result, " ");
			free(result);
			result = ft_strjoin(temp, array[i]);
			free(temp);
		}
		i++;
	}
	return (result);
}

int	parse_launch_echo(char **command)
{
	bool	has_n_option;
	char	*echo_string;

	has_n_option = false;
	if (ft_strcmp(command[1], "-n") == 0)
		has_n_option = true;
	if (has_n_option)
		echo_string = join_arof_ars(command, 2);
	else
		echo_string = join_arof_ars(command, 1);
	ft_echo(echo_string, STDOUT_FILENO, has_n_option);
	return (0);
}

int	parse_launch_cd(t_shell_data *shell, char **command)
{
	int		args_count;
	char	*parsed_path;

	args_count = 0;
	while (command[args_count])
		args_count++;
	if (args_count > 2)
	{
		perror("Too many arguments");
		return (1);
	}
	if (string_in_doublequotes(command[1])
		|| string_in_singlequotes(command[1]))
		parsed_path = remove_quotes(command[1]);
	else
		parsed_path = ft_strdup(command[1]);
	fd_cd(shell, parsed_path);
	free(parsed_path);
	return (0);
}

int	parse_launch_env(t_shell_data *shell, char **command)
{
	int	args_count;

	args_count = 0;
	while (command[args_count])
		args_count++;
	if (args_count > 1)
	{
		perror("Too many arguments");
		return (1);
	}
	ft_env(shell);
	return (0);
}

int	parse_launch_export(t_shell_data *shell, char **command)
{
	ft_export(shell, command);
	return (0);
}

int	parse_launch_pwd(char **command)
{
	int	args_count;

	args_count = 0;
	while (command[args_count])
		args_count++;
	if (args_count > 1)
	{
		perror("Too many arguments");
		return (1);
	}
	ft_pwd();
	return (0);
}

int	select_launch_builtin(t_shell_data *shell, char **command)
{
	char	*command_toupper;

	command_toupper = ft_strtoupper(command[0]);
	if (!command_toupper)
		return (1);
	if (ft_strcmp(command_toupper, "ECHO") == 0)
		parse_launch_echo(command);
	else if (ft_strcmp(command_toupper, "CD") == 0)
		parse_launch_cd(shell, command);
	else if (ft_strcmp(command_toupper, "ENV") == 0)
		parse_launch_env(shell, command);
	else if (ft_strcmp(command_toupper, "EXPORT") == 0)
		parse_launch_export(shell, command);
	else if (ft_strcmp(command_toupper, "PWD") == 0)
		parse_launch_pwd(command);
	else if (ft_strcmp(command_toupper, "UNSET") == 0)
		return (0);
	else if (ft_strcmp(command_toupper, "EXIT") == 0)
		return (0);
	if (command_toupper)
		free(command_toupper);
	return (0);
}

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
		// launch exec function
		cell_launch(command);
		return (0);
	}
	return (0);
}

int	setup_redirects(t_shell_data *shell, t_redirects *redirects)
{
	while (redirects)
	{
		if (redirects->redirect_type == OP_REDIRECT_IN)
			redirect_input(shell, redirects->filename);
		else if (redirects->redirect_type == OP_REDIRECT_OUT)
			redirect_output(shell, redirects->filename);
		else if (redirects->redirect_type == OP_APPEND_OUT)
			redirect_output_append(shell, redirects->filename);
		else if (redirects->redirect_type == OP_HEREDOC)
			redirect_input_heredoc(shell, redirects->delimiter);
		else
		{
			perror("WRONG REDIRECT COMMAND");
			return (1);
		}
		redirects = redirects->next;
	}
	return (0);
}

int	execute_single_cmd(t_shell_data *shell, t_var_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->redirect_count > 0)
		{
			setup_redirects(shell, cmd->redirects);
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

int	execute_script(t_shell_data *shell)
{
	// printf("TEST1-------\n");
	if (shell->pipes_count > 0)
	{
		pipe_multiple_commands(shell, shell->pipe_list, shell->pipes_count);
		return (0);
	}
	else
	{
		execute_single_cmd(shell, shell->pipe_list->cmd);
	}
	return (0);
}

// WE NEEED TO ADD VARIABLE EXPANSION EITHER IN MAIN COMMAND OR IN EXPORT
// ALSO IN HEREDOC IT NEEDS TO FIX VARIABLE EXPANSION INSIDE DOUBLE QUOTES
int	main(int argc, char **argv)
{
	t_shell_data	*shell;

	(void)argv;
	(void)argc;
	atexit(leaks);
	shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell)
		return (1);
	initialize_shell(shell);
	// test_multi_redirect(shell);
	// parse_readline(shell, "cat << EOF > output.txt");
	// parse_readline(shell,"echo 'apple apple apple' | sed 's/apple/orange/g' > output.txt");
	/// parse_readline(shell, "cat << EOF > output.txt");
	parse_readline(shell, "pwd > output.txt");
	// parse_readline(shell,"echo 'Hello World' > output.txt < EOF < test.txt > wow");
	// process_pipe_list(shell->pipe_list);
	execute_script(shell);
	// printf("%s\n", test_get_variable(shell, "PWD"));
	// printf("\nPipes Count: %d\n\n", shell->pipes_count);
	// print_pipe_list(shell->pipe_list);
	// print_variables_list(shell->variables);
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
// (>>) test_redirect_append_output(shell, "file.txt");
// (<<) test_redirect_in_heredoc(shell);

// PIPE TESTS
// test_pipes();

// PARSING KEY VALUE
// parse_variable(shell, "TEST=$USER,$HOME-IS-BEST");
