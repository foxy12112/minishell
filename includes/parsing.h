/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:29:32 by macbook           #+#    #+#             */
/*   Updated: 2025/01/10 18:56:03 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**expand_arguments_in_ar(t_shell_data *shell, char **arr);
char	**ft_split_multidelimiter(const char *str, bool(delim)(char c));
bool	is_delimiter(char c);

// cmd_parse.c
char			**get_simple_cmd(t_shell_data *shell, char *command, int *i);
t_var_cmd		*parse_command(t_shell_data *shell, char *command);

// pipe_split.c
int				add_to_pipelist(t_shell_data *shell, char *command);
void			process_pipe_list(t_var_pipe_list *pipe_list);
int				count_pipe_list_length(t_var_pipe_list *head);
int				parse_readline(t_shell_data *shell, char *commands);

// quote_utils.c
bool			quote_check(char *value, int start);

// redirect_parse_utils.c
void			sort_redirects(t_redirects **redirects);
t_redirect_type	select_redirect_type(char *redirect);
char			*get_filename_delimiter(t_redirect_type redirect_type,
					char *redirect);
// redirect_parse.c
void			parse_redirects(t_var_cmd *cmd_node, char *command, int *i);
void			assign_redirects(t_var_cmd *cmd_node, char *redirect);
void			add_redirect_to_cmd_node(t_var_cmd *cmd_node,
					t_redirects *new_redirect);
t_redirects		*create_redirect_node(char *redirect);

// variable_parse_utils.c
char			*true_quote_removal(char *value);
bool			string_in_singlequotes(char *value);
bool			string_in_doublequotes(char *value);
bool			check_key(char *key);
bool			contains_valid_chars(char *str);

// variable_parse.c
char			*parse_string(t_shell_data *shell, char *string);
char			*join_key_value(char *key, char *value);
char			*parse_variable(t_shell_data *shell, char *variable);

// variable_value.get.c
bool			check_if_surrounded_by_quotes(char *value, char *key,
					int start);
char			*parse_value(t_shell_data *shell, char *value);
