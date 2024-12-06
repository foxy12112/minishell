/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:23 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/06 02:40:06 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node_by_key(t_env_list **head, const char *key)
{
	t_env_list	*current;

	if (!head || !*head || !key)
		return ;
	current = *head;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			if (current == *head)
				*head = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		current = current->next;
	}
}

int	ft_unset(t_shell_data *shell, char *key)
{
	delete_node_by_key(&shell->variables, key);
	delete_node_by_key(&shell->env, key);
	return (0);
}