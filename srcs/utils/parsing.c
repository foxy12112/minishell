/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:04 by ldick             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/16 08:57:27 by ldick            ###   ########.fr       */
=======
/*   Updated: 2024/12/12 13:45:34 by macbook          ###   ########.fr       */
>>>>>>> d5679bfd0c6a2d9c688178af7d4ba644e2a22b8c
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_history(void)
{
	int		fd;
	char	*line;

	fd = open(".git/permanent_history/history.log" , O_RDONLY);
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		line = NULL;
	}
	close(fd);
}

<<<<<<< HEAD
void	add_permanent_history(char *str)
=======
char	ft_is_whitespace(char c)
>>>>>>> d5679bfd0c6a2d9c688178af7d4ba644e2a22b8c
{
	int fd;
	char *file;

	file = ".git/permanent_history/history.log";
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}

static char	ft_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

// static void	print_two_d(char **array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i])
// 	{
// 		printf("%s\n", array[i]);
// 		i++;
// 	}
// }

char	**tokenize(char *input)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;
	char	**ret;

	k = 0;
	j = 0;
	i = 0;
	while(input[i] && ft_is_whitespace(input[i]))
		i++;
	while(input[i])
	{
		if (input[i] == ' ')
		tmp[j] = input[i];
		i++;
		j++;
	}
}

// void	display(void)
// {
// 	char	*input;
// 	char	**token_stack;
// 	char	**variables;
// 	int		i;

	i = 0;
	while (1)
	{
		input = readline("waiting for input:");
		add_permanent_history(input);
		add_history(input);
		// rl_redisplay();
		if (!ft_strncmp(input, "exit", 5))
			break ;
		if (setup_signals() >= 2)
			continue ;
		token_stack = tokenize(input);
		print_two_d(token_stack);
		free(input);
	}
	rl_clear_history();
}
