/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 04:07:36 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/07 05:07:18 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Symbol (>)
// As HEREDOC blocks redirect input in bash there is possibility for
// same function in output but i am not sure
// if there is such case just add this code below (void)shell;
// if (shell->heredoc_launched)
// return ;
int	redirect_output(t_shell_data *shell, const char *filename)
{
	int	fd;

	(void)shell;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		shell->last_exit_code = 1;	
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		shell->last_exit_code = 1;
		return (1);
	}
	close(fd);
	shell->last_exit_code = 0;
	return (0);
}

