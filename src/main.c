/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgmelin <tgmelin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:23:10 by tgmelin           #+#    #+#             */
/*   Updated: 2024/09/16 18:47:21 by tgmelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int _argc, char *_argv[])
{
	t_global_state	state;

	state.is_interactive = true;
	if (_argc > 1)
		state.is_interactive = false;
	if (setup(&state))
		return (EXIT_FAILURE);
	teardown(&state.mem);
	return (EXIT_SUCCESS);
}
