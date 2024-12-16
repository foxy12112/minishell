/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 04:07:19 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/14 16:18:49 by macbook          ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}
