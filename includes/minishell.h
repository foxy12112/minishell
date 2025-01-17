/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:36:55 by ldick             #+#    #+#             */
/*   Updated: 2025/01/17 11:12:07 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# include "structs.h"
# include "parsing.h"
# include "builtins.h"
# include "libs.h"
# include "execution.h"
# include "redirects.h"
# include "utils.h"

# define CTRL_D "\033[A\033[2Kwaiting for input:exit\n"

// main.c
int							main(int argc, char **argv, char **env);
void						display(t_shell_data *shell);
void						print_arofars(char **str);
// loop_utils.c
int							handle_parse_errors(t_shell_data *shell);
int							handle_command_validation(t_shell_data *shell);
int							handle_unclosed_quotes(t_shell_data *shell,
								char *input);
int							handle_empty_input(char *input);
void						init_history(void);
void						add_permanent_history(char *str);
int							disable_control_echo(t_shell_data *shell);
int							restore_control_echo(void);
// expansion.c
bool						unclosed_quotes(char *input);
char						*get_variable_value(t_shell_data *shell, char *var);
//
char						*true_quote_removal(char *str);
// void						test_multi_redirect(t_shell_data *shell);
int							prepare_heredoc(t_shell_data *shell,
								t_var_cmd *cmd);
int							reset_heredoc_fd(t_shell_data *shell, int end[2],
								t_var_cmd *cmd);
void						print_redirects(t_redirects *redirect);
bool						check_for_parse_errors(t_var_pipe_list *pipe_list);

#endif