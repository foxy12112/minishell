/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:36:55 by ldick             #+#    #+#             */
/*   Updated: 2025/01/14 08:00:15 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>
# include <unistd.h>

# define CTRL_D "\033[A\033[2Kwaiting for input:exit\n"

typedef struct s_signal
{
	int						signal;
}							t_signal;

typedef struct s_term_settings
{
	struct termios			original;
}							t_term_settings;

typedef struct s_env_list
{
	char					*key;
	char					*value;
	struct s_env_list		*next;
	struct s_env_list		*prev;
}							t_env_list;

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
	char					*hd_file_name;
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
	char					**exec_env;
	char					**enviroment;
	int						pipes_count;
	t_term_settings			*terminal_settings;
	t_var_pipe_list			*pipe_list;
	bool					heredoc_launched;
	int						fd;
	int						last_exit_code;
	int						saved_stdin;
}							t_shell_data;

// typedef struct s_errdata
// {
// 	void	*alloc_data;
// 	void	(*teardown_func)(void *);
// }							t_errdata
// Import Files
# include "builtins.h"
# include "execution.h"
# include "parsing.h"
# include "redirects.h"
# include "utils.h"

int							utils(void);
void						print_arofars(char **str);
// parsing

void						display(t_shell_data *shell);
// int						setup_signals(void);
void						init_history(void);
void						add_permanent_history(char *str);
int							disable_control_echo(t_shell_data *shell);
int							restore_control_echo(void);
void						insert_word(char *original, char *word, int pos,
								char *result);
char						*replace_var_expanded(t_shell_data *shell,
								char *var, char *input, int i);
// expansion.c
bool						unclosed_quotes(char *input);
char						*get_variable_value(t_shell_data *shell, char *var);
//
char						*true_quote_removal(char *str);

int							main(int argc, char **argv, char **env);
// void						test_multi_redirect(t_shell_data *shell);
int							prepare_heredoc(t_shell_data *shell, t_var_cmd *cmd);
void						cleanup(t_shell_data *shell);
int							check_fd_heredoc(t_shell_data *shell, int end[2],
								t_var_cmd *cmd);
void						print_redirects(t_redirects *redirect);
bool						check_for_parse_errors(t_var_pipe_list *pipe_list);
#endif