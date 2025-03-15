/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:42:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/15 14:23:22 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int	signal_flag;

void	ft_free_shell(t_shell *shell)
{
	
	if (shell->cmd_lst != NULL)
		ft_free_cmd_lst(&shell->cmd_lst);
/* 	else
		free(shell->cmd_lst->args); */
	if (shell->tkn_lst != NULL)
		ft_free_tkn_lst(&shell->tkn_lst);
	free(shell->input);
	unlink(".tempppp");
	//free(shell);
	//free(shell->prompt);
}

t_shell	*ft_init_shell(void)
{
	t_shell *ms;

	ms = malloc(sizeof(t_shell));
	ms->cmd_lst = NULL;
	ms->tkn_lst = NULL;
	ms->exitstat = 0;
	return (ms);
}

void	ft_handle_c(int sig)
{
	(void)sig;
	//	printf("entra en c_normal: %i\n", signal_flag);
	if (signal_flag == 0)
	{
		//printf("entra en 0");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal_flag == 1)
	{
		//printf("entra en 1");
		printf("\n");
		//rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (signal_flag == 2)
	{
		//printf("entra en 2");
		printf("\n");
		//signal_flag = 0;
		exit(130);
	}
	else if (signal_flag == 3)
	{
		//printf("entra en 3");
		printf("");
	}
	signal_flag = 0;
}

/* void	ft_handle_d(int sig)
{
	(void)sig;
	printf("entra?\n");
	exit(130);
	signal_flag = 0;
} */

int	ft_get_input(char *envp[])
{
	char	*input;
	char	*prompt;
	t_shell	*ms;

	ms = ft_init_shell();
	ms->exitstat = 0;
	while (1)//la minishell es lo que ocurra dentro de este bucle
	{
		/* printf("exit: %i\n", ms->exitstat);
		printf("prebvexit: %i\n", ms->prevexitstat); */
		signal_flag = 0;
		if (ms->prevexitstat != 130)
			ms->prevexitstat = ms->exitstat;
		signal(SIGINT, ft_handle_c);
		ms->input = readline("\033[0;33mminichell>\033[0;37m ");//FALTA: prompt personalizado: $USER@$HOSTNAME(hasta el primer .):pwd$
		if (ms->input == NULL)
		{
			ft_free_split(envp);
			printf("exit loop\n");
			break ;
		}
		add_history(ms->input);//FALTA: añadir funciones de modificar historial
		ms->tkn_lst = ft_tokenize(ms, &envp);//devuelve una lista de tokens con un checkeo de sintax previo y comillas limpias(excepto comando)
		//ft_tknprint(ms->tkn_lst);
		if (!ms->tkn_lst)
			ft_free_shell(ms);
		else
		{
			ms->cmd_lst = ft_get_commands(ms, ms->tkn_lst, &envp);//devuelve una lista con los comandos a ejecutar y las redirs necesarias
			//ft_cmdprint(ms->cmd_lst);
			if (ms->cmd_lst)
				ft_exec_commands(ms, &envp);//nos vamos a ejecucion
			ft_free_shell(ms);
		}
	}
	return (free(ms), 1);
}

int main(int argc, char *argv[], char *env[])
{
	char **cpy;
	
	cpy =  ft_copy_dp(env);
	//print_env(cpy);
	ft_get_input(cpy);
	/* print_env(cpy);
	ft_free_split(cpy); */
	return (0);
}