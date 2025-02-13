/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:23:59 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/13 17:11:54 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

void	ft_exec_built_in(t_cmd *cmd, char **envp[])
{
	if (!ft_strcmp(cmd->args[0], "env"))
		print_env(*envp);
	else if (!ft_strcmp(cmd->args[0], "export"))
	{
		if (cmd->args[1])
			*envp = ft_insert_dp(*envp, cmd->args[1]);
		else
			print_env_export(*envp);
	}
	else if (!ft_strcmp(cmd->args[0], "unset"))
		*envp = ft_unset(*envp, cmd->args[1]);
	/* else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo();
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd();
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(); */
}