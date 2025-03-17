/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:15:25 by gmontoro          #+#    #+#             */
/*   Updated: 2024/10/05 15:39:10 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	unsigned long		i;

	i = 0;
	result = malloc(count * size);
	while (i < count * size)
		((char *)result)[i++] = '\0';
	return (result);
}
