/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:50:23 by ldick             #+#    #+#             */
/*   Updated: 2024/12/16 09:03:24 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_signal(int signal)
{
	if (signal == SIGINT)
		return (1);
	else if (signal == SIGQUIT)
		return (2);
	else if (signal == SIGTERM)
		return (3);
	return (0);
}

int	setup_signals(void)
{
	struct sigaction	sa;
	sigset_t			sigset;
	int					signal;

	sa.sa_handler = handle_signal;
	signal = handle_signal;
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
	return(signal);
}
