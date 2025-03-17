/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:30:48 by gmontoro          #+#    #+#             */
/*   Updated: 2024/04/20 19:13:44 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*src_copy;
	char	*dst_copy;
	size_t	i;

	if (dst == 0 && src == 0)
		return (NULL);
	src_copy = (char *)src;
	dst_copy = (char *)dst;
	i = 0;
	if (dst_copy > src_copy)
		while (len-- > 0)
			dst_copy[len] = src_copy[len];
	else
	{
		while (i < len)
		{
			dst_copy[i] = src_copy[i];
			i++;
		}
	}
	return (dst);
}
