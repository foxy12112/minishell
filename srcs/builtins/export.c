/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:17 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/06 03:40:39 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	swap_nodes(t_env_list *a, t_env_list *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	sort_env_list(t_env_list *head)
{
	int swapped;
	t_env_list *ptr1;
	t_env_list *ptr2 = NULL;

	if (head == NULL)
		return ;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;

		while (ptr1->next != ptr2)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		ptr2 = ptr1;
	}
}

int	ft_export(t_shell_data *shell, char **variables)
{
	int	i;

	i = 0;
	while (variables[i])
	{
		i++;
	}
	if (i < 1)
	{
        sort_env_list(shell->variables);
		print_variables_list(shell->variables);
	}
	else
	{
		add_variables(shell, variables);
		sort_env_list(shell->variables);
		free_char_string(variables);
	}
	return (0);
}