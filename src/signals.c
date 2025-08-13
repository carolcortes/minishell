/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 21:50:39 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/13 21:44:23 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include "../inc/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	// Do nothing - ignore SIGQUIT in interactive mode
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	// Setup SIGINT handler
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	// Setup SIGQUIT handler (ignore it)
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
