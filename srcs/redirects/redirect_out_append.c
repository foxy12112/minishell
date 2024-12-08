/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_append.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:52:17 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/08 04:17:46 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Symbol (>>)
int	redirect_output_append(const char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Failed to open output file");
		return (-1);
	}

	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return (-1);
	}

	close(fd);
	return (0);
}