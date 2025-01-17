/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:50:23 by ldick             #+#    #+#             */
/*   Updated: 2025/01/17 21:11:32 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sigint_handle(void)
{
	// printf("\n");
	// rl_on_new_line();
	// // rl_replace_line("", 0);
	// rl_redisplay();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
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

int	restore_control_echo()
{
	struct termios	terminal;

	// printf("WE GOT TO HERE: restore ocntrol echo\n");
	if (tcgetattr(STDIN_FILENO, &terminal) != 0)
		return (EXIT_FAILURE);
	terminal.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	setup_signals(void)
{
	struct sigaction	sa;
	sigset_t			sigset;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigignore(SIGQUIT);
	// signal(SIGQUIT, SIG_IGN);
	sigaddset(&sigset, SIGTERM);
	sa.sa_mask = sigset;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		printf("error setting up SIGINT Handler");
	else if (sigaction(SIGTERM, &sa, NULL) == -1)
		printf("error setting up SIGINT Handler");
}
