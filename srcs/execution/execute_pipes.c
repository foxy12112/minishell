/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 01:20:11 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/17 21:52:21 by ldick            ###   ########.fr       */
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

void	create_child_processes(t_shell_data *shell, int *pipe_fd,
		t_var_pipe_list *current, int input_fd)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		if (input_fd != 0)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (current->next != NULL)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
		}
		execute_single_cmd(shell, current->cmd);
		exit(0);
	}
	close(pipe_fd[1]);
}

void	pipe_multiple_commands(t_shell_data *shell, t_var_pipe_list *pipe_list,
		int cmd_count)
{
	int				pipe_fd[2];
	int				input_fd;
	t_var_pipe_list	*current;

	(void)cmd_count;
	input_fd = 0;
	current = pipe_list;
	while (current != NULL)
	{
		if (current->next != NULL)
			create_pipes(pipe_fd);
		prepare_heredoc(shell, current->cmd);
		create_child_processes(shell, pipe_fd, current, input_fd);
		if (current->prev)
			close(input_fd);
		input_fd = reset_heredoc_fd(shell, pipe_fd, current->cmd);
		current = current->next;
	}
	current = pipe_list;
	while (current != NULL)
	{
		wait(NULL);
		current = current->next;
	}
}
