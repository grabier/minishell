/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:53:32 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/05 15:00:20 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

void	handle_sigquit_fork(int sig)
{
	printf("Quit (core dumped)");
	g_signal = sig;
	kill(0, SIGINT);
}

void	handle_sigint_fork(int sig)
{
	printf("\n");
	if (g_signal == 0)
		g_signal = sig;
}

void	handle_sigint_main(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}