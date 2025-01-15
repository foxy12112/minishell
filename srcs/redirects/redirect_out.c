/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 04:07:36 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/15 05:16:39 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_output(t_shell_data *shell, const char *filename)
{
	int	fd;

	(void)shell;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		shell->last_exit_code = EXIT_FAILURE;	
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		shell->last_exit_code = 2;
		return (1);
	}
	close(fd);
	shell->last_exit_code = 0;
	return (0);
}

