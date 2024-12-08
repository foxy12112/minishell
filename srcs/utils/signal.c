/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:50:23 by ldick             #+#    #+#             */
/*   Updated: 2024/12/08 15:55:40 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	
}

void	handle_signal(int signal)
{
	if (signal == SIGINT)
		printf("CTRL-C: quit all i think\n");
	else if (signal == SIGQUIT)
		printf("CTRL-\\: quit everything propably\n");
	else if (signal == SIGTERM)
		printf("CTRL=D: do something\n");
	else
		printf("caught %d\n", signal);
}