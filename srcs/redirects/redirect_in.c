/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 04:07:19 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/15 05:17:18 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Symbol (<)
void	redirect_input(t_shell_data *shell, const char *filename)
{
	int	fd;

	if (shell->heredoc_launched)
		return ;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open input file");
		shell->last_exit_code = 127;
		exit(127);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		shell->last_exit_code = 127;
		exit(127);
	}
	shell->last_exit_code = 0;
	close(fd);
}
