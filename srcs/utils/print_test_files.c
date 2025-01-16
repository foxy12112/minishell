/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:44:47 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/16 16:45:13 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_redirects(t_redirects *redirect)
{
	printf("Printing Redirects:\n");
	while (redirect)
	{
		printf("\tRedirect Type: %d\n", redirect->redirect_type);
		printf("\tFilename: %s\n", redirect->filename);
		printf("\tDelimiter: %s\n", redirect->delimiter);
		printf("\n");
		redirect = redirect->next;
	}
}

void	print_arofars(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("[%s]", str[i]);
		i++;
	}
	printf("\n");
}

void	print_commands(t_var_cmd *cmd)
{
	while (cmd)
	{
		printf("Command:");
		print_arofars(cmd->command);
		printf("\n");
		printf("Redirect Count: %d\n", cmd->redirect_count);
		if (cmd->redirects)
		{
			print_redirects(cmd->redirects);
		}
		cmd = cmd->next;
	}
}

void	print_pipe_list(t_var_pipe_list *pipe_list)
{
	while (pipe_list)
	{
		if (pipe_list->cmd)
		{
			print_commands(pipe_list->cmd);
		}
		else
		{
			printf("No commands in this pipe.\n");
		}
		printf("\n\n");
		pipe_list = pipe_list->next;
	}
}
