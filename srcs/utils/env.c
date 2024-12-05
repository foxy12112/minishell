/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 02:20:43 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/05 05:08:12 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	print_env_list(t_env_list *variables)
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
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

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

t_env_list	*initialize_env(void)
{
	t_env_list	*variables;
	char		**env;
	char		**key_value;
	int			i;
	int			j;

	env = environ;
	i = 0;
	variables = NULL;
	while (env[i])
	{
		j = 0;
		key_value = ft_split(env[i], '=');
		add_to_variables_list(&variables, key_value);
		free_key_value(key_value);
		i++;
	}
	return (variables);
}
