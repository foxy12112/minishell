/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 03:17:18 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/13 07:03:49 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	initialize_shell(t_shell_data *shell, char **env)
{
	shell->env = initialize_env(env);
	shell->variables = initialize_env(env);
	shell->pipes_count = 0;
	shell->saved_stdin = -1;
	shell->heredoc_launched = false;
	shell->pipe_list = NULL;
	shell->last_exit_code = 0;
	return (0);
}
