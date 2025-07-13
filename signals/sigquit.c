/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigquit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:11:45 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/13 18:57:20 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigquit_handler(int sig)
{
	g_signal = sig; // Indicar que se ha recibido SIGQUIT
	write(2, "Quit: 3\n", 8);
}
