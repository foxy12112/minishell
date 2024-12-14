/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:32:25 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/14 14:43:39 by macbook          ###   ########.fr       */
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

char	*get_filename_delimiter(t_redirect_type redirect_type, char *redirect)
{
	int		i;
	char	*filename;
	char	*filename_parsed;
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
	return (filename_parsed);
}

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
	while (command[*i] == command[(*i) + 1])
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
			while (command[*i] == command[(*i) + 1])
				(*i)++;
		}
	}
}

char	**get_simple_cmd(char *command, int *i)
{
	char	*cmd;
	char	*cmd_parsed;
	char	**cmd_array;

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
	cmd_array = ft_split_whitespace(cmd_parsed);
	free(cmd);
	free(cmd_parsed);
	return (cmd_array);
}

t_var_cmd	*parse_command(char *command)
{
	t_var_cmd	*cmd_node;
	int			i;

	i = 0;
	cmd_node = (t_var_cmd *)malloc(sizeof(t_var_cmd));
	if (!cmd_node)
		return (NULL);
	cmd_node->command = get_simple_cmd(command, &i);
	cmd_node->redirect_count = 0;
	cmd_node->redirects = NULL;
	parse_redirects(cmd_node, command, &i);
	cmd_node->next = NULL;
	cmd_node->prev = NULL;
	return (cmd_node);
}

int	add_to_pipelist(t_shell_data *shell, char *command)
{
	t_var_pipe_list	*new_node;
	t_var_pipe_list	*current;

	new_node = (t_var_pipe_list *)malloc(sizeof(t_var_pipe_list));
	if (!new_node)
		return (-1);
	new_node->cmd = parse_command(command);
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

void	print_redirects(t_redirects *redirect)
{
	while (redirect)
	{
		printf("\tRedirect Type: %d\n", redirect->redirect_type);
		printf("\tFilename: %s\n", redirect->filename);
		printf("\tDelimiter: %s\n", redirect->delimiter);
		redirect = redirect->next;
	}
}

void print_arofars(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		printf("[%s]", str[i]);
		i++;
	}
}
// Function to print command data
void	print_commands(t_var_cmd *cmd)
{
	while (cmd)
	{
		printf("Command:");
		print_arofars(cmd->command);
		printf("\n");
		printf("Redirect Count: %d\n", cmd->redirect_count);
		if (cmd->redirects)
		{
			printf("Redirects:\n");
			print_redirects(cmd->redirects);
		}
		cmd = cmd->next;
	}
}

// Function to print the pipe list data
void	print_pipe_list(t_var_pipe_list *pipe_list)
{
	while (pipe_list)
	{
		if (pipe_list->cmd)
		{
			print_commands(pipe_list->cmd);
		}
		else
		{
			printf("No commands in this pipe.\n");
		}
		printf("\n\n");
		pipe_list = pipe_list->next;
	}
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
	parse_readline(shell, "echo \"Hello World\" | grep >> 'Hello' | wc -c > output.txt | cat << EOF");
	// parse_readline(shell, "echo -n \"Hello World and Sun\" ");
	// parse_readline(shell,
	// 	"echo 'Hello World' >> output.txt <<EOF > test.txt < wow");
	// parse_readline(shell,"echo 'Hello World' > output.txt < EOF < test.txt > wow");
	printf("\nPipes Count: %d\n\n", shell->pipes_count);
	print_pipe_list(shell->pipe_list);
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
