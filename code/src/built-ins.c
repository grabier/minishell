/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:23:59 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:30:15 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

void	ft_exec_built_in(t_shell *ms, char **envp[])
{
	if (!ft_strcmp(ms->cmd_lst->args[0], "env"))
		print_env(*envp);
	else if (!ft_strcmp(ms->cmd_lst->args[0], "export"))
	{
		if (ms->cmd_lst->args[1])
			*envp = ft_export(*envp, ms->cmd_lst->args);
		else
			print_env_export(*envp);
	}
	else if (!ft_strcmp(ms->cmd_lst->args[0], "unset"))
		*envp = ft_unset(*envp, ms->cmd_lst->args);
	else if (!ft_strcmp(ms->cmd_lst->args[0], "cd"))
		ms->exitstat = ft_cd(envp, ms->cmd_lst);
	else if (!ft_strcmp(ms->cmd_lst->args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(ms->cmd_lst->args[0], "echo"))
		ft_echo(ms->cmd_lst, ms);
	else if (!ft_strcmp(ms->cmd_lst->args[0], "exit"))
		ft_exit(ms);
	else
		return ;
}
