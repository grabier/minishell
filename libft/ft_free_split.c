/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:04:06 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/15 15:10:32 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_free_split(char **split)
{
	int	i;

	i = 0;
	//printf("entra a free split\n");
	if (!split || !split[0])
		return (NULL);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	//printf("free split\n");
	free(split);
	return (NULL);
}