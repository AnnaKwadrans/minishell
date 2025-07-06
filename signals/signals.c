/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:08:57 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/30 21:28:50 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	setup_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; // Reiniciar llamadas al sistema interrumpidas

	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL); // Registrar el manejador para SIGINT

	sa.sa_handler = sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL); // Registrar el manejador para SIGQUIT
}

void	setup_interactive_signals(void)
{
	disable_echoctl();
	setup_signals();
}

void	setup_nointeractive(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
