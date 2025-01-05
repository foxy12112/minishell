/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 01:20:11 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/05 13:22:49 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipes(int *pipe_fd)
{
	if (pipe(pipe_fd) < 0)
	{
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
}

// void	create_child_processes(int *pipe_fd, char ***commands, int *iterators,
// 		int *input_fd)
// {
// 	pid_t	pid;

// 	pid = ft_fork();
// 	if (pid == 0)
// 	{
// 		if (iterators[0] > 0)
// 		{
// 			dup2(*input_fd, STDIN_FILENO);
// 			close(*input_fd);
// 		}
// 		if (iterators[0] < iterators[1] - 1)
// 		{
// 			close(pipe_fd[0]);
// 			dup2(pipe_fd[1], STDOUT_FILENO);
// 			close(pipe_fd[1]);
// 		}
// 		cell_launch(commands[iterators[0]]);
// 		exit(0);
// 	}
// 	else
// 	{
// 		if (iterators[0] < iterators[1] - 1)
// 			close(pipe_fd[1]);
// 		*input_fd = pipe_fd[0];
// 	}
// }

void	create_child_processes(t_shell_data *shell, int *pipe_fd,
		t_var_pipe_list *current, int *input_fd)
{
	pid_t	pid;
	int		devnull;

	pid = ft_fork();
	if (pid == 0)
	{
		if (*input_fd != 0)
		{
			dup2(*input_fd, STDIN_FILENO);
			close(*input_fd);
		}
		if (current->next != NULL)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		close(STDERR_FILENO);
		devnull = open("/dev/null", O_WRONLY);
		dup2(devnull, STDERR_FILENO);
		close(devnull);
		execute_single_cmd(shell, current->cmd);
		exit(0);
	}
	else
	{
		if (current->next != NULL)
			close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
}

// void	pipe_multiple_commands(t_shell_data *shell, t_var_pipe_list *pipe_list,
// 		int cmd_count)
// {
// 	int				pipe_fd[2];
// 	int				input_fd;
// 	t_var_pipe_list	*current;

// 	(void)cmd_count;
// 	input_fd = 0;
// 	current = pipe_list;
// 	while (current != NULL)
// 	{
// 		if (current->next != NULL)
// 		{
// 			create_pipes(pipe_fd);
// 		}
// 		create_child_processes(shell, pipe_fd, current, &input_fd);
// 		current = current->next;
// 	}
// 	current = pipe_list;
// 	while (current != NULL)
// 	{
// 		wait(NULL);
// 		current = current->next;
// 	}
// }

void	pipe_multiple_commands(t_shell_data *shell, t_var_pipe_list *pipe_list)
{
	int pipe_fd[2];
	int input_fd;
	t_var_pipe_list *current;

	input_fd = STDIN_FILENO;
	current = pipe_list;
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			create_pipes(pipe_fd);
		}
		create_child_processes(shell, pipe_fd, current, &input_fd);
		if (input_fd != STDIN_FILENO)
		{
			close(input_fd);
			input_fd = STDIN_FILENO;
		}
		if (current->next != NULL)
			close(pipe_fd[1]);
		current = current->next;
	}
	current = pipe_list;
	while (current != NULL)
	{
		wait(NULL);
		current = current->next;
	}
}
