/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jk_env_copy_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:49:57 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 17:31:24 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_strlen_pointers(char *env[])
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	*ft_strdup_jk(char *str)
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
