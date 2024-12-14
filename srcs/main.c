/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:32:25 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/14 06:27:24 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

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

void	assign_redirects(t_shell_data *shell, char *redirect)
{
	t_redirect_type	redirect_type;
	int				i;
	int				redirect_length;
	char			*filename;
	char			*filename_parsed;

	i = 0;
	(void)shell;
	redirect_type = select_redirect_type(redirect);
	redirect_length = ft_strlen(redirect);
	printf("Redir Type: %d\n", redirect_type);
	if (redirect_type == 1 || redirect_type == 2)
	{
		i = 1;
	}
	else if (redirect_type == 3)
	{
		i = 2;
	}
	else if (redirect_type == 4)
	{
		i = 2;
	}
	filename = ft_substr(redirect, i, redirect_length - i);
	filename_parsed = ft_trim_whitespaces(filename);
	free(filename);
	printf("Filename: %s\n\n", filename_parsed);
	free(filename_parsed);
}

void	parse_redirects(t_shell_data *shell, char *command, int *i)
{
	char	*redirect;
	char	*redirects_parsed;
	int		j;

	j = *i;
	(void)shell;
	while (command[*i] == command[(*i) + 1])
		(*i)++;
	while (command[*i])
	{
		(*i)++;
		if (command[*i] == '>' || command[*i] == '<' || command[*i] == '\0')
		{
			redirect = ft_substr(command, j, *i - j);
			redirects_parsed = ft_trim_whitespaces(redirect);
			assign_redirects(shell, redirects_parsed);
			free(redirects_parsed);
			free(redirect);
			j = *i;
			while (command[*i] == command[(*i) + 1])
				(*i)++;
		}
	}
}

char	*get_simple_cmd(t_shell_data *shell, char *command, int *i)
{
	char	*cmd;
	char	*cmd_parsed;

	(void)shell;
	while (command[*i])
	{
		if (command[*i] == '>' || command[*i] == '<')
		{
			break ;
		}
		(*i)++;
	}
	cmd = ft_substr(command, 0, *i);
	cmd_parsed = ft_trim_whitespaces(cmd);
	free(cmd);
	return (cmd_parsed);
}

int	parse_command(t_shell_data *shell, char *command)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = get_simple_cmd(shell, command, &i);
	printf("Command: %s\n", cmd);
	parse_redirects(shell, command, &i);
	free(cmd);
	return (0);
}

int	add_to_pipelist(t_shell_data *shell, char *command)
{
	t_var_pipe_list	*new_node;
	t_var_pipe_list	*current;

	new_node = (t_var_pipe_list *)malloc(sizeof(t_var_pipe_list));
	if (!new_node)
		return (-1);
	new_node->cmd = ft_trim_whitespaces(command);
	new_node->parsed_cmd = parse_command(shell, command);
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!shell->pipe_list)
		shell->pipe_list = new_node;
	else
	{
		current = shell->pipe_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
	return (0);
}

int	parse_readline(t_shell_data *shell, char *commands)
{
	char	**pipe_splitted;
	int		i;

	i = 0;
	pipe_splitted = ft_split(commands, '|');
	if (!pipe_splitted)
		return (-1);
	while (pipe_splitted[i])
	{
		add_to_pipelist(shell, pipe_splitted[i]);
		i++;
	}
	shell->pipes_count = count_pipe_list_length(shell->pipe_list) - 1;
	free_char_string(pipe_splitted);
	return (0);
}

void	print_cmd_list(t_shell_data *shell)
{
	t_var_pipe_list	*current;

	if (!shell || !shell->pipe_list)
	{
		printf("Pipe list is empty or shell is NULL.\n");
		return ;
	}
	current = shell->pipe_list;
	while (current)
	{
		printf("%s\n", current->cmd);
		current = current->next;
	}
	printf("Amount of Pipes: %d\n", shell->pipes_count);
}

// WHEN HEREDOC IS USED REDIRECT_IN HAS TO BE DISABLED --- IMPORTANT NOTICE TO DO
int	main(int argc, char **argv)
{
	t_shell_data	*shell;

	(void)argv;
	(void)argc;
	// atexit(leaks);
	shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell)
		return (1);
	initialize_shell(shell);
	// "echo \"Hello World\" | grep 'Hello' | wc -c > output.txt ";
	// parse_readline(shell, "cat << EOF > output.txt");
	parse_readline(shell,
		"echo 'Hello World' >> output.txt <<EOF > test.txt < wow");
	// parse_readline(shell,"echo 'Hello World' > output.txt < EOF < test.txt > wow");
	// print_cmd_list(shell);
	free_env_list(shell->env);
	free_env_list(shell->variables);
	free_var_pipe_list(shell->pipe_list);
	free(shell);
	return (0);
}

// VARIABLE TEST
// printf("%s\n", test_get_variable(shell, "USER"));

// BUILTIN TESTS
// test_cd(shell);
// test_export(shell);
// test_echo();
// test_env(shell);
// test_pwd();
// test_unset(shell);

// EXEC FUNCTION TESTS
// cell_launch(ft_split("cat test", ' '));
// launch_program();

// REDIRECT TESTS
// (>) test_redirect_output("file.txt");
// (<) test_redirect_input(shell, "file.txt", "cat");
// (>>) test_redirect_append_output("file.txt");
// (<<) test_redirect_in_heredoc(shell);

// PIPE TESTS
// test_pipes();

// PARSING KEY VALUE
// parse_variable(shell, "TEST=$USER,$HOME-IS-BEST");
