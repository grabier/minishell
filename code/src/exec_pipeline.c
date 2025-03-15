/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:39:29 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/14 20:26:42 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"
//el ultimo comando va algo distinto, ya que la redir out ultima no es
//a una pipa, sino al STDOUT o a un outfile
int	ft_exec_last_cmd(t_shell *ms, char **envp[], int	saved_stdin)
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
		if(!ms->cmd_lst->is_bi)
			ft_execute_cmd(ms, envp);
		else
		{
			ft_exec_built_in(ms, envp);
			exit(1);//tenemos que matarlo pq no hay execve
		}
		return (0);
	}
	else
	{
		signal_flag = 1;
		return (pid);
	}
	//waitpid(pid, NULL, 0);
	if (i_fd != 0)
		close(i_fd);
	if (o_fd != 1)
		close(o_fd);
}

int	ft_exec_middle_cmd(t_shell *ms, char **envp[], int i_fd, int o_fd)
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
		signal(SIGINT, SIG_DFL);
		close(p[0]);
		if (!ms->cmd_lst->outfile)
			dup2(p[1], STDOUT_FILENO);
		else
			dup2(o_fd, STDOUT_FILENO);
		if(!ms->cmd_lst->is_bi)
			ft_execute_cmd(ms, envp);
		else
		{
			ft_exec_built_in(ms, envp);
			exit(1);//tenemos que matarlo pq no hay execve
		}
		return (0);
	}
	else//cuando estas en el padre, pid contiene el process id del hijo
	{
		signal_flag = 1;
		close(p[1]);
		dup2(p[0], STDIN_FILENO);//dupeamos el stdin en el proceso padre
		//para que el siguiente comando lea de la pipa
		if (ms->cmd_lst->next && !ft_strcmp(ms->cmd_lst->next->args[0], "head"))
			return (-1);
		//waitpid(pid, NULL, 0);
		return (pid);
	}
}

void	ft_exec_pipeline(t_shell *ms, char **envp[])
{
	int		i_fd;
	int		o_fd;
	int		size = ft_cmdsize(ms->cmd_lst);
	int		saved_stdin;
	int		saved_stdout;
	int		pids[size];
	int		i = 0;
	
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	t_cmd *head = ms->cmd_lst;
	while (ms->cmd_lst->next)//del primero al penultimo
	{
		i_fd = ft_open_n_redir(ms->cmd_lst, 0, saved_stdin, ms);//el infile lo dupeamos 
		o_fd = ft_open_n_redir(ms->cmd_lst, 1, 0, ms);//el outfile no
		pids[i] = ft_exec_middle_cmd(ms, envp, i_fd, o_fd);
		if (i_fd != 0)
			close(i_fd);
		if (o_fd != 1)
			close(o_fd);
		i++;
		ms->cmd_lst = ms->cmd_lst->next;
	}
	pids[i] = ft_exec_last_cmd(ms, envp, saved_stdin);//ultimo comando a parte
	i = 0;//pq las redirecciones son distintas(no devuelve a una pipe)
	while (i < size)
		waitpid(pids[i++], &ms->exitstat, 0);
	if (WIFEXITED(ms->exitstat))
		ms->exitstat = WEXITSTATUS(ms->exitstat);  // Extraer correctamente el exit status
	else if (WIFSIGNALED(ms->exitstat))
		ms->exitstat = 128 + WTERMSIG(ms->exitstat);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	ms->cmd_lst = head;
}
