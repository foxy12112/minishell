/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:03:07 by macbook           #+#    #+#             */
/*   Updated: 2025/01/11 04:05:21 by auplisas         ###   ########.fr       */
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

// void	redirect_input_heredoc(t_shell_data *shell, const char *delimiter)
// {
// 	int		pipe_fd[2];
// 	char	*line;
// 	char	*parsed_line;

// 	if (pipe(pipe_fd) == -1)
// 		return (perror("pipe failed"));
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		parsed_line = parse_heredoc(shell, line);
// 		ft_putstr_fd(parsed_line, pipe_fd[1]);
// 		ft_putchar_fd('\n', pipe_fd[1]);
// 		free(line);
// 	}
// 	close(pipe_fd[1]);
// 	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// 		return (perror("dup2 failed"));
// 	shell->heredoc_launched = true;
// 	close(pipe_fd[0]);
// }

void redirect_input_heredoc(t_shell_data *shell, const char *delimiter)
{
    int pipe_fd[2];
    char *line;
    char *parsed_line;
    int saved_stdin;

    saved_stdin = dup(STDIN_FILENO);
    if (saved_stdin == -1)
    {
        perror("dup failed to save stdin");
        return;
    }

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe failed");
        close(saved_stdin);
        return;
    }

    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        parsed_line = parse_heredoc(shell, line);
        ft_putstr_fd(parsed_line, pipe_fd[1]);
        ft_putchar_fd('\n', pipe_fd[1]);
        free(line);
    }

    close(pipe_fd[1]);

    if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
    {
        perror("dup2 failed to redirect stdin to pipe");
        close(pipe_fd[0]);
        close(saved_stdin);
        return;
    }
    shell->heredoc_launched = true;
    close(pipe_fd[0]);

    redirect_output(shell, "output.txt");
	launch_single_command(shell, shell->pipe_list->cmd->command);
    if (dup2(saved_stdin, STDIN_FILENO) == -1)
    {
        perror("dup2 failed to restore stdin");
    }
    close(saved_stdin);

}
