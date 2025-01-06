/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:03:07 by macbook           #+#    #+#             */
/*   Updated: 2025/01/05 14:54:46 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parse_heredoc(t_shell_data *shell, char *str)
{
	char	*line;

	line = ft_expand_variables(shell, str);
	return (line);
}

void	redirect_input_heredoc(t_shell_data *shell, const char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	char	*parsed_line;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe failed"), exit(EXIT_FAILURE));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		parsed_line = parse_heredoc(shell, line);
		ft_putstr_fd(parsed_line, pipe_fd[1]);
		ft_putchar_fd('\n', pipe_fd[1]);
		// free(line);
		free(parsed_line);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 failed"), exit(EXIT_FAILURE));
	shell->heredoc_launched = true;
	close(pipe_fd[0]);
}
