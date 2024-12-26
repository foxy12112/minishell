/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 03:17:18 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/26 17:19:22 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	initialize_shell(t_shell_data *shell)
{
	shell->env = initialize_env();
	shell->variables = initialize_env();
	shell->pipes_count = 0;
	shell->heredoc_launched = false;
	shell->pipe_list = NULL;
	shell->last_exit_code = 0;
	return (0);
}
