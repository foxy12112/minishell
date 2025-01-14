/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:03:07 by macbook           #+#    #+#             */
/*   Updated: 2025/01/14 14:46:57 by ldick            ###   ########.fr       */
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

static void	custom_handler(int signal)
{
	(void)signal;
	printf("\n");
	exit(130);
}

static char	*save_heredoc(char *delimiter)
{
	char	*tmp;
	char	*line;

	line = ft_strdup("");
	signal(SIGINT, custom_handler);
	while(1)
	{
		tmp = readline("heredoc> ");
		if (tmp == NULL)
			return(NULL);
		if (!ft_strncmp(delimiter, tmp, ft_strlen(delimiter)) || tmp == NULL)
			break ;
		line = ft_strjoin(line, tmp);
		free (tmp);
	}
	free (tmp);
	return (line);
}


// void	redirect_input_heredoc(t_shell_data *shell, const char *delimiter)
// {
// 	int		pipe_fd[2];
// 	char	*line;
// 	char	*parsed_line;
// 	// char	*heredoc;

// 	if (pipe(pipe_fd) == -1)
// 		return ;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		parsed_line = parse_heredoc(shell, line);
// 		// heredoc = save_heredoc(heredoc, parsed_line);
// 		// ft_putstr_fd(parsed_line, pipe_fd[1]);
// 		// ft_putchar_fd('\n', pipe_fd[1]);
// 		free(line);
// 		// free(parsed_line);
// 	}
// 	// ft_putstr_fd(heredoc, STDOUT_FILENO);
// 	close(pipe_fd[1]);
// 	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// 		return (perror("dup2 failed"));
// 	shell->heredoc_launched = true;
// 	close(pipe_fd[0]);
// }

void	redirect_input_heredoc(t_shell_data *shell, char *delmiter)
{
	int		pipe_fd[2];
	char	*ret;

	(void)shell;
	if (pipe(pipe_fd) == -1)
		return ;
	ret = save_heredoc(delmiter);
	printf("%s\n", ret);
	add_history(ret);
	add_permanent_history(ret);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 failed"));
	free(ret);
	shell->heredoc_launched = true;
	close(pipe_fd[0]);
}
