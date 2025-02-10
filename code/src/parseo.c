/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:42:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/10 16:16:27 by gmontoro         ###   ########.fr       */
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
	while (1)
	{
		input = readline("minishell->");
		if (!ft_strncmp(input, "exit", 5))
		{
			free(input);
			break ;
		}
		printf("llegaaaaa\n");
		add_history(input);
		tkn_lst = ft_tokenize(input);
		ft_check_syntax(tkn_lst);
		ft_quotes(&tkn_lst);
		ft_tknprint(tkn_lst);
		cmd_lst = ft_get_commands(tkn_lst);
		//ft_exec_commands(cmd_lst, envp);
		ft_cmdprint(cmd_lst);
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