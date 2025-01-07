/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_to_terminal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:12:16 by macbook           #+#    #+#             */
/*   Updated: 2025/01/07 05:12:25 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int redirect_to_terminal(t_shell_data *shell)
{
    int fd;

    fd = open("/dev/tty", O_WRONLY);
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