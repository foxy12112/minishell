/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:31:29 by macbook           #+#    #+#             */
/*   Updated: 2025/01/12 18:14:56 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_redirects(t_redirects *redirect)
{
	while (redirect)
	{
		// printf("\tRedirect Type: %d\n", redirect->redirect_type);
		// printf("\tFilename: %s\n", redirect->filename);
		// printf("\tDelimiter: %s\n", redirect->delimiter);
		// printf("\n");
		if(redirect->redirect_type == 0)
		{
			return (printf("minishell: syntax error near unexpected token \n"),
				false);		
		}
		if (!redirect->filename && !redirect->delimiter)
		{
			return (printf("minishell: syntax error near unexpected token \n"),
				false);
		}
		if ((!redirect->filename && ft_strlen(redirect->delimiter) == 0)
			|| (!redirect->delimiter && ft_strlen(redirect->filename) == 0))
		{
			return (printf("minishell: syntax error near unexpected token \n"),
				false);
		}
		redirect = redirect->next;
	}
	return (true);
}

bool	check_single_command(t_var_cmd *cmd)
{
	while (cmd)
	{
		// printf("Command:");
		// print_arofars(cmd->command);
		// printf("\n");
		// printf("Redirect Count: %d\n", cmd->redirect_count);
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