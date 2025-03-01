/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:42:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/28 18:42:56 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void	ft_free_shell(t_shell *shell)
{
	
	if (shell->cmd_lst != NULL)
		ft_free_cmd_lst(&shell->cmd_lst);
	if (shell->tkn_lst != NULL)
		ft_free_tkn_lst(&shell->tkn_lst);
	free(shell->input);
	//free(shell);
	//free(prompt);
}

int	ft_get_input(char *envp[])
{
	char	*input;
	char	*prompt;
	t_shell	*ms;
	//t_tkn	*tkn_lst;
	//t_cmd	*cmd_lst;

	//ms = NULL;
	//ms->input = "hola k paza";
	//print_env(envp);
	ms = malloc(sizeof(t_shell));
	ms->exitstat = 0;
	while (1)//la minishell es lo que ocurra dentro de este bucle
	{
		//prompt = ft_get_prompt("minichell>");
		ms->input = readline("minichell> ");//FALTA: prompt personalizado: $USER@$HOSTNAME(hasta el primer .):pwd$
		//printf("exitstatus: %i\n", ms->exitstat);
		/* if (!ft_strcmp(ms->input, "exit"))
		{
			ft_free_shell(ms);
			free(ms);
			unlink(".tempppp");//eliminamos el temporal del here_doc si hay
			ft_free_split(envp);
			return (1);
		} */
		add_history(ms->input);//FALTA: añadir funciones de modificar historial
		ms->tkn_lst = ft_tokenize(ms, &envp);//devuelve una lista de tokens con un checkeo de sintax previo y comillas limpias(excepto comando)
		//ft_tknprint(tkn_lst);
		if (!ms->tkn_lst)
		{
			//printf("sale x aki?\n");
			ft_free_shell(ms);
		}
		else
		{
			ms->cmd_lst = ft_get_commands(ms->tkn_lst, &envp);//devuelve una lista con los comandos a ejecutar y las redirs necesarias
			//printf("sale?\n");
			
			if (ms->cmd_lst)
				ft_exec_commands(ms, &envp);//nos vamos a ejecucion
			//printf("sale?\n");
			//printf("exit: %i\n", cmd_lst->exit_status);
			unlink(".tempppp");
			ft_free_shell(ms);
		}
	}
	free(ms);
	return (1);
}

int main(int argc, char *argv[], char *env[])
{
	char **cpy;
	
	cpy =  ft_copy_dp(env);
	//printf("cpy[0]: %s\n", cpy[0]);
	ft_get_input(cpy);
	/* print_env(cpy);
	ft_free_split(cpy); */
	return (0);
}