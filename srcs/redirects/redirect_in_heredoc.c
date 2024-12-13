/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:03:07 by macbook           #+#    #+#             */
/*   Updated: 2024/12/13 07:57:18 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_to_heredoc_list(t_shell_data *shell, t_heredoc_list **head,
		char *word)
{
	t_heredoc_list	*new_node;
	t_heredoc_list	*temp;

	if (!head)
		return ;
	if (word[0] == '$')
		new_node = handle_variable_node(shell, word);
	else
		new_node = create_heredoc_node(word);
	if (!new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
}

char	*create_sentence(t_heredoc_list **head)
{
	t_heredoc_list	*current;
	char			*sentence;
	int				index;
	int				len;

	current = *head;
	index = 0;
	sentence = (char *)malloc(sizeof(char) * (count_line_size(head) + 1));
	if (!sentence)
		return (NULL);
	while (current)
	{
		if (current->word)
		{
			len = ft_strlen(current->word);
			ft_memcpy(&sentence[index], current->word, len);
			index += len;
		}
		if (current->next)
			sentence[index++] = ' ';
		current = current->next;
	}
	sentence[index] = '\0';
	return (sentence);
}

char	*parse_heredoc(t_shell_data *shell, char *str)
{
	char			**words;
	t_heredoc_list	*words_list;
	char			*line;
	int				i;

	words = ft_split(str, ' ');
	words_list = NULL;
	i = 0;
	if (!words)
		return (NULL);
	while (words[i])
		add_to_heredoc_list(shell, &words_list, words[i++]);
	line = create_sentence(&words_list);
	free_heredoc_list(&words_list);
	free_char_string(words);
	return (line);
}

void	redirect_input_heredoc(t_shell_data *shell, const char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	char	*parsed_line;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe failed"), exit(EXIT_FAILURE));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		parsed_line = parse_heredoc(shell, line);
		ft_putstr_fd(parsed_line, pipe_fd[1]);
		ft_putchar_fd('\n', pipe_fd[1]);
		free(line);
		free(parsed_line);
	}
	close(pipe_fd[1]);
	if(isatty(STDIN_FILENO))
	{
		printf("OWOWOW\n");
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 failed"), exit(EXIT_FAILURE));
	close(pipe_fd[0]);
}
