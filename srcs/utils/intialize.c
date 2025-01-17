/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 03:17:18 by auplisas          #+#    #+#             */
/*   Updated: 2025/01/17 22:19:02 by ldick            ###   ########.fr       */
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
	shell->heredoc_c = false;
	return (0);
}
