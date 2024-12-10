/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 03:18:43 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/10 10:14:34 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// VARIABLES

char	*test_get_variable(t_shell_data *shell, char *key)
{
	return (retrieve_variable(shell, key));
}

// BUILTIN TESTS

void	test_cd(t_shell_data *shell)
{
	printf("Printing OLD PWDs:\n\n");
	printf("PWD: %s\n", retrieve_variable(shell, "PWD"));
	printf("OLDPWD: %s\n", retrieve_variable(shell, "OLDPWD"));
	fd_cd(shell, "../");
	printf("\nPrinting Renewed PWDs:\n\n");
	printf("PWD: %s\n", retrieve_variable(shell, "PWD"));
	printf("OLDPWD: %s\n", retrieve_variable(shell, "OLDPWD"));
}

void	test_export(t_shell_data *shell)
{
	printf("Printing Default Variable List:\n\n");
	print_variables_list(shell->variables);
	ft_export(shell, ft_split("HI=MTE YELLO=YUUU", ' '));
	printf("\nPrinting Renewed Variable List:\n\n");
	print_variables_list(shell->variables);
}

void	test_echo(char **string, int fd)
{
	ft_echo(string, fd, false);
}

void	test_env(t_shell_data *shell)
{
	ft_env(shell);
}

void	test_pwd(void)
{
	ft_pwd();
}

void	test_unset(t_shell_data *shell)
{
	ft_export(shell, ft_split("HI=MTE YELLO=YUUU", ' '));
	printf("\nPrinting Default ENV List:\n\n");
	print_env_list(shell->env);
	ft_unset(shell, "HI");
	printf("\nPrinting New ENV List:\n\n");
	print_env_list(shell->env);
}

// REDIRECT TESTS

//(>)
int	test_redirect_output(char *filename)
{
	if (redirect_output(filename) < 0)
	{
		return (1);
	}
	test_echo(ft_split("HI THIS IS TEST", ' '), STDOUT_FILENO);
	return (0);
}

//(<)
void	test_redirect_input(char *filename, char *command)
{
	char	*args[] = {command, NULL};

	redirect_input(filename);
	cell_launch(args);
}

int	test_redirect_append_output(char *filename)
{
	if (redirect_output_append(filename) < 0)
	{
		return (1);
	}
	test_echo(ft_split("GELA", ' '), STDOUT_FILENO);
	return (0);
}

void	test_redirect_in_heredoc(t_shell_data *shell)
{
	char	*args[] = {"cat", NULL};

	redirect_input_heredoc(shell, "EOF");
	redirect_output("test.txt");
	cell_launch(args);
}

// EXECs

void	test_exec(char **command)
{
	cell_launch(command);
}

void	launch_program(void)
{
	char	*args[] = {"/Users/auplisas/Desktop/minishell/testprogram", NULL};

	cell_launch(args);
}

// PIPES

void	test_pipes(void)
{
	char *cmd1[] = {"echo", "xarfruit apple zebanana cherry", NULL};
	char *cmd2[] = {"tr", " ", "\n", NULL};
	char *cmd3[] = {"sort", NULL};
	char **commands[] = {cmd1, cmd2, cmd3};

	pipe_multiple_commands(commands, 3);
}