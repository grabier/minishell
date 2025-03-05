/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:53:32 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/05 10:52:59 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_find_end_sq(char *input)
{
	int	i;

	i = 1;
	while (input[i] != 39 && input[i])
		i++;
	if (!input[i])
		return (printf("sq end not found\n"), 0);
	return (i + 1);
}

int	ft_find_end_dq(char *input)
{
	int	i;

	i = 1;
	while (input[i] != 34 && input[i])
		i++;
	if (input[i] == '\0')
		return(0);
	return (i + 1);
}

void	ft_free_tkn_lst(t_tkn **tkn)
{
	t_tkn *aux;

	while (*tkn)
	{
		aux = (*tkn)->next;
		//printf("freed token %s\n", (*tkn)->token);
		free((*tkn)->token);
		free(*tkn);
		*tkn = aux;
	}
}