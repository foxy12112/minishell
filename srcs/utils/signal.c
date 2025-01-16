/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:50:23 by ldick             #+#    #+#             */
/*   Updated: 2025/01/16 16:37:47 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sigint_handle(void)
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

static void	handler(int signal)
{
	if (signal == SIGINT)
		sigint_handle();
	else if (signal == SIGTERM)
		return ;
}

int	disable_control_echo(t_shell_data *shell)
{
	struct termios	terminal;

	tcgetattr(STDIN_FILENO, &terminal);
	tcgetattr(STDIN_FILENO, &shell->terminal_settings->original);
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	return (EXIT_SUCCESS);
}

int	restore_control_echo(void)
{
	struct termios	terminal;

	if (tcgetattr(STDIN_FILENO, &terminal) != 0)
		return (EXIT_FAILURE);
	terminal.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// sigignore(SIGQUIT);
// signal(SIGQUIT, SIG_IGN);

void	setup_signals(void)
{
	struct sigaction	sa;
	sigset_t			sigset;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigaddset(&sigset, SIGTERM);
	sa.sa_mask = sigset;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		printf("error setting up SIGINT Handler");
	else if (sigaction(SIGTERM, &sa, NULL) == -1)
		printf("error setting up SIGINT Handler");
}
