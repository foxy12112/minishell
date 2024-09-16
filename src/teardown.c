/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teardown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgmelin <tgmelin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:24:51 by tgmelin           #+#    #+#             */
/*   Updated: 2024/09/16 18:49:10 by tgmelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	teardown(void	*_mem)
{
	t_allocated_memory	*mem;

	mem = _mem; //thats why i use those underscores
}
