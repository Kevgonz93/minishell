/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:11:45 by kegonza           #+#    #+#             */
/*   Updated: 2025/06/28 18:18:30 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigquit_handler(int sig)
{
	(void)sig;
	write(2, "Quit: 3\n", 8);
}
