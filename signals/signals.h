/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:13:52 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/01 19:31:11 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../data.h"

extern volatile sig_atomic_t g_heredoc_interrupted;

void	rl_replace_line(const char *text, int clear_undo);

// HERE_DOC.C
void	sigint_handler_heredoc(int);
void	setup_heredoc_signals(void);

// SIGINT.C
void	disable_echoctl(void);
void	sigint_handler(int signum);

// SIGNALS.C
void	setup_signals(void);
void	setup_interactive_signals(void);
void 	restore_signals(void);

// SIGQUIT.C
void	sigquit_handler(int signum);

#endif
