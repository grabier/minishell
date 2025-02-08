/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:19:26 by gmontoro          #+#    #+#             */
/*   Updated: 2025/01/28 19:31:16 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_count_quotes(char *input)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			cont++;
		i++;
	}
	return (cont);
}

char	*ft_delete_quotes(char *input)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(input) - ft_count_quotes(input) + 1);
	i = 0;
	j = 0;
	while (input[i])
	{
		if(input[i] == 34 || input[i] == 39)
			i++;
		else
			res[j++] = input[i++];
	}
	res[j] = 0;
	free(input);
	return (res);
}
