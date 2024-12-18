/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 03:17:18 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/18 11:58:55 by ldick            ###   ########.fr       */
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
	return (0);
}
