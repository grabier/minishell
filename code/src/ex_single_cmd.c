/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_single_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:33:39 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/11 19:40:19 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int		ft_open_n_redir(t_cmd *cmd, int mode)
{
	int	fd;
	
	if (mode == 0)
		fd = 0;
	else
		fd = 1;
	if (mode == 0 && cmd->infile && !cmd->hd)
	{
		fd = open(cmd->infile, O_RDONLY, 0777);
		if(!fd)
			exit(2);
		dup2(fd, STDIN_FILENO);
	}
	else if (mode == 1 && cmd->outfile && !cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 1 && cmd->outfile && cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if(fd < 0)
		exit(2);
	return (fd);
}

void	ft_exec_single_cmd(t_cmd *cmd, char *envp[])
{
	pid_t	pid;
	int		i_fd;
	int		o_fd;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	i_fd = ft_open_n_redir(cmd, 0);
	o_fd = ft_open_n_redir(cmd, 1);
	pid = fork();
	if (pid == 0)
	{
		//o_fd = ft_open_n_redir_out(cmd, 1);
		dup2(o_fd, STDOUT_FILENO);
		ft_execute_cmd(cmd, envp);
	}
	else
		waitpid(pid, NULL, 0);
	if (i_fd != 0)
		close(i_fd);
	if (o_fd != 1)
		close(o_fd);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	//printf("llegaaaaa\n");
}
