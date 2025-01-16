/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:32:25 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/16 08:13:32 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

void	print_redirects(t_redirects *redirect)
{
	printf("Printing Redirects:\n");
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
	printf("\n");
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

static char	**init_exec_env(void)
{
	char	**env;

	env = ft_split(getenv("PATH"), ':');
	return (env);
}

int	main(int argc, char **argv, char **env)
{
	t_shell_data	*shell;
	int				exit_code;

	(void)argv;
	(void)argc;
	// (void)env;
	// atexit(leaks);
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
	//system("leaks minishell");
	return (exit_code);
}

// char **dara = ft_split_delimiters("$USER$TESTNOTFOUND$HOME$WTF$PWD asd '");
// print_arofars(dara);