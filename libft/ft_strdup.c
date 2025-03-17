/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:26:46 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/15 19:13:57 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	result = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!result)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		result[i] = ((char *)s1)[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
