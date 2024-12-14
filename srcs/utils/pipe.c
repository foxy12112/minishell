/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 01:20:11 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/14 11:22:02 by macbook          ###   ########.fr       */
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

void	create_child_processes(int *pipe_fd, char ***commands, int *iterators,
		int *input_fd)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		if (iterators[0] > 0)
		{
			dup2(*input_fd, STDIN_FILENO);
			close(*input_fd);
		}
		if (iterators[0] < iterators[1] - 1)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		cell_launch(commands[iterators[0]]);
		// if (iterators[0] == 0)
		// {
		// 	test_echo(ft_split("xarfruit apple zebanana cherry", ' '),
		// 		STDOUT_FILENO);
		// }
		// else if (iterators[0] == 2)
		// {
		// 	redirect_output("output.txt");
		// 	cell_launch(commands[iterators[0]]);
		// }
		// else
		// {
		// 	cell_launch(commands[iterators[0]]);
		// }
		exit(0);
	}
	else
	{
		if (iterators[0] < iterators[1] - 1)
			close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
}

void	pipe_multiple_commands(char ***commands, int cmd_count)
{
	int	pipe_fd[2];
	int	iterators[2];
	int	input_fd;

	iterators[0] = 0;
	iterators[1] = cmd_count;
	input_fd = 0;
	while (iterators[0] < cmd_count)
	{
		if (iterators[0] < cmd_count - 1)
		{
			create_pipes(pipe_fd);
		}
		create_child_processes(pipe_fd, commands, iterators, &input_fd);
		iterators[0]++;
	}
	while (iterators[0] > 0)
	{
		wait(NULL);
		iterators[0]--;
	}
}
