/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:34:45 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:29:18 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

char	**ft_get_dp(char *aux)
{
	char	**dp;

	dp = malloc(sizeof(char *) * 3);
	dp[0] = ft_strdup("export");
	dp[1] = ft_strdup(aux);
	dp[2] = NULL;
	return (dp);
}

char	**ft_unset_in_cd(char **env, char *str)
{
	char	**insert;
	char	**envc;

	insert = ft_get_dp(str);
	envc = ft_unset(env, insert);
	ft_free_split(insert);
	return (envc);
}

char	*ft_getenv(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var))
			&& env[i][ft_strlen(var)] == '=')
			return (ft_strdup(&env[i][ft_strlen(var) + 1]));
		i++;
	}
	return (NULL);
}
