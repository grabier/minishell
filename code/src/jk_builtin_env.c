/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jk_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:25:35 by jkubecka          #+#    #+#             */
/*   Updated: 2025/02/28 19:23:56 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

static void	ft_free_split_dp(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split[i]);
	free(split);
}

char	**ft_unset(char **env_copy, char *str)
{
	char	**copy;
	int		i;
	int		pos;
	int		j;

	i = 0;
	pos = -1;
	j = 0;
	while (env_copy[i])
	{
		if (!ft_strncmp(str, env_copy[i], ft_strlen(str)))
			pos = i;
		i++;
	}
	if (pos == -1)
		return (env_copy);
	copy = (char **)malloc(ft_strlen_pointers(env_copy) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (env_copy[i])
	{
		if (i != pos)
			copy[j++] = ft_strdup(env_copy[i]);
		i++;
	}
	copy[j] = NULL;
	ft_free_split_dp(env_copy);
	return (copy);
}

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
	char	*other_value;

	i = 0;
	var_name = ft_get_var_name(insert);
	value = ft_strchr(insert, '=') + 1;
	new_value = ft_strjoin("\"", value);
	other_value = ft_strjoin(new_value, "\"");
	free(new_value);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, ft_strlen(var_name))
			&& env[i][ft_strlen(var_name)] == '=')
		{
			free(env[i]);
			new_value = ft_strjoin(var_name, "=");
			env[i] = ft_strjoin(new_value, other_value);
			free(other_value);
			free(new_value);
			free(var_name);
			*changed = 1;
			return (env);
		}
		i++;
	}
	return (free(other_value), free(var_name), env);
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
		ft_free_split_dp(env);
		free(aux);
		return (copy);
	}
	else
		return (free(aux), env);
}

char	**ft_insert_dp(char **env, char *insert)
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
	copy = (char **)malloc((ft_strlen_pointers(env) + 1 + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = ft_strdup(insert);
	i++;
	copy[i] = NULL;
	ft_free_split_dp(env);
	return (copy);
}


