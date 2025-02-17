/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:03:57 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/17 17:23:45 by gmontoro         ###   ########.fr       */
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
	if (access(re, X_OK) == -1)
	{
		return (free(re), NULL);
	}
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
		result = ft_strcat_cmd(split[i], cmd);
		//printf("rsult: %s\n", result);
		if (result)
			break ;
		free(result);
		i++;
	}
	if (!split[i] || !result)
		return (ft_free_split(split));
	else
		return (ft_free_split(split), result);
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
	if (envp[i])
		path = envp[i] + 4;
	else
		return (NULL);
	if (!ft_find_cmd(cmd, path))
	{
		printf("%s: command not found\n", cmd);
		return (free(res), NULL);
	}
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
