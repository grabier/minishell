/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:28:35 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/05 11:08:06 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	/* printf("s1: %s\n", s1);
	printf("s2: %s\n", s2); */
	if (!s1 || !s2)
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

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