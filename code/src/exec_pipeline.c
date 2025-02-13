/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:39:29 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/13 11:32:47 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

void	ft_exec_last_cmd(t_cmd *cmd, char *envp[])
{
	pid_t	pid;
	int		i_fd;
	int		o_fd;

	i_fd = ft_open_n_redir(cmd, 0);
	o_fd = ft_open_n_redir(cmd, 1);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		dup2(o_fd, STDOUT_FILENO);
		ft_execute_cmd(cmd, envp);
	}
	else
		waitpid(pid, NULL, 0);
	if (i_fd != 0)
		close(i_fd);
	if (o_fd != 1)
		close(o_fd);
}

void	ft_exec_middle_cmd(t_cmd *cmd, char *envp[], int i_fd, int o_fd)
{
	pid_t	pid;
	int		p[2];

	if (pipe(p) < 0)
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		close(p[0]);
		if (!cmd->outfile)
			dup2(p[1], STDOUT_FILENO);
		else
			dup2(o_fd, STDOUT_FILENO);
		ft_execute_cmd(cmd, envp);
	}
	else
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		//waitpid(pid, NULL, 0);
	}
}

void	ft_exec_pipeline(t_cmd *cmd, char *envp[])
{
	int		i_fd;
	int		o_fd;
	int		saved_stdin;
	int		pids[ft_cmdsize(cmd)];
	
	saved_stdin = dup(STDIN_FILENO);
	while (cmd->next)
	{
		i_fd = ft_open_n_redir(cmd, 0);
		o_fd = ft_open_n_redir(cmd, 1);
		ft_exec_middle_cmd(cmd, envp, i_fd, o_fd);
		if (i_fd != 0)
			close(i_fd);
		if (o_fd != 1)
			close(o_fd);
		cmd = cmd->next;
	}
	/* i_fd = ft_open_n_redir(cmd, 0);
	o_fd = ft_open_n_redir(cmd, 1); */
	ft_exec_last_cmd(cmd, envp);
	dup2(saved_stdin, STDIN_FILENO);
	/* if (i_fd != 0)
		close(i_fd);
	if (o_fd != 1)
		close(o_fd); */
}
