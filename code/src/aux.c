/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:28:35 by gmontoro          #+#    #+#             */
/*   Updated: 2025/01/29 12:06:00 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

char	*ft_strinsert(char *str, char *word, int start, int end)
{
	int	i;
	int	j;
	char	*res;
	
	i = -1;
	j = 0;
	//printf("start: %i\n", start);
	//printf("end: %i\n", end);
	res = malloc(ft_strlen(str) - (end - start) + ft_strlen(word) + 1);
	while (++i < start)
		res[i] = str[i];
	while (word[j])
		res[i++] = word[j++];
	end++;
	while (str[end])
		res[i++] = str[end++];
	res[i] = '\0';
	return (res);
}

void	ft_printsplit(char **sp)
{
	int	i;

	i = -1;
	while (sp[++i])
		printf("[%s]\n", sp[i]);
}