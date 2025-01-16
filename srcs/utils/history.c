/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:41:57 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/16 16:44:02 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_history(void)
{
	int		fd;
	char	*line;

	fd = open(".git/permanent_history/history.log", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		free(line);
		line = NULL;
	}
	close(fd);
}

void	add_permanent_history(char *str)
{
	int		fd;
	char	*file;

	file = ".git/permanent_history/history.log";
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*str == '\0')
	{
		ft_putchar_fd('\n', fd);
		close(fd);
		return ;
	}
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}
