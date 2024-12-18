/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 04:29:58 by macbook           #+#    #+#             */
/*   Updated: 2024/12/18 18:20:12 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipe_list_length(t_var_pipe_list *head)
{
	int				count;
	t_var_pipe_list	*current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	add_to_pipelist(t_shell_data *shell, char *command)
{
	t_var_pipe_list	*new_node;
	t_var_pipe_list	*current;

	new_node = (t_var_pipe_list *)malloc(sizeof(t_var_pipe_list));
	if (!new_node)
		return (-1);
	new_node->cmd = parse_command(command);
	if (!new_node->cmd)
		return (free(new_node), (-1));
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
	if (commands == NULL)
		return (ft_putchar_fd('\n', 1), 1);
	pipe_splitted = ft_split_quotes(commands, '|');
	if (!pipe_splitted)
		return (-1);
	while (pipe_splitted[i])
	{
		add_to_pipelist(shell, pipe_splitted[i]);
		i++;
	}
	shell->pipes_count = count_pipe_list_length(shell->pipe_list) - 1;
	free_string_array(pipe_splitted);
	return (0);
}

//This function is launched after everything is parsed
//It iterates and sorts redirects as HEREDOC always needs to be launched first
void	process_pipe_list(t_var_pipe_list *pipe_list)
{
	t_var_pipe_list	*current_pipe;
	t_redirects		**redirects;

	current_pipe = pipe_list;
	while (current_pipe)
	{
		if (current_pipe->cmd)
		{
			redirects = &current_pipe->cmd->redirects;
			sort_redirects(redirects);
		}
		current_pipe = current_pipe->next;
	}
}
