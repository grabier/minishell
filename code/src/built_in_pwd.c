/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:11:55 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/17 09:38:58 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_pwd(char ***env, t_cmd *cmd)
{
	char *aux;

	if (cmd->args[1])
		return (printf("pwd: too many arguments\n"), 0);
	aux = getcwd(NULL, 0);
	printf("%s\n", aux);
	free(aux);
	return (1);
}
