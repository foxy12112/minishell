/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:38:18 by macbook           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/10 10:54:25 by ldick            ###   ########.fr       */
=======
/*   Updated: 2024/12/10 10:36:54 by ldick            ###   ########.fr       */
>>>>>>> 6ab469a7dabddd1902f573d59be82f8034bd2907
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv)
{
	// t_shell_data	*shell;

	// atexit(leaks);
	(void)argv;
	(void)argc;
	shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell)
		return (1);
	initialize_shell(shell);
	cell_launch(ft_split("cat input.txt", ' '));
	free_env_list(shell->env);
	free_env_list(shell->variables);
	free(shell);
	return (0);
}

//BUILTIN TESTS

// test_cd(shell);
// test_export(shell);
// test_echo();
// test_env(shell);
// test_pwd();
// test_unset(shell);

//Exec function tests
//cell_launch(ft_split("mkdir test", ' '));
//REDIRECT TESTS