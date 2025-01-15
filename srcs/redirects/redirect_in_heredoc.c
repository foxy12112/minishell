/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:03:07 by macbook           #+#    #+#             */
/*   Updated: 2025/01/15 03:46:36 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	reset_heredoc_fd(t_shell_data *shell, int pipe_fd[2], t_var_cmd *cmd)
{
	int	fd_in;

	if (shell->heredoc_launched)
	{
		close(pipe_fd[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = pipe_fd[0];
	return (fd_in);
}

// int	reset_heredoc_fd(t_shell_data *shell, int pipe_fd[2], t_var_cmd *cmd)
// {
// 	int	fd_in;

// 	if (shell->heredoc_launched)
// 	{
// 		close(pipe_fd[0]);
// 		if (cmd->hd_file_name != NULL) // Check for NULL
// 		{
// 			fd_in = open(cmd->hd_file_name, O_RDONLY);
// 			if (fd_in == -1)
// 			{
// 				perror("Error opening heredoc file");
// 				return (-1); // Handle error properly
// 			}
// 		}
// 		else
// 		{
// 			return (-1); // Handle error properly
// 		}
// 	}
// 	else
// 	{
// 		fd_in = pipe_fd[0];
// 	}
// 	return (fd_in);
// }

int	create_heredoc(t_redirects *heredoc, t_shell_data *shell, char *file_name)
{
	int		fd;
	char	*line;

	(void)shell;
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("> ");
	while (1)
	{
		if (!line || ft_strcmp(line, heredoc->delimiter) == 0)
		{
			free(line);
			break ;
		}
		line = expand_heredoc_line(shell, line);
		line = remove_heredoc_quotes(line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (!line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	parse_and_create_heredoc(t_shell_data *shell, t_redirects *heredoc,
		char *file_name)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	remove_char(heredoc->delimiter, '\"');
	remove_char(heredoc->delimiter, '\'');
	exit_code = create_heredoc(heredoc, shell, file_name);
	shell->heredoc_launched = true;
	// shell->inside_heredoc = false;
	shell->last_exit_code = exit_code;
	return (exit_code);
}

int	prepare_heredoc(t_shell_data *shell, t_var_cmd *cmd)
{
	t_redirects	*start;

	start = cmd->redirects;
	shell->last_exit_code = EXIT_SUCCESS;
	while (cmd->redirects)
	{
		if (cmd->redirects->redirect_type == OP_HEREDOC)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_file();
			shell->last_exit_code = parse_and_create_heredoc(shell,
					cmd->redirects, cmd->hd_file_name);
			if (shell->last_exit_code)
			{
				return (cleanup(shell), 1);
			}
		}
		cmd->redirects = cmd->redirects->next;
	}
	cmd->redirects = start;
	return (EXIT_SUCCESS);
}

int	redirect_heredoc_launch(t_shell_data *shell, char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	(void)shell;
	return (EXIT_SUCCESS);
}