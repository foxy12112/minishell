/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgmelin <tgmelin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:25:51 by tgmelin           #+#    #+#             */
/*   Updated: 2024/09/16 18:39:10 by tgmelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	setup(t_global_state	*_state)
{
	t_ft_err_data	err_data;

	err_data.alloc_data = &_state->mem;
	err_data.teardown_func = teardown;
	ft_error(&err_data, NULL, 0);
	return (EXIT_SUCCESS);
}
