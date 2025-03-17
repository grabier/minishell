/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_single_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:33:39 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/17 10:11:30 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"
//devuelve el fd de infile/outfile, 0, y 1 por defecto
//pero consideramos las redirecciones

int		ft_open_n_redir(t_cmd *cmd, int mode, int saved_stdin, t_shell *ms)
{
	int	fd;
	
	if (mode == 0)//mode 0 ->infile
		fd = 0;
	else//mode 1 -> outfile
		fd = 1;
	if (mode == 0 && cmd->infile && !cmd->hd)
	{
		fd = open(cmd->infile, O_RDONLY, 0777);
		if(fd < 0)
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

	saved_stdin = dup(STDIN_FILENO);//las redirecciones in las gestionamos 
	i_fd = ft_open_n_redir(ms->cmd_lst, 0, saved_stdin, ms);//en la funcion open_n_redir, asi que hay que
	o_fd = ft_open_n_redir(ms->cmd_lst, 1, 0, ms);//guardar una copia del STDIN para devolverlo
	if (i_fd < 0 || o_fd < 0 || ms->exitstat == 130)
		return ;
	pid = fork();
	if (pid == 0)//dupeamos la salida out en el hijo para no tener que preocuparnos
	{
		dup2(o_fd, STDOUT_FILENO);//los dups realizados en procesos hijos
		if (!ms->cmd_lst->is_bi)
			ft_execute_cmd(ms, envp);//no afectan al proceso padre
	}
	signal_flag = 1;
	waitpid(pid, &ms->exitstat, 0);
	if (WIFEXITED(ms->exitstat))
		ms->exitstat = WEXITSTATUS(ms->exitstat);  // Extraer correctamente el exit status
	else if (WIFSIGNALED(ms->exitstat))
		ms->exitstat = 128 + WTERMSIG(ms->exitstat);
	ft_close_if_needed(i_fd, o_fd);
	dup2(saved_stdin, STDIN_FILENO);//devolvemos STDIN a lo original
}
