/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:43:34 by macbook           #+#    #+#             */
/*   Updated: 2025/01/14 07:58:51 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
// free.c
void		free_env_list(t_env_list *head);
void		free_string_array(char **str);
void		free_var_pipe_list(t_var_pipe_list *head);
char		**free_all(char **parentarray, int arrayindex);
// ft_split_whitespace.c
char		**ft_split_whitespace(char const *s);
// ft_split_by_first_equal.c
char		**ft_split_by_first_equal(const char *s);
// ft_split_quotes.c
char		**ft_split_quotes(char *s, char delimiter);
// utils.c
char		ft_is_whitespace(char c);
char		*ft_trim_whitespaces(char *str);
char		*ft_strtoupper(char *str);
char		*join_arof_ars(char **array, int start);

void		setup_signals(void);
char		*ft_strncpy(char *dst, const char *src, size_t len);
