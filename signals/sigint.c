/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:10:53 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/13 18:56:26 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	disable_echoctl(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag &= ~ECHOCTL; // Desactiva el eco de caracteres de control
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = sig; // Indicar que se ha recibido SIGINT
	write(1, "\n", 1);
	rl_replace_line("", 0); // Limpiar la línea actual
	rl_on_new_line(); // Mover el cursor a la nueva línea
	rl_redisplay(); // Redibujar la línea
}
