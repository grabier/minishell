/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:05:09 by gmontoro          #+#    #+#             */
/*   Updated: 2024/04/20 19:11:57 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_copy;
	char	*src_copy;

	if (dst == 0 && src == 0)
		return (NULL);
	i = 0;
	dst_copy = (char *)dst;
	src_copy = (char *)src;
	while (i < n)
	{
		dst_copy[i] = src_copy[i];
		i++;
	}
	return (dst);
}
