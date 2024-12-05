/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:08:24 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/05 16:47:28 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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