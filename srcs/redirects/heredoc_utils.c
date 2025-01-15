/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:58:57 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/14 21:06:11 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_heredoc_line(t_shell_data *shell, char *line)
{
	char	**splitted_line;
	char	*expanded_line;

	splitted_line = ft_split_delimiters(line, &is_delimiter);
	expand_single_arg(shell, splitted_line);
	expanded_line = join_subarrays(splitted_line);
	free(line);
	free_string_array(splitted_line);
	return (expanded_line);
}

char	*remove_heredoc_quotes(char *line)
{
	char	**splitted_line;
	char	*unquoted_line;

	splitted_line = ft_split_delimiters(line, &is_delimiter);
	remove_quotes(splitted_line);
	unquoted_line = join_subarrays(splitted_line);
	free(line);
	free_string_array(splitted_line);
	return (unquoted_line);
}

void	remove_char(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

char	*generate_heredoc_file(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.heredoc_", num);
	free(num);
	return (file_name);
}
