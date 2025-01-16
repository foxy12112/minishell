/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_linked_lists.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:55:18 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/16 21:21:57 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_list(t_env_list *head)
{
	t_env_list	*temp;

	while (head != NULL)
	{
		temp = head->next;
		if (head->key)
			free(head->key);
		if (head->value)
			free(head->value);
		free(head);
		head = temp;
	}
}

void	free_redirects(t_redirects *redirect)
{
	t_redirects	*temp;

	while (redirect)
	{
		temp = redirect->next;
		if (redirect->filename)
			free(redirect->filename);
		if (redirect->delimiter)
			free(redirect->delimiter);
		free(redirect);
		redirect = temp;
	}
}

void	free_commands(t_var_cmd *cmd)
{
	t_var_cmd	*temp;

	while (cmd)
	{
		temp = cmd;
		if (cmd->command)
			free_string_array(cmd->command);
		if (cmd->hd_file_name)
			free(cmd->hd_file_name);
		if (cmd->redirects)
			free_redirects(cmd->redirects);
		cmd = cmd->next;
		free(temp);
	}
}

void	free_var_pipe_list(t_var_pipe_list *head)
{
	t_var_pipe_list	*current;
	t_var_pipe_list	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_commands(current->cmd);
		free(current);
		current = next;
	}
}
