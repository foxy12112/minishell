/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:08:24 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/16 13:19:12 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_list(t_env_list *head)
{
	t_env_list	*temp;

	while (head != NULL)
	{
		temp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = temp;
	}
}

void	free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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
		free_string_array(cmd->command);
		if (cmd->redirects)
		{
			free_redirects(cmd->redirects);
		}
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

char	**free_all(char **parentarray, int arrayindex)
{
	int	j;

	j = 0;
	while (j < arrayindex)
	{
		free(parentarray[j]);
		j++;
	}
	free(parentarray);
	return (NULL);
}
