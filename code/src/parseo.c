/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:42:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:21:43 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int	g_signal_flag;

void	ft_free_shell(t_shell *shell)
{
	if (shell->cmd_lst != NULL)
		ft_free_cmd_lst(&shell->cmd_lst);
	if (shell->tkn_lst != NULL)
		ft_free_tkn_lst(&shell->tkn_lst);
	free(shell->input);
	unlink(".tempppp");
}

t_shell	*ft_init_shell(void)
{
	t_shell	*ms;

	ms = malloc(sizeof(t_shell));
	ms->cmd_lst = NULL;
	ms->tkn_lst = NULL;
	ms->aux = NULL;
	ms->em = "End quote not found\n";
	ms->exitstat = 0;
	ms->prevexitstat = 0;
	ms->i = 0;
	return (ms);
}

void	ft_handle_c(int sig)
{
	(void)sig;
	if (g_signal_flag == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_signal_flag == 1)
	{
		printf("\n");
		rl_replace_line("", 0);
	}
	else if (g_signal_flag == 2)
	{
		printf("\n");
		exit(130);
	}
	else if (g_signal_flag == 3)
		printf("");
	g_signal_flag = 0;
}

int	ft_get_input(char *envp[], t_shell *ms)
{
	while (1)
	{
		g_signal_flag = 0;
		if (ms->prevexitstat != 130)
			ms->prevexitstat = ms->exitstat;
		signal(SIGINT, ft_handle_c);
		ms->input = readline("\033[0;33mminichell>\033[0;37m ");
		if (ms->input == NULL)
			return (free(ms), ft_free_split(envp), printf("exit loop\n"), 1);
		add_history(ms->input);
		ms->tkn_lst = ft_tokenize(ms, &envp);
		if (!ms->tkn_lst)
			ft_free_shell(ms);
		else
		{
			ms->cmd_lst = ft_get_commands(ms, ms->tkn_lst, &envp);
			if (ms->cmd_lst)
				ft_exec_commands(ms, &envp);
			ft_free_shell(ms);
		}
	}
	return (free(ms), 1);
}

int	main(int argc, char *argv[], char *env[])
{
	char	**cpy;
	t_shell	*ms;

	(void)argc;
	(void)argv;
	cpy = ft_copy_env(env);
	ms = ft_init_shell();
	ft_get_input(cpy, ms);
	return (0);
}
