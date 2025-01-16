/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:31:29 by macbook           #+#    #+#             */
/*   Updated: 2025/01/16 21:01:33 by auplisas         ###   ########.fr       */
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
			ft_putstr_fd("minishell: syntax error near unexpected token \n",
				STDERR_FILENO);
			return (false);
		}
		if (!redirect->filename && !redirect->delimiter)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token \n",
				STDERR_FILENO);
			return (false);
		}
		if ((!redirect->filename && ft_strlen(redirect->delimiter) == 0)
			|| (!redirect->delimiter && ft_strlen(redirect->filename) == 0))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token \n",
				STDERR_FILENO);
			return (false);
		}
		redirect = redirect->next;
	}
	return (true);
}

bool	check_single_command(t_var_cmd *cmd)
{
	while (cmd)
	{
		if (args_length(cmd->command) < 1)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token \n",
				STDERR_FILENO);
			return (false);
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
