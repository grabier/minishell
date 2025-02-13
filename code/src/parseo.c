/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:42:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/13 10:39:10 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int	ft_get_input(char *envp[])
{
	char	*input;
	t_tkn	*tkn_lst;
	t_cmd	*cmd_lst;

	(void)envp;
	while (1)//la minishell es lo que ocurra dentro de este bucle
	{
		input = readline("minishell->");//FALTA: prompt personalizado: $USER@$HOSTNAME(hasta el primer .):pwd$
		if (!ft_strncmp(input, "exit", 5))
		{
			free(input);
			break ;
		}
		add_history(input);//FALTA: añadir funciones de modificar historial
		tkn_lst = ft_tokenize(input);//devuelve una lista de tokens con un checkeo de sintax previo
									// y comillas limpias(excepto comando)
		//ft_tknprint(tkn_lst);
		cmd_lst = ft_get_commands(tkn_lst);//devuelve una lista con los comandos 
							//a ejecutar y las redirs necesarias
		//ft_cmdprint(cmd_lst);
		ft_exec_commands(cmd_lst, envp); 
		ft_free_tkn_lst(&tkn_lst);
		ft_free_cmd_lst(&cmd_lst);
		free(input);
	}
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	int token_count;
	ft_get_input(envp);
	//ft_get_input(envp);
	//printf("DEBUGGER\n");
	return (0);
}