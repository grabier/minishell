/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:37:34 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 17:28:52 by gmontoro         ###   ########.fr       */
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

char	*ft_check_return(char *input, char *res)
{
	if (res)
		return (free(input), res);
	else
		return (free(res), input);
}

int	f(int i, int j, int k, int f)
{
	if (f == 0)
	{
		if (i != '$')
		{
			if (j != 34)
			{
				if (k != 32 || k == 0)
					return (0);
			}
		}
	}
	else
	{
		if (i == '$')
		{
			if (j != 34)
			{
				if (k != 32 || k == 0)
					return (0);
			}
		}
	}
	return (1);
}
