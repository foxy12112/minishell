/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:38:18 by macbook           #+#    #+#             */
/*   Updated: 2024/12/07 07:59:47 by macbook          ###   ########.fr       */
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

// Symbol > , redirects output of echo f.e into file
int	redirect_output(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

void	redirect_input(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open input file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

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
	// redirect_input("hi.txt");
	// shell->fd = redirect_output("file.txt");
	// if (shell->fd < 0)
	// {
	// 	return (1);
	// }
	// close(shell->fd);
	// char *args[] = {"cat", NULL};

    // cell_launch(args);
	cell_launch(ft_split("cat test", ' '));
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