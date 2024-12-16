/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:36:55 by ldick             #+#    #+#             */
/*   Updated: 2024/12/16 13:49:11 by macbook          ###   ########.fr       */
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

// Import Files
# include "builtins.h"
# include "execution.h"
# include "parsing.h"
# include "redirects.h"
# include "utils.h"

int							main(int argc, char **argv);
int							utils(void);
void						print_arofars(char **str);

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
int							test_redirect_append_output(t_shell_data *shell,
								char *filename);
void						test_redirect_in_heredoc(t_shell_data *shell);
void						test_exec(char **command);
void						launch_program(void);
void						test_pipes(void);
void						test_multi_redirect(t_shell_data *shell);
#endif