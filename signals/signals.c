/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:08:57 by kegonza           #+#    #+#             */
/*   Updated: 2025/05/22 21:26:25 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	setup_interactive_signals(void)
{
	disable_echoctl();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN); // Ignorar Ctrl+\;
}
