/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:38:18 by macbook           #+#    #+#             */
/*   Updated: 2024/12/08 07:34:42 by auplisas         ###   ########.fr       */
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

void	redirect_input_heredoc(const char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	size_t	len;
	ssize_t	nread;

	line = NULL;
	len = 0;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf("heredoc> ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			break ;
		}
		write(pipe_fd[1], "HI", 2);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	free(line);
}

int	main(int argc, char **argv)
{
	t_shell_data	*shell;
	char			*args[] = {"cat", NULL};

	// atexit(leaks);
	(void)argv;
	(void)argc;
	shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell)
		return (1);
	initialize_shell(shell);
	redirect_input_heredoc("EOF");
	cell_launch(args);
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