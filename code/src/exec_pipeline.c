/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:39:29 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:27:13 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_exec_last_cmd(t_shell *ms, char **envp[], int saved_stdin)
{
	pid_t	pid;
	int		i_fd;
	int		o_fd;

	i_fd = ft_open_n_redir(ms->cmd_lst, 0, saved_stdin, ms);
	o_fd = ft_open_n_redir(ms->cmd_lst, 1, 0, ms);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup2(o_fd, STDOUT_FILENO);
		if (!ms->cmd_lst->is_bi)
			ft_execute_cmd(ms, envp);
		else
		{
			ft_exec_built_in(ms, envp);
			exit(1);
		}
	}
	g_signal_flag = 1;
	return (pid);
	ft_close_if_needed(i_fd, o_fd);
}

void	ft_do_middle_process(t_shell *ms, char **envp[])
{
	signal(SIGINT, SIG_DFL);
	if (!ms->cmd_lst->is_bi)
		ft_execute_cmd(ms, envp);
	else
	{
		ft_exec_built_in(ms, envp);
		exit(1);
	}
}

int	ft_exec_middle_cmd(t_shell *ms, char **envp[], int i_fd, int o_fd)
{
	pid_t	pid;
	int		p[2];

	(void)i_fd;
	if (pipe(p) < 0)
		return (0);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(p[0]);
		if (!ms->cmd_lst->outfile)
			dup2(p[1], STDOUT_FILENO);
		else
			dup2(o_fd, STDOUT_FILENO);
		ft_do_middle_process(ms, envp);
	}
	g_signal_flag = 1;
	close(p[1]);
	dup2(p[0], STDIN_FILENO);
	if (ms->cmd_lst->next && !ft_strcmp(ms->cmd_lst->next->args[0], "head"))
		return (-1);
	return (pid);
}

void	ft_check_signals(t_shell *ms)
{
	if (WIFEXITED(ms->exitstat))
		ms->exitstat = WEXITSTATUS(ms->exitstat);
	else if (WIFSIGNALED(ms->exitstat))
		ms->exitstat = 128 + WTERMSIG(ms->exitstat);
}

void	ft_exec_pipeline(t_shell *ms, char **envp[], int i)
{
	int		i_fd;
	int		o_fd;
	int		size;
	int		saved_stdin;
	int		pids[100];

	ms->head = ms->cmd_lst;
	size = ft_cmdsize(ms->cmd_lst);
	saved_stdin = dup(STDIN_FILENO);
	while (ms->cmd_lst->next)
	{
		i_fd = ft_open_n_redir(ms->cmd_lst, 0, saved_stdin, ms);
		o_fd = ft_open_n_redir(ms->cmd_lst, 1, 0, ms);
		pids[i++] = ft_exec_middle_cmd(ms, envp, i_fd, o_fd);
		ft_close_if_needed(i_fd, o_fd);
		ms->cmd_lst = ms->cmd_lst->next;
	}
	pids[i] = ft_exec_last_cmd(ms, envp, saved_stdin);
	i = 0;
	while (i < size)
		waitpid(pids[i++], &ms->exitstat, 0);
	ft_check_signals(ms);
	dup2(saved_stdin, STDIN_FILENO);
	ms->cmd_lst = ms->head;
}
