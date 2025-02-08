/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:03:57 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/08 20:06:02 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

char	*ft_strcat_cmd(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*re;

	i = 0;
	re = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1[i])
	{
		re[i] = s1[i];
		i++;
	}
	re[i] = '/';
	j = i + 1;
	i = 0;
	while (s2[i])
	{
		re[j] = s2[i];
		i++;
		j++;
	}
	re[j] = '\0';
	return (re);
}

char	*ft_find_cmd(char *cmd, char *path)
{
	char	**split;
	char	*result;
	int		i;

	if (!path || !cmd)
		return (NULL);
	split = ft_split(path, ':');
	if (!split)
		return (ft_free_split(split), NULL);
	i = 0;
	while (split[i])
	{
		if (!access(ft_strcat_cmd(split[i], cmd), X_OK))
			break ;
		i++;
	}
	if (!split[i])
		return (ft_free_split(split), NULL);
	else
	{
		result = ft_strcat_cmd(split[i], cmd);
		return (ft_free_split(split), result);
	}
}

char	*aux_find_path(char *cmd, char *envp[], char *res, int i)
{
	char	*path;

	while (envp[i])
	{
		if (!ft_strncmp((const char *)envp[i], "PWD=", 4))
			break ;
		i++;
	}
	path = envp[i] + 4;
	if (!ft_find_cmd(cmd, path))
		return (free(res), NULL);
	return (free(res), ft_find_cmd(cmd, path));
}

char	*ft_find_path(char *cmd, char *envp[])
{
	int		i;
	char	*path;
	char	*res;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp((const char *)envp[i], "PATH=", 5))
			break ;
		i++;
	}
	path = envp[i];
	i = 0;
	res = ft_find_cmd(cmd, path);
	if (!res)
		return (aux_find_path(cmd, envp, res, i));
	return (res);
}
