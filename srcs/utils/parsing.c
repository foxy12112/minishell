/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:04 by ldick             #+#    #+#             */
/*   Updated: 2024/12/19 17:48:50 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_history(void)
{
	int		fd;
	char	*line;

	fd = open(".git/permanent_history/history.log", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		line = NULL;
	}
	close(fd);
}

void	add_permanent_history(char *str)
{
	int		fd;
	char	*file;

	file = ".git/permanent_history/history.log";
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*str == '\0')
	{
		ft_putchar_fd('\n', fd);
		close(fd);
		return ;
	}
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

// static char	*replace_var_expanded(t_shell_data *shell, char *var, char *input,
// 		int i)
// {
// 	char	*expanded;
// 	int		j;

// 	(void)shell;
// 	(void)var;
// 	expanded = ft_strdup(input);
// 	while(!ft_is_whitespace(expanded[i]))
// 	{
// 		expanded[i] = retrieve_variable(shell, var)
// 	}
// 	input[i] = '0';
// 	printf("%s\n", input);
// 	return input;
// }

static char	*ft_expand_variables(t_shell_data *shell, char *input)
{
	int		i;
	int		sing_quote;
	char	var[7000];
	int		j;

	j = 0;
	i = 0;
	(void)shell;
	sing_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			sing_quote++;
		if (input[i] == '$' && sing_quote % 2 == 0)
		{
			while (!ft_is_whitespace(input[i]) && input[i])
			{
				var[j] = input[i];
				i++;
				j++;
			}
			var[j] = '\0';
			// replace_var_expanded(shell, var, input, i - ft_strlen(var));
		}
		i++;
	}
	// printf("%s\n", var);
	return (input);
}

void	display(t_shell_data *shell)
{
	char	*input;

	disable_control_echo(shell);
	setup_signals();
	while (1)
	{
		input = readline("waiting for input:");
		if (input == NULL)
		{
			printf("%s", CTRL_D);
			break ;
		}
		if (*input == '\0')
			continue ;
		add_permanent_history(input);
		add_history(input);
		input = ft_expand_variables(shell, input);
		parse_readline(shell, input);
		execute_script(shell);
		free(input);
	}
	restore_control_echo(shell);
	rl_clear_history();
}
