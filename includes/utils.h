/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:43:34 by macbook           #+#    #+#             */
/*   Updated: 2025/01/17 17:25:02 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

// history.c
void		init_history(void);
void		add_permanent_history(char *str);
// env_init.c
t_env_list	*initialize_env(char **env);
void		add_to_variables_list(t_env_list **head, char **key_value);
int			print_env_list(t_env_list *variables);
int			print_variables_list(t_env_list *variables);
int			add_variables(t_shell_data *shell, char **variables);
int			initialize_shell(t_shell_data *shell, char **env);
// variables.c
void		sort_env_list(t_env_list *head);
char		*retrieve_variable(t_shell_data *shell, char *key);
// free_linked_lists.c
void		free_env_list(t_env_list *head);
void		free_var_pipe_list(t_var_pipe_list *head);
// free.c
void		free_string_array(char **str);
char		**free_all(char **parentarray, int arrayindex);
void		cleanup(t_shell_data *shell);
void		clear_shell_data(t_shell_data *shell);
void		handle_exit(t_shell_data *shell, char *input);
// ft_split_whitespace.c
char		**ft_split_whitespace(char const *s);
// ft_split_by_first_equal.c
char		**ft_split_by_first_equal(const char *s);
// ft_split_quotes.c
char		**ft_split_quotes(char *s, char delimiter);
// utils.c
char		ft_is_whitespace(char c);
char		*ft_trim_whitespaces(char *str);
char		*join_arof_ars(char **array, int start);
// signals.c
void		setup_signals(void);
char		*ft_strncpy(char *dst, const char *src, size_t len);

#endif