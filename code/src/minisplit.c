/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:41:31 by gmontoro          #+#    #+#             */
/*   Updated: 2025/01/27 16:52:50 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

static int	ft_cword(const char *s, char c)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	if (s[0] == '\0')
		return (0);
	if (s[0] != c && s[0] != '\0')
		cont++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c & s[i + 1] != '\0')
			cont++;
		i++;
	}
	if (cont == 0 && s[i - 1] != c)
		return (1);
	return (cont);
}

static int	ft_cletter(const char *s, char c)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		cont++;
		i++;
	}
	return (cont);
}

static char	*ft_free(char **s, int index, int size)
{
	int	i;

	i = 0;
	s[index] = (char *)malloc(size);
	if (!s[index])
	{
		while (i <= index)
		{
			free(s[i]);
			i++;
		}
		return (NULL);
	}
	return (s[index]);
}

char	**ft_split(const char *s, char c)
{
	char	**sp;
	int		i;
	int		cont[3];

	i = 0;
	while (i < 3)
		cont[i++] = 0;
	sp = (char **)malloc((sizeof(char *)) * (ft_cword(s, c) + 1));
	if (!s || !sp)
		return (NULL);
	while (cont[0] < ft_cword(s, c))
	{
		sp[cont[0]] = ft_free(sp, cont[0], ft_cletter(&s[cont[2]], c) + 1);
		if (sp[cont[0]] == NULL)
			return (free(sp), NULL);
		while (s[cont[2]] == c)
			cont[2]++;
		while (s[cont[2]] != c && s[cont[2]] != '\0')
			sp[cont[0]][cont[1]++] = s[cont[2]++];
		sp[cont[0]++][cont[1]] = '\0';
		cont[1] = 0;
	}
	sp[cont[0]] = NULL;
	return (sp);
}
