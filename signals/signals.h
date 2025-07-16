/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:13:52 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/16 19:44:11 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../data.h"
# include <signal.h>

void	rl_replace_line(const char *text, int clear_undo);

// HERE_DOC.C
void	sigint_handler_heredoc(int sig);
void	setup_heredoc_signals(void);

// SIGINT.C
void	disable_echoctl(void);
void	sigint_handler(int signum);

// SIGNALS.C
void	setup_signals(void);
void	setup_interactive_signals(void);
void	setup_nointeractive(void);
void	restore_signals(void);

// SIGQUIT.C
void	sigquit_handler(int signum);

#endif
