/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:13:52 by kegonza           #+#    #+#             */
/*   Updated: 2025/05/22 21:25:34 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SGIGNALS_H
# define SGIGNALS_H

# include "../data.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>


void	rl_replace_line(const char *text, int clear_undo);

void	setup_signals(void);
void	sigint_handler(int signum);
void	sigquit_handler(int signum);
void	setup_interactive_signals(void);
void	disable_echoctl(void);

#endif
