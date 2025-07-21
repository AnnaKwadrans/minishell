/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:10:53 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/18 13:01:39 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

// Function to enable the ECHOCTL flag in the terminal settings
void	disable_echoctl(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
