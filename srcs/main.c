/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:38:18 by macbook           #+#    #+#             */
/*   Updated: 2024/12/10 04:40:59 by auplisas         ###   ########.fr       */
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

// void	leaks(void)
// {
// 	system("leaks minishella");
// }

int	main(int argc, char **argv)
{
	// t_shell_data	*shell;
	char			*cmd1[] = {"cat", "file.txt", NULL};
	char			*cmd2[] = {"awk", "/pattern/", NULL};
	char			*cmd3[] = {"sort", NULL};

	char			**commands[] = {cmd1, cmd2, cmd3};
	// atexit(leaks);
	(void)argv;
	(void)argc;
	// shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	// if (!shell)
	// 	return (1);
	// initialize_shell(shell);
	// pipe_commands(cmd1, cmd2);
	pipe_multiple_commands(commands, 3);
	// pipe_commands(cmd2, cmd3);
	// free_env_list(shell->env);
	// free_env_list(shell->variables);
	// free(shell);
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
// (>) test_redirect_output("file.txt");
// (<) test_redirect_input("file.txt", "cat");
// (>>) test_redirect_append_output("file.txt");
// (<<) test_redirect_in_heredoc(shell);
