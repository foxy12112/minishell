/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:09 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/13 03:43:23 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_env_list(t_env_list *variables)
{
	t_env_list	*current;

	if (!variables)
	{
		printf("List is empty.\n");
		return (1);
	}
	current = variables->next;
	while (current != NULL)
	{
		if (!current->key || !current->value)
		{
			printf("Invalid entry in the list.\n");
			return (1);
		}
		if (printf("%s=%s\n", current->key, current->value) < 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_env(t_shell_data *shell)
{
	int	exit_code;

	exit_code = print_env_list(shell->env);
	return (exit_code);
}

int	parse_launch_env(t_shell_data *shell, char **command)
{
	int	args_count;

	args_count = 0;
	shell->last_exit_code = 0;
	while (command[args_count])
		args_count++;
	if (args_count > 1)
	{
		perror("Too many arguments");
		shell->last_exit_code = 1;
		return (shell->last_exit_code);
	}
	shell->last_exit_code = ft_env(shell);
	return (shell->last_exit_code);
}
