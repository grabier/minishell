/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:42:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/01/28 17:19:55 by gmontoro         ###   ########.fr       */
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
	char	**tokens;
	int token_count;
	int	i = -1;

	(void)envp;
	while (1)
	{
		input = readline("minishell->");
		if (!ft_strncmp(input, "exit", 5))
		{
			free(input);
			break ;
		}
		add_history(input);
		input = ft_quotes(input);
		free(input);
		/* tokens = parse_input(input, &token_count);
		while (tokens[++i])
			printf("[%s]\n", tokens[i]);
		free_tokens(tokens, token_count); */
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