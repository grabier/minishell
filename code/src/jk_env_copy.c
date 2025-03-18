/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jk_env_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:08:06 by jkubecka          #+#    #+#             */
/*   Updated: 2025/03/18 17:32:43 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

char	**ft_hardcode_env(void)
{
	char	**c;
	char	*a;

	a = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/sbin:/bin";
	c = (char **)malloc((3) * sizeof(char *));
	c[0] = ft_strdup("SHLVL=0");
	c[1] = ft_strdup(a);
	c[2] = NULL;
	return (c);
}

char	**ft_copy_env(char **env)
{
	char	**copy;
	int		i;

	i = 0;
	if (!env[i])
		return (ft_hardcode_env());
	copy = (char **)malloc((ft_strlen_pointers(env) + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	print_env(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
	{
		if (env_copy[i][0] != '+' && env_copy[i][1] != '+')
			printf("%s\n", env_copy[i]);
		i++;
	}
	printf("%s\n", "_=/usr/bin/env");
}

void	print_env_export(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
	{
		if (env_copy[i][0] != '_'
				&& env_copy[i][0] != '+' && env_copy[i][1] != '+')
		{
			printf("declare -x ");
			printf("%s\n", env_copy[i]);
		}
		if (env_copy[i][0] == '+' && env_copy[i][1] == '+')
		{
			printf("declare -x ");
			printf("%s\n", &env_copy[i][2]);
		}
		i++;
	}
}
