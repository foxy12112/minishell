/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 03:17:18 by auplisas          #+#    #+#             */
/*   Updated: 2024/12/13 05:37:57 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	initialize_shell(t_shell_data *shell)
{
	shell->env = initialize_env();
	shell->variables = initialize_env();
	shell->pipes_count = 0;
	shell->operation_type = NO_RDR;
	return (0);
}
