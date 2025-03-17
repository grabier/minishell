/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:22:20 by gmontoro          #+#    #+#             */
/*   Updated: 2024/04/21 18:11:36 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char			*trimmed;
	unsigned int	s;
	unsigned int	f;
	unsigned int	aux;

	s = 0;
	f = ft_strlen(s1);
	while (ft_strchr(set, s1[s]) != NULL && s < f)
		s++;
	while (ft_strchr(set, s1[f]) != NULL && f > s)
		f--;
	f++;
	if (s1[s] == '\0')
		aux = 1;
	else
		aux = f - s + 1;
	trimmed = (char *)malloc((sizeof(char)) * (aux));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, &s1[s], f - s + 1);
	return (trimmed);
}
