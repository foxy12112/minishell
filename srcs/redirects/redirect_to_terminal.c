/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_to_terminal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 05:12:16 by macbook           #+#    #+#             */
/*   Updated: 2025/01/07 14:13:07 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int redirect_to_terminal(void)
{
    int fd;

    fd = open("/dev/tty", O_WRONLY);
    if (fd < 0)
    {
        perror("open");
        return (1);
    }

    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return (1);
    }

    close(fd);
    return (0);
}