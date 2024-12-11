/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:04 by ldick             #+#    #+#             */
/*   Updated: 2024/12/11 17:01:27 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_history(void)
{
	int		fd;
	int		i;
	int		j;
	char	buffer[7000];
	char	tmp[5000];

	i = 0;
	j = 0;
	fd= open(".git/permanent_history/history.log" , O_RDONLY);
	read(fd, buffer, 7000);
	if (fd != -1)
	{
		while(buffer[i])
		{
			if (buffer[i + 1] == '\n')
			{
				j = 0;
				add_history(tmp);
			}
			tmp[j] = buffer[i];
			i++;
			j++;
		}
	}
}

void	add_permanent_history(char *str)
{
	int fd;
	char *file;

	file = ".git/permanent_history/history.log";
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}

char	**ft_tokenize(char *input)
{
	char	**token_stack;

	token_stack = ft_split(input, ' ');
	return (token_stack);
}

static char	ft_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	possible_var(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void	print_two_d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

static int	check_var(char *input)
{
	int	i;

	i = 0;
	while(input[i])
	{
		if (!input[i])
			break ;
		if (input[i] == '=' && ft_is_whitespace(input[i + 1]))
			return (3);
		else if (input[i + 1] == '"' || input[i + 1] == '\'')
		{
			i++;
			i++;
			while(input[i])
			{
				if (input[i] == '"' || input[i] == '\'')
					return (1);
				i++;
			}
		}
		else if (input[i + 1] && !ft_is_whitespace(input[i + 1]))
		{
			i++;
			i++;
			while(input[i])
			{
				if (ft_is_whitespace(input[i]))
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

static int		is_valid_var(char *input)
{
	int		i;
	int		j;
	char	*check;
	char	*tmp;

	i = 0;
	j = 0;
	while(input[i])
	{
		printf("%d\n", i);
		if (input[i] == '=' && input[i + 1])
		{
			i--;
			if (ft_is_whitespace(input[i]))
			{
				while(input[i] && ft_is_whitespace(input[i]))
					i--;
				while(input[i] && !ft_is_whitespace(input[i]))
					i--;
				while(!ft_is_whitespace(input[i]) && input[i])
				{
					tmp[j] = input[i];
					i++;
					j++;
				}
				return (printf("%s: command not found\n", tmp), 1);
			}
		}
		i++;
	}
	return (0);
}

void	display(void)
{
	char	*input;
	char	**token_stack;
	char	**variables;
	int		i;

	i = 0;
	while (1)
	{
		input = readline("waiting for input:");
		add_permanent_history(input);
		add_history("ji");
		rl_on_new_line();
		if (!ft_strncmp(input, "exit", 5))
			break ;
		if (setup_signals() >= 2)
			continue ;
		// if (possible_var(input))
		// {
		// 	if (check_var(input))
		// 		printf("is variable\n");
		// }
		is_valid_var(input);
		// token_stack = ft_tokenize(input);
		// print_two_d(token_stack);
		free(input);
	}
	rl_clear_history();
}
