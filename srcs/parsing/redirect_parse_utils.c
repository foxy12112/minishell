/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 05:46:42 by macbook           #+#    #+#             */
/*   Updated: 2025/01/16 15:35:41 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirect_type	select_redirect_type(char *redirect)
{
	int	i;

	i = 0;
	if (redirect[i] == '<')
	{
		while (redirect[i] == '<')
			i++;
		if (i == 1)
			return (OP_REDIRECT_IN);
		else if (i == 2)
			return (OP_HEREDOC);
	}
	else if (redirect[i] == '>')
	{
		while (redirect[i] == '>')
			i++;
		if (i == 1)
			return (OP_REDIRECT_OUT);
		else if (i == 2)
			return (OP_APPEND_OUT);
	}
	return (REDIR_FAIL);
}

char	*get_filename_delimiter(t_redirect_type redirect_type, char *redirect)
{
	int		i;
	char	*filename;
	char	*filename_parsed;
	char	**filename_split;
	int		redirect_length;

	i = 0;
	redirect_length = ft_strlen(redirect);
	if (redirect_type == OP_REDIRECT_IN || redirect_type == OP_REDIRECT_OUT)
		i = 1;
	else if (redirect_type == OP_HEREDOC || redirect_type == OP_APPEND_OUT)
		i = 2;
	filename = ft_substr(redirect, i, redirect_length - i);
	filename_parsed = ft_trim_whitespaces(filename);
	free(filename);
	filename_split = ft_split_delimiters(filename_parsed);
	free(filename_parsed);
	remove_quotes(filename_split);
	filename_parsed = join_subarrays(filename_split);
	free_string_array(filename_split);
	return (filename_parsed);
}

// char	*get_filename_delimiter(t_redirect_type redirect_type, char *redirect)
// {
// 	int		i;
// 	char	*filename;
// 	char	*filename_parsed;
// 	int		redirect_length;

// 	i = 0;
// 	redirect_length = ft_strlen(redirect);
// 	if (redirect_type == OP_REDIRECT_IN || redirect_type == OP_REDIRECT_OUT)
// 		i = 1;
// 	else if (redirect_type == OP_HEREDOC || redirect_type == OP_APPEND_OUT)
// 		i = 2;
// 	filename = ft_substr(redirect, i, redirect_length - i);
// 	filename_parsed = ft_trim_whitespaces(filename);
// 	free(filename);
// 	return (filename_parsed);
// }

void	move_heredoc_to_head(t_redirects **head, t_redirects *current)
{
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	current->next = *head;
	if (*head)
		(*head)->prev = current;
	current->prev = NULL;
	*head = current;
}

void	sort_redirects(t_redirects **redirects)
{
	t_redirects	*current;
	t_redirects	*head;
	t_redirects	*next;

	if (!redirects || !(*redirects))
		return ;
	current = *redirects;
	head = *redirects;
	while (current)
	{
		next = current->next;
		if (current->redirect_type == OP_HEREDOC && current != head)
		{
			move_heredoc_to_head(&head, current);
			*redirects = head;
		}
		current = next;
	}
}
