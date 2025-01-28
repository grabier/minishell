/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:25:56 by gmontoro          #+#    #+#             */
/*   Updated: 2025/01/28 17:18:37 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

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
	free(input);
	free(name);
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
				free(res);
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
	free(input);
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
