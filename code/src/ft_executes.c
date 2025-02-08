/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:27:15 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/08 20:08:06 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_execute_cmd(char *cmd, char *envp[])
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		return (0);
	if (execve(ft_find_path(args[0], envp), args, envp) == -1)
		exit(1);
	return (0);
}
