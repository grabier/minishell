/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:55:41 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/15 16:13:52 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"
//hay que ejecutar los built ins por separado
int	ft_execute_cmd(t_cmd *cmd, char **envp[])
{
	/* if (cmd->is_bi)
	{
		//llamamos a la funcion para builtins
		ft_exec_built_in(cmd, envp);
		exit(1);
	} */
	if (execve(ft_find_path(cmd->args[0], *envp), cmd->args, *envp) == -1)
		exit(1);
	return (0);
}

void	ft_exec_commands(t_cmd *cmd_lst, char **envp[])
{
	int	i_fd;
	int	o_fd;
	
	if (!cmd_lst->next)//las redirecciones son distintas si no hay pipas
	{
		/* if (cmd_lst->is_bi)
			ft_exec_built_in(cmd_lst, envp);
		else */
			ft_exec_single_cmd(cmd_lst, envp);
	}
	else
		ft_exec_pipeline(cmd_lst, envp);
}
