/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:03:07 by macbook           #+#    #+#             */
/*   Updated: 2025/01/07 04:59:28 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parse_heredoc(t_shell_data *shell, char *str)
{
	char	*line;

	(void)shell;
	line = str;
	return (line);
}

// static void	sigint_handle(void)
// {
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

void	redirect_input_heredoc(t_shell_data *shell, const char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	char	*parsed_line;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe failed"));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			// free(line);
			break ;
		}
		parsed_line = parse_heredoc(shell, line);
		ft_putstr_fd(parsed_line, pipe_fd[1]);
		ft_putchar_fd('\n', pipe_fd[1]);
		free(line);
		// free(parsed_line);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 failed"));
	shell->heredoc_launched = true;
	close(pipe_fd[0]);
}
