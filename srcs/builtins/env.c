/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:09 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/16 12:32:11 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_env(t_shell_data *shell)
{
	print_env_list(shell->env);
	return (0);
}

int	parse_launch_env(t_shell_data *shell, char **command)
{
	int	args_count;

	args_count = 0;
	while (command[args_count])
		args_count++;
	if (args_count > 1)
	{
		perror("Too many arguments");
		return (1);
	}
	ft_env(shell);
	return (0);
}
