/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubecka <jkubecka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:39:29 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/18 19:39:30 by jkubecka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_exec_last_cmd(t_cmd *cmd, char **envp[], int	saved_stdin)
{
	pid_t	pid;
	int		i_fd;
	int		o_fd;

	i_fd = ft_open_n_redir(cmd, 0, saved_stdin);
	o_fd = ft_open_n_redir(cmd, 1, 0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		dup2(o_fd, STDOUT_FILENO);
		ft_execute_cmd(cmd, envp);
		return (0);
	}
	else
		return (pid);
	//waitpid(pid, NULL, 0);
	if (i_fd != 0)
		close(i_fd);
	if (o_fd != 1)
		close(o_fd);
}

int	ft_exec_middle_cmd(t_cmd *cmd, char **envp[], int i_fd, int o_fd)
{
	pid_t	pid;
	int		p[2];

	if (pipe(p) < 0)
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		close(p[0]);
		if (!cmd->outfile)
			dup2(p[1], STDOUT_FILENO);
		else
			dup2(o_fd, STDOUT_FILENO);
		ft_execute_cmd(cmd, envp);
		return (0);
	}
	else
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		if (!ft_strcmp(cmd->next->args[0], "head"))
			return (-1);
		//waitpid(pid, NULL, 0);
		return (pid);
	}
}

void	ft_exec_pipeline(t_cmd *cmd, char **envp[])
{
	int		i_fd;
	int		o_fd;
	int		size = ft_cmdsize(cmd);
	int		saved_stdin;
	int		saved_stdout;
	int		pids[size];
	int		i = 0;
	
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (cmd->next)
	{
		i_fd = ft_open_n_redir(cmd, 0, saved_stdin);
		o_fd = ft_open_n_redir(cmd, 1, 0);
		pids[i] = ft_exec_middle_cmd(cmd, envp, i_fd, o_fd);
		if (i_fd != 0)
			close(i_fd);
		if (o_fd != 1)
			close(o_fd);
		i++;
		cmd = cmd->next;
	}
	/* i_fd = ft_open_n_redir(cmd, 0);
	o_fd = ft_open_n_redir(cmd, 1); */
	pids[i] = ft_exec_last_cmd(cmd, envp, saved_stdin);
	i = 0;
	while (i < size)
		waitpid(pids[i++], NULL, 0);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	/* if (i_fd != 0)
		close(i_fd);
	if (o_fd != 1)
		close(o_fd); */
}
