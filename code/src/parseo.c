/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:42:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/17 17:00:36 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void	ft_free_parse(char *input, t_tkn **t, t_cmd **c, char *prompt)
{
	if (c != NULL)
		ft_free_cmd_lst(c);
	ft_free_tkn_lst(t);
	free(input);
	free(prompt);
}

int	ft_get_input(char *envp[])
{
	char	*input;
	char	*prompt;
	t_tkn	*tkn_lst;
	t_cmd	*cmd_lst;

	(void)envp;
	cmd_lst = NULL;
	tkn_lst = NULL;
	//print_env(envp);
	while (1)//la minishell es lo que ocurra dentro de este bucle
	{
		prompt = ft_get_prompt(envp);
		input = readline(prompt);//FALTA: prompt personalizado: $USER@$HOSTNAME(hasta el primer .):pwd$
		if (!ft_strcmp(input, "exit"))
		{
			ft_free_parse(input, &tkn_lst, &cmd_lst, prompt);
			unlink(".tempppp");
			return (1);
		}
		add_history(input);//FALTA: añadir funciones de modificar historial
		tkn_lst = ft_tokenize(input);//devuelve una lista de tokens con un checkeo de sintax previo y comillas limpias(excepto comando)
		if (!tkn_lst)
			ft_free_parse(input, &tkn_lst, NULL, prompt);
			//ft_tknprint(tkn_lst);
		else
		{
			//printf("sale?\n");
			cmd_lst = ft_get_commands(tkn_lst);//devuelve una lista con los comandos a ejecutar y las redirs necesarias
			//ft_cmdprint(cmd_lst);
			ft_exec_commands(cmd_lst, &envp); 
			ft_free_parse(input, &tkn_lst, &cmd_lst, prompt);
		}
	}
	return (1);
}

int main(int argc, char *argv[], char *env[])
{
	char **cpy;
	
	cpy =  ft_copy_dp(env);
	ft_get_input(cpy);
	ft_free_split(cpy);
	return (0);
}