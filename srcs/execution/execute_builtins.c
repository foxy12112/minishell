/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:21:08 by macbook           #+#    #+#             */
/*   Updated: 2025/01/16 16:35:07 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strtoupper(char *str)
{
	int		i;
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		new_str[i] = ft_toupper(str[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

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

// ft_strcmp(command_toupper, "/BIN/ECHO") == 0

int	select_launch_builtin(t_shell_data *shell, char **command)
{
	char	*command_toupper;

	command_toupper = ft_strtoupper(command[0]);
	if (!command_toupper)
		return (1);
	if (ft_strcmp(command_toupper, "ECHO") == 0)
		return (free(command_toupper), parse_launch_echo(shell, command));
	else if (ft_strcmp(command_toupper, "CD") == 0)
		return (free(command_toupper), parse_launch_cd(shell, command));
	else if (ft_strcmp(command_toupper, "ENV") == 0)
		return (free(command_toupper), parse_launch_env(shell, command));
	else if (ft_strcmp(command_toupper, "EXPORT") == 0)
		return (free(command_toupper), parse_launch_export(shell, command));
	else if (ft_strcmp(command_toupper, "PWD") == 0)
		return (free(command_toupper), parse_launch_pwd(shell, command));
	else if (ft_strcmp(command_toupper, "UNSET") == 0)
		return (free(command_toupper), parse_launch_unset(shell, command));
	else if (ft_strcmp(command_toupper, "EXIT") == 0)
	{
		free(command_toupper);
		return (ft_exit(shell, command));
	}
	if (command_toupper)
		free(command_toupper);
	return (0);
}
