/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_append.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:52:17 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/06 19:25:49 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Symbol (>>)
int	redirect_output_append(t_shell_data *shell, const char *filename)
{
	int	fd;

	(void)shell;
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Failed to open output file");
		shell->last_exit_code = 1;
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		shell->last_exit_code = 1;
		return (-1);
	}
	close(fd);
	shell->last_exit_code = 0;
	return (0);
}
