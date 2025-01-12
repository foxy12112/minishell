/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoctest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:58:57 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/12 08:20:58 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_fd_heredoc(t_shell_data *shell, int pipe_fd[2], t_var_cmd *cmd)
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

// while (line && ft_strncmp(heredoc->delimiter, line,ft_strlen(heredoc->delimiter))
// 	&& !g_global.stop_heredoc)
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

int	ft_heredoc(t_shell_data *shell, t_redirects *heredoc, char *file_name)
{
	int	sl;

	sl = EXIT_SUCCESS;
	sl = create_heredoc(heredoc, shell, file_name);
	shell->heredoc_launched = true;
	return (sl);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_shell_data *shell, t_var_cmd *cmd)
{
	t_redirects	*start;
	int			sl;

	start = cmd->redirects;
	sl = EXIT_SUCCESS;
	while (cmd->redirects)
	{
		if (cmd->redirects->redirect_type == OP_HEREDOC)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_filename();
			sl = ft_heredoc(shell, cmd->redirects, cmd->hd_file_name);
			if (sl)
			{
				return (cleanup(shell), 1);
			}
		}
		cmd->redirects = cmd->redirects->next;
	}
	cmd->redirects = start;
	return (EXIT_SUCCESS);
}

int	handle_infile(t_shell_data *shell, char *file)
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