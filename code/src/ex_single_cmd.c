/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_single_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:33:39 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:13:11 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_open_n_redir(t_cmd *cmd, int mode, int saved_stdin, t_shell *ms)
{
	int	fd;

	if (mode == 0)
		fd = 0;
	else
		fd = 1;
	if (mode == 0 && cmd->infile && !cmd->hd)
	{
		fd = open(cmd->infile, O_RDONLY, 0777);
		if (fd < 0)
			return (-1);
		dup2(fd, STDIN_FILENO);
	}
	else if (mode == 0 && cmd->infile && cmd->hd)
	{
		dup2(saved_stdin, STDIN_FILENO);
		fd = ft_here_doc(cmd->infile, ms);
		dup2(fd, STDIN_FILENO);
	}
	else if (mode == 1 && cmd->outfile && !cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 1 && cmd->outfile && cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}

void	ft_close_if_needed(int i_fd, int o_fd)
{
	if (i_fd != 0)
		close(i_fd);
	if (o_fd != 1)
		close(o_fd);
}

void	ft_exec_single_cmd(t_shell *ms, char **envp[])
{
	pid_t	pid;
	int		i_fd;
	int		o_fd;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	i_fd = ft_open_n_redir(ms->cmd_lst, 0, saved_stdin, ms);
	o_fd = ft_open_n_redir(ms->cmd_lst, 1, 0, ms);
	if (i_fd < 0 || o_fd < 0 || ms->exitstat == 130)
		return ;
	pid = fork();
	if (pid == 0)
	{
		dup2(o_fd, STDOUT_FILENO);
		if (!ms->cmd_lst->is_bi)
			ft_execute_cmd(ms, envp);
	}
	g_signal_flag = 1;
	waitpid(pid, &ms->exitstat, 0);
	if (WIFEXITED(ms->exitstat))
		ms->exitstat = WEXITSTATUS(ms->exitstat);
	else if (WIFSIGNALED(ms->exitstat))
		ms->exitstat = 128 + WTERMSIG(ms->exitstat);
	ft_close_if_needed(i_fd, o_fd);
	dup2(saved_stdin, STDIN_FILENO);
}
