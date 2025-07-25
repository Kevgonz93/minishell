/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:13:52 by kegonza           #+#    #+#             */
/*   Updated: 2025/07/18 11:40:28 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <termios.h>
# include "../data.h"

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
