/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:36:55 by ldick             #+#    #+#             */
/*   Updated: 2024/12/15 11:21:07 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// > - RDR_COMMAND_TO_INPUT, < - RDR_INPUT_TO_COMMAND, << -

typedef struct s_signal
{
	int						signal;
}							t_signal;

typedef struct s_env_list
{
	char					*key;
	char					*value;
	struct s_env_list		*next;
	struct s_env_list		*prev;
}							t_env_list;

typedef struct s_heredoc_list
{
	char					*word;
	struct s_heredoc_list	*next;
	struct s_heredoc_list	*prev;
}							t_heredoc_list;

typedef enum e_redirect_type
{
	REDIR_FAIL = 0,
	OP_REDIRECT_IN = 1,
	OP_REDIRECT_OUT,
	OP_APPEND_OUT,
	OP_HEREDOC,
}							t_redirect_type;

typedef struct s_redirects
{
	t_redirect_type			redirect_type;
	char					*delimiter;
	char					*filename;
	struct s_redirects		*next;
	struct s_redirects		*prev;
}							t_redirects;

typedef struct s_var_cmd
{
	char					**command;
	int						redirect_count;
	t_redirects				*redirects;
	struct s_var_cmd		*next;
	struct s_var_cmd		*prev;
}							t_var_cmd;

typedef struct s_var_pipe_list
{
	t_var_cmd				*cmd;
	struct s_var_pipe_list	*next;
	struct s_var_pipe_list	*prev;
}							t_var_pipe_list;

typedef struct s_shell_data
{
	t_env_list				*env;
	t_env_list				*variables;
	int						pipes_count;
	t_var_pipe_list			*pipe_list;
	bool					heredoc_launched;
	int						fd;
}							t_shell_data;

int							main(int argc, char **argv);
int							utils(void);
int	execute_single_cmd(t_shell_data *shell, t_var_cmd *cmd);
// builtins
int							fd_cd(t_shell_data *shell, char *path);
int							ft_echo(char *args, int fd, bool n_option);
int							ft_env(t_shell_data *shell);
int							ft_export(t_shell_data *shell, char **variables);
void						change_pwd_env(t_env_list **head, const char *key,
								const char *value);
int							ft_pwd(void);
int							ft_unset(t_shell_data *shell, char *variables);
// redirect_parse_utils.c
void						sort_redirects(t_redirects **redirects);
t_redirect_type				select_redirect_type(char *redirect);
char						*get_filename_delimiter(t_redirect_type redirect_type,
								char *redirect);
// redirect_parse.c
void						parse_redirects(t_var_cmd *cmd_node, char *command,
								int *i);
void						assign_redirects(t_var_cmd *cmd_node,
								char *redirect);
void						add_redirect_to_cmd_node(t_var_cmd *cmd_node,
								t_redirects *new_redirect);
t_redirects					*create_redirect_node(char *redirect);
// cmd_parse.c
char						**get_simple_cmd(char *command, int *i);
t_var_cmd					*parse_command(char *command);
// pipe_split.c
int							add_to_pipelist(t_shell_data *shell, char *command);
int							parse_readline(t_shell_data *shell, char *commands);
void						process_pipe_list(t_var_pipe_list *pipe_list);
int							count_pipe_list_length(t_var_pipe_list *head);
// variable_parse_utils.c
char						*remove_quotes(char *value);
bool						string_in_singlequotes(char *value);
bool						string_in_doublequotes(char *value);
bool						check_key(char *key);
bool						contains_valid_chars(char *str);
// variable_parse.c
char						*join_key_value(char *key, char *value);
char						*parse_variable(t_shell_data *shell,
								char *variable);
// variable_value.get.c
char						*parse_value(t_shell_data *shell, char *value);
// env.c
t_env_list					*initialize_env(void);
void						add_to_variables_list(t_env_list **head,
								char **key_value);
void						print_env_list(t_env_list *variables);
void						print_variables_list(t_env_list *variables);
int							add_variables(t_shell_data *shell,
								char **variables);
int							initialize_shell(t_shell_data *shell);
// redirects.c
int							redirect_output(t_shell_data *shell,
								const char *filename);
void						redirect_input(t_shell_data *shell,
								const char *filename);
int	redirect_output_append(t_shell_data *shell, const char *filename);
void						redirect_input_heredoc(t_shell_data *shell,
								const char *delimiter);
// heredocutils.c
int							count_line_size(t_heredoc_list **head);
t_heredoc_list				*create_heredoc_node(char *word);
t_heredoc_list				*handle_variable_node(t_shell_data *shell,
								char *word);
// exec.c
pid_t						ft_fork(void);
void						cell_launch(char **args);
// variables.c
void						sort_env_list(t_env_list *head);
char						*retrieve_variable(t_shell_data *shell, char *key);
// free.c
void						free_env_list(t_env_list *head);
void						free_key_value(char **key_value);
void						free_char_string(char **str);
void						free_heredoc_list(t_heredoc_list **head);
void						free_var_pipe_list(t_var_pipe_list *head);
// pipe.c
// void						pipe_commands(char ***commands, int cmd_count);
void						pipe_commands(char **cmd1, char **cmd2);
// void	pipe_multiple_commands(t_shell_data *shell, char ***commands, int cmd_count);
void	pipe_multiple_commands(t_shell_data *shell, t_var_pipe_list *pipe_list,
		int cmd_count);
// utils.c
char						ft_is_whitespace(char c);
bool						is_valid_char(char c, char *invalid_chars);
char						**ft_split_by_first_equal(const char *s);
char						*ft_trim_whitespaces(char *str);
char						**ft_split_whitespace(char const *s);
char	*ft_strtoupper(char *str);
// variable_parse.c
bool						check_valid_variable(char *variable);
// test.c
char						*test_get_variable(t_shell_data *shell, char *key);
void						test_cd(t_shell_data *shell);
void						test_export(t_shell_data *shell);
void						test_echo(char *string, int fd);
void						test_env(t_shell_data *shell);
void						test_pwd(void);
void						test_unset(t_shell_data *shell);
int							test_redirect_output(t_shell_data *shell,
								char *filename);
void						test_redirect_input(t_shell_data *shell,
								char *filename, char *command);
int							test_redirect_append_output(t_shell_data *shell, char *filename);
void						test_redirect_in_heredoc(t_shell_data *shell);
void						test_exec(char **command);
void						launch_program(void);
void						test_pipes(void);
void						test_multi_redirect(t_shell_data *shell);
#endif