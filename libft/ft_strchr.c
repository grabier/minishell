/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:32:01 by gmontoro          #+#    #+#             */
/*   Updated: 2024/04/20 19:06:14 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if ((char)c == 0)
		return (&((char *)s)[ft_strlen(s)]);
	while (*s)
	{
		if (*s == (char)c)
			return (((char *)s));
		s++;
	}
	return (NULL);
}
