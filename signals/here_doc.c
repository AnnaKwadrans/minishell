/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:09:43 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/30 21:26:33 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	write(1, "\n", 1);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa; // Estructura para manejar señales

	sa.sa_handler = sigint_handler_heredoc; // Asignar el manejador de señales
	sigemptyset(&sa.sa_mask);	// Indica que ninguna señal será bloqueada mientras se ejecuta el handler
	sa.sa_flags = 0; // No usar flags especiales

	sigaction(SIGINT, &sa, NULL); // Registrar el manejador para SIGINT
	signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT para evitar que se cierre el programa
}
