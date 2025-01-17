/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:25:20 by macbook           #+#    #+#             */
/*   Updated: 2025/01/17 21:04:01 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

// execute_builtins.c
char	*command_is_builtin(char *command);
int		select_launch_builtin(t_shell_data *shell, char **command);
// execute_redirects.c
int		setup_redirects(t_shell_data *shell, t_var_cmd *cmd,
			t_redirects *redirects);
char	*ft_strtoupper(char *str);
// execute_command.c
int		execute_script(t_shell_data *shell);
int		launch_single_command(t_shell_data *shell, char **command);
int		execute_single_cmd(t_shell_data *shell, t_var_cmd *cmd);
char	*find_cmd(t_env_list *env, char *cmd);
// execute_pipes.c
void	pipe_multiple_commands(t_shell_data *shell, t_var_pipe_list *pipe_list,
			int cmd_count);
// exec.c
pid_t	ft_fork(void);
int		cell_launch(t_shell_data *shell, char **args);
char	**true_quote_removal_from_array(char **array);

#endif