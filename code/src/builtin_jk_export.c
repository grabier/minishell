/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jk_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:25:35 by jkubecka          #+#    #+#             */
/*   Updated: 2025/03/17 09:43:56 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

char	*ft_get_var_name(char *var)
{
	int		len;
	int		i;
	char	*var_name;

	len = 0;
	i = 0;
	while (var[len] && var[len] != '=')
		len++;
	var_name = (char *)malloc((len + 1) * sizeof(char));
	if (!var_name)
		return (NULL);
	while (i < len)
	{
		var_name[i] = var[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	**ft_insert_change(char **env, char *insert, int *changed)
{
	int		i;
	char	*var_name;
	char	*value;
	char	*new_value;

	i = 0;
	var_name = ft_get_var_name(insert);
	value = ft_strchr(insert, '=') + 1;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, ft_strlen(var_name))
			&& env[i][ft_strlen(var_name)] == '=')
		{
			free(env[i]);
			new_value = ft_strjoin(var_name, "=");
			env[i] = ft_strjoin(new_value, value);
			free(new_value);
			free(var_name);
			*changed = 1;
			return (env);
		}
		i++;
	}
	return (free(var_name), env);
}

char	**ft_insert_no_value(char **env, char *insert)
{
	char	**copy;
	int		i;
	char	*aux;
	int		changed;
	
	i = 0;
	/* aux = ft_strjoin("++", insert);
	ft_unset(env, aux);
	free(aux); */
	aux = ft_strjoin(insert, "=");
	if (!ft_strnstr(insert, aux, ft_strlen(insert) - 1))
	{
		free(aux);
		aux = ft_strjoin("++", insert);
		copy = (char **)malloc((ft_strlen_pointers(env) + 2) * sizeof(char *));
		while (env[i])
		{
			copy[i] = ft_strdup(env[i]);
			i++;
		}
		copy[i++] = ft_strdup(aux);
		copy[i] = NULL;
		return (ft_free_split_dp(env), free(aux), copy);
	}
	return (free(aux), env);
}

char	**ft_do_export(char **env, char *insert)
{
	char	**copy;
	int		i;
	char	*aux;
	int		changed;

	
	if (!ft_strchr(insert, '='))
		return (ft_insert_no_value(env, insert));
	i = 0;
	changed = 0;
	env = ft_insert_change(env, insert, &changed);
	if (changed == 1)
		return (env);
	if (!(copy = malloc((ft_strlen_pointers(env) + 1 + 1) * sizeof(char *))))
		return (NULL);
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = ft_strdup(insert);
	copy[++i] = NULL;
	ft_free_split_dp(env);
	return (copy);
}

char	**ft_export(char **env, char **insert)
{
	char	**copy;
	int		i;

	i = 1;
	copy = env;
	while (insert[i])
	{
		copy = ft_do_export(copy, insert[i]);
		i++;
	}
	return (copy);
}


