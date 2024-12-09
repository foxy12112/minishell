/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_heredoc_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:34:41 by macbook           #+#    #+#             */
/*   Updated: 2024/12/09 03:02:59 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_line_size(t_heredoc_list **head)
{
	t_heredoc_list	*current;
	int				size;

	current = *head;
	size = 0;
	while (current)
	{
		if (current->word)
			size += ft_strlen(current->word);
		if (current->next)
			size++;
		current = current->next;
	}
	return (size);
}

t_heredoc_list	*create_heredoc_node(char *word)
{
	t_heredoc_list	*new_node;

	new_node = (t_heredoc_list *)malloc(sizeof(t_heredoc_list));
	if (!new_node)
		return (NULL);
	if (!word)
		new_node->word = ft_strdup("");
	else
		new_node->word = ft_strdup(word);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_heredoc_list	*handle_variable_node(t_shell_data *shell, char *word)
{
	t_heredoc_list	*new_node;
	char			*retrieved_variable;

	retrieved_variable = ft_strdup(word + 1);
	new_node = create_heredoc_node(retrieve_variable(shell,
				retrieved_variable));
	if (!new_node)
		return (NULL);
	free(retrieved_variable);
	return (new_node);
}
