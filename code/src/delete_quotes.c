/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:19:26 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/11 19:46:42 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"
//34 == doble    ||   39 == single
int	ft_count_quotes(char *input, int mode)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (input[i])
	{
		if (input[i] == mode)
			cont++;
		i++;
	}
	return (cont);
}

char	*ft_delete_dquotes(char *input)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(input) - ft_count_quotes(input, 34) + 1);
	i = 0;
	j = 0;
	while (input[i])
	{
		if(input[i] == 34)
			i++;
		else
			res[j++] = input[i++];
	}
	res[j] = 0;
	free(input);
	return (res);
}

char	*ft_delete_squotes(char *input)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(input) - ft_count_quotes(input, 39) + 1);
	i = 0;
	j = 0;
	while (input[i])
	{
		if(input[i] == 39)
			i++;
		else
			res[j++] = input[i++];
	}
	res[j] = 0;
	free(input);
	return (res);
}
