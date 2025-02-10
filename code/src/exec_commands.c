/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:55:41 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/10 15:30:19 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_execute_cmd(char **args, char *envp[])
{
	char	*cmd;

	if (execve(ft_find_path(args[0], envp), args, envp) == -1)
		exit(1);
	return (0);
}


int	ft_redir_n_exec(char **cmd, char *envp[])
{
	int		p[2];
	pid_t	pid;
	
	if (pipe(p) < 0)
	return (1);
	pid = fork();
	if (pid < 0)
	return (2);
	if (pid == 0)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		ft_execute_cmd(cmd, envp);
	}
	else
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
	}
	return (1);
}

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
	if(!fd)
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
		ft_execute_cmd(cmd->args, envp);
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

void	ft_exec_commands(t_cmd *cmd_lst, char *envp[])
{
	int	i_fd;
	int	o_fd;
	
	if (!cmd_lst->next)
		ft_exec_single_cmd(cmd_lst, envp);
	printf("SALE\n");
	
}
