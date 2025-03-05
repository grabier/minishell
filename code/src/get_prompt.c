/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:06:54 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/03 10:26:24 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

char *ft_trim_session_manager(char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '/')
		i++;
	i++;
	while (s[i] && s[i] != '.')
	{
		j++;
		i++;
	}
	res = malloc(j + 2);
	i = 0;
	while (s[i] && s[i] != '/')
		i++;
	i++;
	j = 0;
	while (s[i] && s[i] != '.')
		res[j++] = s[i++];
	res[j] = '\0';
	free(s);
	return (res);
}

char *ft_get_session_manager(char **env)
{
	int		i;
	int		j;
	char	*aux;
	char	*res;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SESSION_MANAGER=", 16))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	aux = ft_strdup(&env[i][16]);
	//printf("aux: %s\n", aux);
	return (ft_trim_session_manager(aux));
}

char *ft_get_user(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp((const char *)env[i], "USER=", 5))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	else
		return (ft_strdup(&env[i][5]));
}

char *ft_trim_pwd(void)
{
	char	*aux;
	char	*res;
	int		i;
	int		cont;

	i = 0;
	cont = 0;
	aux = getcwd(NULL, 0);
	while (aux[i] && cont < 3)
	{
		if (aux[i] =='/')
			cont++;
		i++;
	}
	res = ft_strdup(&aux[i - 1]);
	free(aux);
	return (res);
}

char *ft_put_together(char *u, char *s, char *p)
{
	int		i;
	int		j;
	char	*res;

	if (!u || !s || !p)
		return (NULL);
	i = 0;
	j = 0;
	res = malloc(ft_strlen(u) + ft_strlen(s) + ft_strlen(p) + 6);
	while (u[i])
		res[j++] = u[i++];
	res[j] = '@';
	i = 0;
	j++;
	while (s[i])
		res[j++] = s[i++];
	res[j++] = ':';
	res[j++] = '~';
	i = 0;
	while (p[i])
		res[j++] = p[i++];
	res[j++] = '$';
	res[j++] = ' ';
	res[j] = '\0';
	return (res);
}

char *ft_get_prompt(char **env)
{
	char	*s;
	char	*res;
	char	*p;
	char	*u;

	//printf("env: %s\n", env[0]);
	if (!env[0])
		return (ft_strdup("minishell>"));
	u = ft_get_user(env);
	s = ft_get_session_manager(env);
	p = ft_trim_pwd();
	res = ft_put_together(u, s, p);
	//printf("res: %s\n", res);
	if (u)
		free(u);
	if (s)
		free(s);
	if (p)
		free(p);
	if (!res)
		return (ft_strdup("minishell>"));
	return (res);
}
