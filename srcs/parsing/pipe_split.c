/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 04:29:58 by macbook           #+#    #+#             */
/*   Updated: 2024/12/15 04:31:00 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_to_pipelist(t_shell_data *shell, char *command)
{
	t_var_pipe_list	*new_node;
	t_var_pipe_list	*current;

	new_node = (t_var_pipe_list *)malloc(sizeof(t_var_pipe_list));
	if (!new_node)
		return (-1);
	new_node->cmd = parse_command(command);
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!shell->pipe_list)
		shell->pipe_list = new_node;
	else
	{
		current = shell->pipe_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
	return (0);
}

int	parse_readline(t_shell_data *shell, char *commands)
{
	char	**pipe_splitted;
	int		i;

	i = 0;
	pipe_splitted = ft_split(commands, '|');
	if (!pipe_splitted)
		return (-1);
	while (pipe_splitted[i])
	{
		add_to_pipelist(shell, pipe_splitted[i]);
		i++;
	}
	shell->pipes_count = count_pipe_list_length(shell->pipe_list) - 1;
	free_char_string(pipe_splitted);
	return (0);
}