/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:21:21 by macbook           #+#    #+#             */
/*   Updated: 2025/01/11 20:21:09 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	setup_redirects(t_shell_data *shell, t_var_cmd *cmd, t_redirects *redirects)
{
	while (redirects)
	{
		if (redirects->redirect_type == OP_REDIRECT_IN)
			redirect_input(shell, redirects->filename);
		else if (redirects->redirect_type == OP_REDIRECT_OUT)
			redirect_output(shell, redirects->filename);
		else if (redirects->redirect_type == OP_APPEND_OUT)
			redirect_output_append(shell, redirects->filename);
		// else if (redirects->redirect_type == OP_HEREDOC)
		// 	redirect_input_heredoc(shell, redirects->delimiter);
		else if (redirects->redirect_type == OP_HEREDOC)
		{
			handle_infile(shell, cmd->hd_file_name);
		}
		else
		{
			perror("WRONG REDIRECT COMMAND");
			return (1);
		}
		redirects = redirects->next;
	}
	return (0);
}
