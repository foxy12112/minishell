/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 05:54:47 by macbook           #+#    #+#             */
/*   Updated: 2024/12/06 06:31:25 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		printf("Fork Failed");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	ft_execvp(const char *file, char *const argv[])
{
	if (!file || !argv)
	{
		printf("Execvp: invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	fflush(stdout);
	if (execvp(file, argv) == -1)
	{
		perror("Ececvp failed");
		exit(EXIT_FAILURE);
	}
}

void	cell_launch(char **args)
{
	pid_t pid = ft_fork();
	if (pid == 0)
	{
		ft_execvp(args[0], args);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
	}
}