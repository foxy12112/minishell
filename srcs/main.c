/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:38:18 by macbook           #+#    #+#             */
/*   Updated: 2024/12/08 04:18:48 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	select_operation_type(char **args_ar, t_shell_data *data_tree)
{
	int	i;

	i = 0;
	while (args_ar[i])
	{
		if (ft_strcmp(args_ar[i], "<") == 0)
			data_tree->operation_type = RDR_OUTPUT;
		else if (ft_strcmp(args_ar[i], ">") == 0)
			data_tree->operation_type = RDR_INPUT;
		else if (ft_strcmp(args_ar[i], ">>") == 0)
			data_tree->operation_type = RDR_APPEND;
		else if (ft_strcmp(args_ar[i], "<<") == 0)
			data_tree->operation_type = RDR_HEREDOC;
		else if (ft_strcmp(args_ar[i], "|") == 0)
			data_tree->operation_type = PIPE;
		else
			data_tree->operation_type = NO_RDR;
	}
}

int	execute_arguments(char **args_ar)
{
	t_shell_data	*data_tree;

	data_tree = malloc(1 * sizeof(t_shell_data));
	if (!data_tree)
		return (1);
	select_operation_type(args_ar, data_tree);
	if (data_tree->operation_type != NO_RDR)
	{
		// launch_redirect();
	}
	return (0);
}

void	leaks(void)
{
	system("leaks minishella");
}

// void	redirect_input_heredoc(const char *delimiter)
// {
// 	int		pipe_fd[2];
// 	char	*line;
// 	size_t	len;
// 	ssize_t	nread;

// 	line = NULL;
// 	len = 0;
// 	// Create a pipe to pass the heredoc input
// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("pipe failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	// Read the input for the heredoc until we encounter the delimiter
// 	while (1)
// 	{
// 		printf("heredoc> ");
// 		nread = getline(&line, &len, stdin);
// 		if (nread == -1)
// 		{
// 			break ;
// 		}
// 		// If the line matches the delimiter, stop reading
// 		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
// 		{
// 			break ;
// 		}
// 		// Write the line to the pipe
// 		write(pipe_fd[1], line, nread);
// 	}
// 	// Close the write end of the pipe
// 	close(pipe_fd[1]);
// 	// Redirect the pipe to stdin
// 	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// 	{
// 		perror("dup2 failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	// Close the read end of the pipe
// 	close(pipe_fd[0]);
// 	free(line); // Free the line buffer
// }

int	main(int argc, char **argv)
{
	t_shell_data	*shell;

	// atexit(leaks);
	(void)argv;
	(void)argc;
	shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell)
		return (1);
	initialize_shell(shell);
	// redirect_input_heredoc("EOF");
	free_env_list(shell->env);
	free_env_list(shell->variables);
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

// REDIRECT TESTS
// (>) 	test_redirect_output("file.txt");
// (<) test_redirect_input("file.txt", "cat");
// (>>) test_redirect_append_output("file.txt");
// (<<)