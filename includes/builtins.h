/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:21:55 by macbook           #+#    #+#             */
/*   Updated: 2025/01/13 03:13:28 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pipe_list(t_var_pipe_list *pipe_list);
// cd.c
int		fd_cd(t_shell_data *shell, char *path);
int		parse_launch_cd(t_shell_data *shell, char **command);
// echo.c
int		ft_echo(char *args, int fd, bool n_option);
int		parse_launch_echo(char **command);
// env.c
int		ft_env(t_shell_data *shell);
int		parse_launch_env(t_shell_data *shell, char **command);
// export.c
int		ft_export(t_shell_data *shell, char **variables);
int		parse_launch_export(t_shell_data *shell, char **command);
// pwd.c
void	change_pwd_env(t_env_list **head, const char *key, const char *value);
int		ft_pwd(void);
int		parse_launch_pwd(t_shell_data *shell, char **command);
// unset.c
int		ft_unset(t_shell_data *shell, char *variables);
int		parse_launch_unset(t_shell_data *shell, char **command);
// exit.c
int		ft_exit(t_shell_data *shell, char **command);