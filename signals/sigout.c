/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonza <kegonzal@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:11:45 by kegonza           #+#    #+#             */
/*   Updated: 2025/05/22 21:18:17 by kegonza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigquit_handler(int sig)
{
	(void)sig;
	write(1, "Quit\n", 6);
}
