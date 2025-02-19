/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 04:23:30 by macbook           #+#    #+#             */
/*   Updated: 2025/01/14 23:26:54 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_simple_cmd(t_shell_data *shell, char *command, int *i)
{
	char	*cmd;
	char	*cmd_parsed;
	char	**cmd_array;
	char	**expanded_cmd_array;

	while (command[*i])
	{
		if ((command[*i] == '>' || command[*i] == '<') && !quote_check(command,
				(*i)))
		{
			break ;
		}
		(*i)++;
	}
	cmd = ft_substr(command, 0, *i);
	cmd_parsed = ft_trim_whitespaces(cmd);
	cmd_array = ft_split_quotes(cmd_parsed, ' ');
	free(cmd);
	free(cmd_parsed);
	(void)shell;
	(void)expanded_cmd_array;
	expanded_cmd_array = expand_command(shell, cmd_array);
	free_string_array(cmd_array);
	return (expanded_cmd_array);
}

t_var_cmd	*parse_command(t_shell_data *shell, char *command)
{
	t_var_cmd	*cmd_node;
	int			i;

	i = 0;
	cmd_node = (t_var_cmd *)malloc(sizeof(t_var_cmd));
	if (!cmd_node)
		return (NULL);
	cmd_node->command = get_simple_cmd(shell, command, &i);
	cmd_node->redirect_count = 0;
	cmd_node->redirects = NULL;
	cmd_node->hd_file_name = NULL;
	parse_redirects(cmd_node, command, &i);
	cmd_node->next = NULL;
	cmd_node->prev = NULL;
	return (cmd_node);
}
