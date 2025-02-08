/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:55:41 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/08 20:10:28 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_execute_cmd(char **args, char *envp[])
{
	if (execve(ft_find_path(args[0], envp), args, envp) == -1)
		exit(1);
	return (0);
}

void	ft_exec_commands(t_cmd *cmd_lst, char *envp[])
{
	pid_t pid;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		ft_execute_cmd(cmd_lst->args, envp);
	waitpid(pid, NULL, 0);
	return ;
}