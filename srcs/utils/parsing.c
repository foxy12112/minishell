/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:04 by ldick             #+#    #+#             */
/*   Updated: 2024/12/16 09:32:30 by ldick            ###   ########.fr       */
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

void	display(t_shell_data *shell)
{
	char	*input;
	int		i;

	i = 0;
	while (1)
	{
		input = readline("waiting for input:");
		add_permanent_history(input);
		add_history(input);
		// rl_redisplay();
		if (!ft_strncmp(input, "exit", 5))
			break ;
		parse_readline(shell, input);
		execute_script(shell);
		free(input);
	}
	rl_clear_history();
}
