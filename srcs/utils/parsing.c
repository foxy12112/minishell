/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:53:04 by ldick             #+#    #+#             */
/*   Updated: 2024/12/22 12:16:13 by ldick            ###   ########.fr       */
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

static void	insert_word(char *original, char *word, int pos, char *result)
{
	int	origin_len;
	int	word_len;

	origin_len = ft_strlen(original);
	if (word == NULL)
		word = "";
	word_len = ft_strlen(word);
	ft_strncpy(result, original, pos);
	result[pos] = '\0';
	ft_strcat(result, word);
	result[pos + word_len] = '\0';
}

// static int	var_double_quotes(const char *str, int dollar_pos)
// {
// 	int	i;
// 	int	double_quote_count;
// 	int	single_quote_count;

// 	i = 0;
// 	double_quote_count = 0;
// 	single_quote_count = 0;
// 	while (i < dollar_pos)
// 	{
// 		if (str[i] == '"' && single_quote_count % 2 == 0)
// 			double_quote_count++;
// 		else if (str[i] == '\'' && double_quote_count % 2 == 0)
// 			single_quote_count++;
// 		i++;
// 	}
// 	return (double_quote_count % 2 == 1);
// }

static char	*replace_var_expanded(t_shell_data *shell, char *var, char *input,
		int i)
{
	char	*expanded;

	expanded = malloc((sizeof(char) * ft_strlen(input)
				+ ft_strlen(retrieve_variable(shell, var))));
	// if (!var_double_quotes(input, i))
	if (ft_strcmp(var, "$?") == 0)
		insert_word(input, ft_itoa(shell->last_exit), i, expanded);
	else
		insert_word(input, retrieve_variable(shell, var), i, expanded);
	return (expanded);
}

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
			j = 0;
			input = replace_var_expanded(shell, var, input, i - ft_strlen(var));
			ft_bzero(var, ft_strlen(var));
		}
		i++;
	}
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
