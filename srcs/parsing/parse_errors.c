/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:31:29 by macbook           #+#    #+#             */
/*   Updated: 2025/01/16 07:59:32 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

bool	check_redirects(t_redirects *redirect)
{
	while (redirect)
	{
		if (redirect->redirect_type == 0)
		{
			return (ft_putstr_fd("minishell: syntax error near unexpected token \n",
					STDERR_FILENO), false);
		}
		if (!redirect->filename && !redirect->delimiter)
		{
			return (ft_putstr_fd("minishell: syntax error near unexpected token \n",
					STDERR_FILENO), false);
		}
		if ((!redirect->filename && ft_strlen(redirect->delimiter) == 0)
			|| (!redirect->delimiter && ft_strlen(redirect->filename) == 0))
		{
			return (ft_putstr_fd("minishell: syntax error near unexpected token \n",
					STDERR_FILENO), false);
		}
		redirect = redirect->next;
	}
	return (true);
}

// int	check_redirects(t_redirects *redirect)
// {
// 	while (redirect)
// 	{
// 		if (redirect->redirect_type == 0)
// 		{
// 			return (ft_putstr_fd("minishell: syntax error near unexpected token \n",
// 					STDERR_FILENO), 2);
// 		}
// 		if (!redirect->filename && !redirect->delimiter)
// 		{
// 			return (ft_putstr_fd("minishell: syntax error near unexpected token \n",
// 					STDERR_FILENO), 2);
// 		}
// 		if ((!redirect->filename && ft_strlen(redirect->delimiter) == 0)
// 			|| (!redirect->delimiter && ft_strlen(redirect->filename) == 0))
// 		{
// 			return (ft_putstr_fd("minishell: syntax error near unexpected token \n",
// 					STDERR_FILENO), 2);
// 		}
// 		redirect = redirect->next;
// 	}
// 	return (0);
// }

bool	check_single_command(t_var_cmd *cmd)
{
	while (cmd)
	{
		if (args_length(cmd->command) < 1)
		{
			return (ft_putstr_fd("minishell: syntax error near unexpected token \n",
					STDERR_FILENO), false);
		}
		if (cmd->redirects)
		{
			if (!check_redirects(cmd->redirects))
			{
				return (false);
			}
		}
		cmd = cmd->next;
	}
	return (true);
}

bool	check_for_parse_errors(t_var_pipe_list *pipe_list)
{
	while (pipe_list)
	{
		if (pipe_list->cmd)
		{
			if (!check_single_command(pipe_list->cmd))
			{
				return (false);
			}
		}
		pipe_list = pipe_list->next;
	}
	return (true);
}

// int	check_single_command(t_var_cmd *cmd)
// {
// 	while (cmd)
// 	{
// 		if (cmd->redirects)
// 		{
// 			if (!check_redirects(cmd->redirects))
// 			{
// 				return (2);
// 			}
// 		}
// 		cmd = cmd->next;
// 	}
// 	return (0);
// }

// bool	check_for_parse_errors(t_var_pipe_list *pipe_list)
// {
// 	while (pipe_list)
// 	{
// 		if (pipe_list->cmd)
// 		{
// 			if (!check_single_command(pipe_list->cmd))
// 			{
// 				return (2);
// 			}
// 		}
// 		pipe_list = pipe_list->next;
// 	}
// 	return (0);
// }