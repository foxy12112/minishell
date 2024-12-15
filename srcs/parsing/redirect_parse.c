/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 04:10:09 by macbook           #+#    #+#             */
/*   Updated: 2024/12/15 14:08:59 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirects	*create_redirect_node(char *redirect)
{
	t_redirect_type	redirect_type;
	char			*filename_delimiter;
	t_redirects		*new_redirect;

	redirect_type = select_redirect_type(redirect);
	filename_delimiter = get_filename_delimiter(redirect_type, redirect);
	new_redirect = (t_redirects *)malloc(sizeof(t_redirects));
	if (!new_redirect)
		return (NULL);
	new_redirect->redirect_type = redirect_type;
	if (redirect_type == 4)
	{
		new_redirect->filename = NULL;
		new_redirect->delimiter = filename_delimiter;
	}
	else
	{
		new_redirect->filename = filename_delimiter;
		new_redirect->delimiter = NULL;
	}
	new_redirect->next = NULL;
	new_redirect->prev = NULL;
	return (new_redirect);
}

void	add_redirect_to_cmd_node(t_var_cmd *cmd_node, t_redirects *new_redirect)
{
	t_redirects	*current;

	if (!cmd_node->redirects)
	{
		cmd_node->redirects = new_redirect;
	}
	else
	{
		current = cmd_node->redirects;
		while (current->next)
			current = current->next;
		current->next = new_redirect;
		new_redirect->prev = current;
	}
	cmd_node->redirect_count++;
}

void	assign_redirects(t_var_cmd *cmd_node, char *redirect)
{
	t_redirects	*new_redirect;

	new_redirect = create_redirect_node(redirect);
	if (!new_redirect)
		return ;
	add_redirect_to_cmd_node(cmd_node, new_redirect);
}

void	parse_redirects(t_var_cmd *cmd_node, char *command, int *i)
{
	char	*redirect;
	char	*redirects_parsed;
	int		j;

	j = *i;
	while (command[*i] && command[*i] == command[(*i) + 1])
		(*i)++;
	while (command[*i])
	{
		(*i)++;
		if (command[*i] == '>' || command[*i] == '<' || command[*i] == '\0')
		{
			redirect = ft_substr(command, j, *i - j);
			redirects_parsed = ft_trim_whitespaces(redirect);
			assign_redirects(cmd_node, redirects_parsed);
			free(redirects_parsed);
			free(redirect);
			j = *i;
			while (command[*i] && command[*i] == command[(*i) + 1])
				(*i)++;
		}
	}
}

// void parse_redirects(t_var_cmd *cmd_node, char *command, int *i)
// {
//     char    *redirect;
//     char    *redirects_parsed;
//     int     j;

//     j = *i;

//     // Ensure no out-of-bounds access for consecutive characters
//     while (command[*i] && command[*i] == command[(*i) + 1])
//         (*i)++;
    
//     while (command[*i])
//     {
//         (*i)++;
//         // Check bounds before accessing `command[(*i) + 1]`
//         if (command[*i] == '>' || command[*i] == '<' || command[*i] == '\0')
//         {
//             redirect = ft_substr(command, j, *i - j); // Extract the substring
//             redirects_parsed = ft_trim_whitespaces(redirect); // Trim whitespace
//             assign_redirects(cmd_node, redirects_parsed); // Assign parsed redirects
            
//             // Free allocated memory
//             free(redirects_parsed);
//             free(redirect);

//             j = *i;

//             // Ensure no out-of-bounds access for consecutive characters
//             while (command[*i] && command[*i] == command[(*i) + 1])
//                 (*i)++;
//         }
//     }
// }