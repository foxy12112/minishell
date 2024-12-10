/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:36:55 by ldick             #+#    #+#             */
/*   Updated: 2024/12/10 10:03:40 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

// > - RDR_COMMAND_TO_INPUT, < - RDR_INPUT_TO_COMMAND, << -
typedef enum s_operation_type
{
	RDR_INPUT,
	RDR_OUTPUT,
	RDR_HEREDOC,
	RDR_APPEND,
	PIPE,
	NO_RDR,
}						t_operation_type;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
	struct s_env_list	*prev;
}						t_env_list;

typedef struct s_signal
{
	int					signal;
}						t_signal;

typedef struct s_var_list
{
	char				*var_name;
	char				*var_value;
	struct s_var_list	*next;
	struct s_var_list	*prev;
}						t_var_list;

typedef struct s_shell_data
{
	t_operation_type	operation_type;
	t_env_list			*env;
	t_env_list			*variables;
}						t_shell_data;

typedef struct s_nodes
{
}						t_nodes;

int						main(int argc, char **argv);
int						utils(void);

// builtins
int						ft_echo(char **args, int fd);
int						fd_cd(char *path);
int						ft_pwd(void);
int						ft_export(t_shell_data *shell, char **variables);
// env.c
t_env_list				*initialize_env(void);
void					add_to_variables_list(t_env_list **head,
							char **key_value);
void					print_env_list(t_env_list *variables);
void					print_variables_list(t_env_list *variables);
// free.c
void					free_env_list(t_env_list *head);
void					free_key_value(char **key_value);

// parsing

void					display(void);
int						setup_signals(void);

#endif