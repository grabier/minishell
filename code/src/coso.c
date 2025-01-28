/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coso.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:15:12 by gmontoro          #+#    #+#             */
/*   Updated: 2025/01/27 18:34:17 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_splitsize(char **sp)
{
	int	i;

	i = 0;
	while (sp[i])
		i++;
	return (i);
}

void	ft_freesplit(char **sp)
{
	int	size;
	int	i;

	i = 0;
	size = ft_splitsize(sp);
	while(i <= size)
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}

char	*ft_strinsert(char *str, char *word, int start, int end)
{
	int	i;
	int	j;
	char	*res;
	
	printf("DEBUGGER\n");
	printf("res: %i\n", end);
	i = 0;
	j = 0;
	res = malloc(ft_strlen(str) - (end - start) + ft_strlen(word));
	while (i < start)
		res[i] = str[i++];
	while (word[j])
		res[i++] = word[j++];
	while (str[end])
		res[i++] = str[end++];
	res[i]  = '\0';
	return (res);
}


char	**ft_splitjoin(char **sp1, char **sp2)
{
	char	**ret;
	int		i;
	int		j;
	int		size;

	size = (ft_splitsize(sp1) + ft_splitsize(sp2));
	ret = malloc(sizeof(char *) * (size + 1));
	i = -1;
	j = 0;
	while (++i < ft_splitsize(sp1))
		ret[i] = ft_strdup(sp1[i]);
	//i--;
	while (j < ft_splitsize(sp2))
		ret[i++] = ft_strdup(sp2[j++]);
	ret[i] = NULL;
	ft_freesplit(sp1);
	ft_freesplit(sp2);
	return (ret);
}

/* char	**ft_parse_input(char *input)
{
	char	**tokens;

	
} */

int main()
{
	char **sp1 = ft_split("hola me llamo", ' ');
	char **sp2 = ft_split("Paco y soy de Valle", ' ');
	char **ret = ft_splitjoin(sp1, sp2);
	int i = 0;
	printf("DEBUGGER\n");
	while (ret[i])
	{
		printf(": %s\n", ret[i]);
		i++;
	}
	ft_freesplit(ret);
	return (0);
}