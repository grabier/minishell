/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:42:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/01/28 14:04:10 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int	ft_check_quotes(char *input)
{
	int	i;
	int	cont1;
	int	cont2;

	cont1 = 0;
	cont2 = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == 39)
			cont1++;
		if (input[i] == 34)
			cont2++;
		i++;
	}
	if (cont1 % 2 != 0 || cont2 % 2 != 0)
		return (0);
	return (1);
}

static char	*ft_strinsert(char *str, char *word, int start, int end)
{
	int	i;
	int	j;
	char	*res;
	
	i = -1;
	j = 0;
	printf("start: %i\n", start);
	printf("end: %i\n", end);
	res = malloc(ft_strlen(str) - (end - start) + ft_strlen(word) + 1);
	while (++i < start)
		res[i] = str[i];
	while (word[j])
		res[i++] = word[j++];
	end++;
	while (str[end])
		res[i++] = str[end++];
	res[i] = '\0';
	return (res);
}

char	*ft_expand(char *input, int start)
{
	int		i;
	int		j;
	char	*name;
	char	*res;

	j = 0;
	i = start;
	while (input[i] != 34 && input[i] != ' ')
	{
		i++;
		j++; 
	}
	name = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(name, &input[start], j + 1);
	printf("name: %s\n", name);
	if (!getenv(name))
		return (NULL);
	res = ft_strinsert(input, getenv(name), start - 1, i - 1);
	return (res);
}

char	*ft_check_expands(char *input)
{
	int	i;
	char	*res;

	i = 0;
	res = NULL;
	while (input[i])
	{
		if (input[i] == 34 && input[i + 1] != '\0')
		{
			//printf("i: %i\n", i);
			i++;
			while (input[i] != '$' && input[i] != 34 && input[i])
				i++;
			if (input[i] == '$')
			{
				res = ft_expand(input, i + 1);
				if (!res)
					return (NULL);
				//free(input);
				input = ft_strdup(res);
				printf("input: %s\n", input);
				i = -1;
			}
		}
		i++;
	}
	return (res);
}

char *ft_quotes(char *input)
{
	char	*res;

	if (!ft_check_quotes(input))
		return (NULL);
	res = ft_check_expands(input);
	if (!res)
		return (input);
	printf("res: %s\n", res);
	return (res);
}

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
			break ;
		input = ft_quotes(input);
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