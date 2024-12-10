/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 01:20:11 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/10 08:16:24 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipes(int *pipe_fd)
{
	// Creates pipe for every command except last one and checks that pipe did not fail
	if (pipe(pipe_fd) < 0)
	{
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
}

void	create_child_processes(int *pipe_fd, char ***commands, int i,
		int cmd_count, int *input_fd)
{
	pid_t	pid;

	pid = ft_fork();
	// INTERESTING PART ABOUT THIS CODE IS THAT AS FOR CHILD PROCESS ITS OWN PID IS 0 IT MEANS THAT IF ITS WORKING
	// IN ITSELF IT SHOULD TO THIGNS BELOW, IF NOT
	if (pid == 0)
	{
		// IF NOT THE FIRST COMMAND
		if (i > 0)
		{
			dup2(*input_fd, STDIN_FILENO);
			close(*input_fd);
		}
		// IF NOT THE LAST COMMAND
		if (i < cmd_count - 1)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		if (i == 0)
		{
			test_echo(ft_split("xarfruit apple zebanana cherry", ' '),
				STDOUT_FILENO);
		}
		else if(i == 2)
		{
			redirect_output("output.txt");
			cell_launch(commands[i]);
		}
		else
		{
			cell_launch(commands[i]);
		}
		exit(0);
	}
	else
	{
		if (i < cmd_count - 1)
		{
			close(pipe_fd[1]);
		}
		*input_fd = pipe_fd[0];
	}
}

void	pipe_multiple_commands(char ***commands, int cmd_count)
{
	int	pipe_fd[2];
	int	i;
	int	input_fd;

	i = 0;
	input_fd = 0;
	// ITERATE THROUGH EVERY COMMAND
	while (i < cmd_count)
	{
		// IF NOT THE LAST COMMAND PIPE IS OPENED
		if (i < cmd_count - 1)
		{
			create_pipes(pipe_fd);
		}
		create_child_processes(pipe_fd, commands, i, cmd_count, &input_fd);
		i++;
	}
	while (i > 0)
	{
		wait(NULL);
		i--;
	}
}
