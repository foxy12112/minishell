/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 02:20:43 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/10 10:51:33 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

t_env_list	*create_env_node(char **key_value)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key_value[0]);
	if (key_value[1])
	{
		new_node->value = ft_strdup(key_value[1]);
	}
	else
	{
		new_node->value = NULL;
	}
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_to_variables_list(t_env_list **head, char **key_value)
{
	t_env_list	*new_node;
	t_env_list	*temp;

	new_node = create_env_node(key_value);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
}

void	print_variables_list(t_env_list *variables)
{
	t_env_list	*current;

	if (!variables)
	{
		printf("List is empty.\n");
		return ;
	}
	current = variables->next;
	while (current != NULL)
	{
		printf("declare -x %s=%s\n", current->key, current->value);
		current = current->next;
	}
}

t_env_list	*initialize_env(void)
{
	t_env_list	*variables;
	char		**env;
	char		**key_value;
	int			i;

	env = environ;
	i = 0;
	variables = NULL;
	while (env[i])
	{
		key_value = ft_split(env[i], '=');
		add_to_variables_list(&variables, key_value);
		free_key_value(key_value);
		i++;
	}
	return (variables);
}
