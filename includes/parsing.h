/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:29:32 by macbook           #+#    #+#             */
/*   Updated: 2025/01/16 21:48:58 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**expand_command(t_shell_data *shell, char **arr);
char			*join_subarrays(char **array);
void			select_final_qupte_type(char *arr, bool *in_single_quotes,
					bool *in_double_quotes);
bool			is_delimiter(char c);
void			expand_single_arg(t_shell_data *shell, char **args_ar);
void			remove_quotes(char **args);
char			*remove_heredoc_quotes(char *line);
// ft_split_delimiters_utils.c
char			*process_regular(const char *s, int *i, char **parentarray,
					int *ar_index);
char			*process_dollar(const char *s, int *i, char **parentarray,
					int *ar_index);
char			*process_delimiter(const char *s, int *i, char **parentarray,
					int *ar_index);
char			*allocate_and_copy_delimiters(const char *s, int startindex,
					int count);
// ft_split_delimiters.c
char			**str_div_logic_delimiters(char **parentarray, const char *s,
					int ar_index);
char			**ft_split_delimiters(const char *s);
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
