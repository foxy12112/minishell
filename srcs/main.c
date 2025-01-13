/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:32:25 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/13 04:53:25 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

// static char	**init_exec_env(void)
// {
// 	char	**env;

// 	env = ft_split(getenv("PATH"), ':');
// 	return (env);
// }

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

int	main(int argc, char **argv, char **env)
{
	char test[] = "\"\'\"\'$USER\'\"\'\"";
	char **res;
	
	res = ft_split_delimiters(test, &is_delimiter);
	print_arofars(res);
	// t_shell_data	*shell;

	(void)argv;
	(void)argc;
	(void)env;
	// // atexit(leaks);
	// shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	// if (!shell)
	// 	return (1);
	// initialize_shell(shell, env);
	// shell->enviroment = env;
	// init_history();
	// shell->exec_env = init_exec_env();
	// disable_control_echo(shell);
	// display(shell);
	// free_env_list(shell->env);
	// free_env_list(shell->variables);
	// free_var_pipe_list(shell->pipe_list);
	// free(shell);
	// // system("leaks minishell");
	// return (shell->last_exit_code);
	return (0);
}
