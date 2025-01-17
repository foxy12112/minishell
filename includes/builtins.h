/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:21:55 by macbook           #+#    #+#             */
/*   Updated: 2025/01/17 11:12:56 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

void	print_pipe_list(t_var_pipe_list *pipe_list);
void	print_commands(t_var_cmd *cmd);
// cd.c
int		fd_cd(t_shell_data *shell, char *path);
int		parse_launch_cd(t_shell_data *shell, char **command);
// echo.c
int		ft_echo(char *args, int fd, bool n_option);
int		parse_launch_echo(t_shell_data *shell, char **command);
// env.c
int		ft_env(t_shell_data *shell);
int		parse_launch_env(t_shell_data *shell, char **command);
// export_utils.c
void	swap_nodes(t_env_list *a, t_env_list *b);
// export.c
int		ft_export(t_shell_data *shell, char **variables);
int		parse_launch_export(t_shell_data *shell, char **command);
// pwd.c
void	change_pwd_env(t_env_list **head, const char *key, const char *value);
int		ft_pwd(int fd);
int		parse_launch_pwd(t_shell_data *shell, char **command);
// unset.c
int		ft_unset(t_shell_data *shell, char *variables);
int		parse_launch_unset(t_shell_data *shell, char **command);
bool	valid_key(const char *key);
// exit.c
int		ft_exit(t_shell_data *shell, char **command);
int		args_length(char **command);

#endif