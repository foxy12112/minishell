/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:50:23 by ldick             #+#    #+#             */
/*   Updated: 2024/12/17 14:49:35 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handler(int signal)
{
	if (signal == SIGINT)
		printf("Received SIGINT\n");
	else if (signal == SIGQUIT)
		printf("Received SIGQUIT\n");
	else if (signal == SIGTERM)
		printf("Received SIGTERM\n");
	printf("Received signal: %d\n", signal);
}

void	setup_signals(void)
{
	struct sigaction	sa;
	sigset_t			sigset;

	sa.sa_handler = handler;
	sa.sa_flags	=	0;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigaddset(&sigset, SIGQUIT);
	sigaddset(&sigset, SIGTERM);
	sa.sa_mask = sigset;

	if (sigaction(SIGINT, &sa, NULL) == -1)
		printf("error setting up SIGINT Handler");
	else if (sigaction(SIGQUIT, &sa, NULL) == -1)
		printf("error setting up SIGINT Handler");
	else if (sigaction(SIGTERM, &sa, NULL) == -1)
		printf("error setting up SIGINT Handler");
}
