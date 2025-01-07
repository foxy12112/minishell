/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:21:08 by macbook           #+#    #+#             */
/*   Updated: 2025/01/07 06:03:04 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*command_is_builtin(char *command)
{
	char	*command_toupper;
	command_toupper = ft_strtoupper(command);
	if (!command_toupper)
		return (NULL);
	if (ft_strcmp(command_toupper, "ECHO") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "CD") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "ENV") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "EXIT") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "EXPORT") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "PWD") == 0)
		return (command_toupper);
	else if (ft_strcmp(command_toupper, "UNSET") == 0)
		return (command_toupper);
	else
		return (free(command_toupper), NULL);
}

int	select_launch_builtin(t_shell_data *shell, char **command)
{
	char	*command_toupper;

	command_toupper = ft_strtoupper(command[0]);
	if (!command_toupper)
		return (1);
	if (ft_strcmp(command_toupper, "ECHO") == 0)
		shell->last_exit_code = parse_launch_echo(command);
	else if (ft_strcmp(command_toupper, "CD") == 0)
		shell->last_exit_code = parse_launch_cd(shell, command);
	else if (ft_strcmp(command_toupper, "ENV") == 0)
		shell->last_exit_code = parse_launch_env(shell, command);
	else if (ft_strcmp(command_toupper, "EXPORT") == 0)
		shell->last_exit_code = parse_launch_export(shell, command);
	else if (ft_strcmp(command_toupper, "PWD") == 0)
		shell->last_exit_code = parse_launch_pwd(shell, command);
	else if (ft_strcmp(command_toupper, "UNSET") == 0)
		shell->last_exit_code = parse_launch_unset(shell, command);
	else if (ft_strcmp(command_toupper, "EXIT") == 0)
		ft_exit(shell);
	if (command_toupper)
		free(command_toupper);
	return (0);
}
