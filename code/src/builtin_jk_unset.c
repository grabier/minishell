/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jk_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:25:35 by jkubecka          #+#    #+#             */
/*   Updated: 2025/03/17 09:44:16 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

void	ft_free_split_dp(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split[i]);
	free(split);
}

int	ft_len_to_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (0);
	else
		return (i);
}

char	**ft_copy_dp(char **src, int pos)
{
	int		i;
	int		j;
	char	**copy;
	
	i = 0;
	j = 0;
	copy = (char **)malloc(ft_strlen_pointers(src) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (src[i])
	{
		if (i != pos)
		copy[j++] = ft_strdup(src[i]);
		i++;
	}
	copy[j] = NULL;
	ft_free_split_dp(src);
	return (copy);
}

char	**ft_do_unset(char **env_copy, char *str)
{
	int		i;
	int		pos;
	
	i = 0;
	pos = -1;
	while (env_copy[i])
	{
		if (!ft_strncmp(str, env_copy[i], ft_len_to_equal(env_copy[i])))
		pos = i;
		i++;
	}
	if (pos == -1)
		return (env_copy);
	return (ft_copy_dp(env_copy, pos));
}

char	**ft_unset(char **env_copy, char **str)
{
	char	**copy;
	int		i;

	i = 1;
	copy = env_copy;
	while (str[i])
	{
		copy = ft_do_unset(copy, str[i]);
		i++;
	}
	return (copy);
}
