/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 00:56:03 by macbook           #+#    #+#             */
/*   Updated: 2024/12/26 16:57:26 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell_data *shell)
{
	static int	i;

	free_env_list(shell->env);
	free_env_list(shell->variables);
	free_var_pipe_list(shell->pipe_list);
	restore_control_echo(shell);
	free(shell);
	exit(i);
}

int utils(void)
{
	return (0);
}
