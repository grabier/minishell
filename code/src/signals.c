/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:53:32 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/05 14:45:20 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"


void	handle_sigquit_fork(int sig)
{
	printf("Quit (core dumped)");
	kill(0, SIGINT);
}

void	handle_sigint_fork(int sig)
{
	printf("\n");
}

void	handle_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	ft_handle_c(int	sig)
{
	
}