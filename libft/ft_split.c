/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:05:18 by gmontoro          #+#    #+#             */
/*   Updated: 2024/05/10 17:52:35 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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






/* #include "libft.h"

static size_t	ft_wordcount(char *s, char c)
{
	size_t	count;
	size_t	i;

	if (!s)
		return (0);
	if (!ft_strlen(s))
		return (0);
	i = 0;
	count = s[i] != c;
	while (s[i])
	{
		count += (s[i] == c && s[i + 1] != c && s[i + 1] != '\0');
		i++;
	}
	return (count);
}

static int	ft_next_worlen(char const *s, int i, char c)
{
	int	count;

	count = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\0')
			return (count);
		i++;
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	tab_index;
	size_t	end;
	char	**tab;

	tab = ft_calloc(ft_wordcount((char *)s, c) + 1, sizeof(char *));
	if (!tab || !s)
		return (NULL);
	i = 0;
	tab_index = 0;
	while (tab_index < ft_wordcount((char *)s, c))
	{
		while (s[i] == c)
			i++;
		end = ft_next_worlen(s, i, c);
		tab[tab_index] = ft_substr(s, i, end);
		i += end;
		tab_index++;
		i++;
	}
	return (tab);
} */

/* void ft_leaks(void)
{
	system("leaks -q a.out");
}

#include <stdio.h>

int main()
{
	//char *pr = "hello!";
	char **sp = ft_split("hello!", ' ');
	//int n1 = ft_cword(pr, ' ');
	atexit(ft_leaks);
	//printf("palabras: %i\n", n1);
	//printf("letras: %i\n", ft_cletter(&pr[13], ' '));
	int i = 0;
	while (i < 1)
	{
		printf("palabra %i: %s\n", i, sp[i]);
		i++;
	} 
	return (0);
}  */