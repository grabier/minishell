/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jk_env_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:08:06 by jkubecka          #+#    #+#             */
/*   Updated: 2025/02/18 17:28:23 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//checkear si existe ya la variable    insert==export
//limpiar todo + comentarios + dividirlo en 2 archivos y pasarlo a gabri

#include "../parseo.h"


int	ft_strlen_pointers(char *env[]) //para saber cuantas variables en env
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	*ft_strdup_jk(char *str) //para copiar las lineas de cada variables de env
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(ft_strlen(str) * sizeof(char) + 1);
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**ft_copy_dp(char **env) //para copiar solo el primero puntero con las lineas
{
	char	**copy;
	int		i;

	i = 0;
	copy = (char **)malloc((ft_strlen_pointers(env) + 2) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = ft_strdup("_=/usr/bin/env");
	i++;
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
}

void	print_env_export(char **env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i])
	{
		if (env_copy[i][0] != '_' && env_copy[i][0] != '+' && env_copy[i][1] != '+')
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









/* int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	
	char **copy;
	copy = ft_copy_dp(env);
	int i = 0;
	while(copy[i])
	{
		printf("%s\n", copy[i]);
		i++;
	}
	char **newc;
	newc = ft_insert_dp(copy, "JENNY");
	newc = ft_insert_dp(newc, "GABI");
	newc = ft_insert_dp(newc, "noe");
	newc = ft_insert_dp(newc, "jr");
	newc = ft_unset(newc, "JENNY");
	newc = ft_unset(newc, "GABI");
	i = 0;
	while(newc[i])
	{
		printf("%s\n", newc[i]);
		i++;
	}
	//ft_free_split(copy);
	ft_free_split(newc);
} */