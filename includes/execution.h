/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:25:20 by macbook           #+#    #+#             */
/*   Updated: 2025/01/05 16:07:43 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// execute_builtins.c
char	*command_is_builtin(char *command);
int		select_launch_builtin(t_shell_data *shell, char **command);
// execute_redirects.c
int		setup_redirects(t_shell_data *shell, t_redirects *redirects);
// execute_command.c
int		execute_script(t_shell_data *shell);
int		execute_single_cmd(t_shell_data *shell, t_var_cmd *cmd);
char	*find_cmd(char **path, char *cmd);