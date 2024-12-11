/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:08:24 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/11 09:56:13 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_key_value(char **key_value)
{
	int	i;

	i = 0;
	while (key_value[i])
	{
		free(key_value[i]);
		i++;
	}
	free(key_value);
}

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

void	free_char_string(char **str)
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

void	free_heredoc_list(t_heredoc_list **head)
{
	t_heredoc_list	*current;
	t_heredoc_list	*temp;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		temp = current->next;
		free(current->word);
		free(current);
		current = temp;
	}
	*head = NULL;
}