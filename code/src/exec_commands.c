/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:55:41 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/09 16:57:43 by gmontoro         ###   ########.fr       */
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

void	ft_exec_commands(t_cmd *cmd_lst, char *envp[])
{
	int	i_fd;
	int	o_fd;
	
	while (cmd_lst)
	{
		if (cmd_lst->infile && !cmd_lst->hd)
		{
			i_fd = open(cmd_lst->infile, O_RDONLY, 0777);
			dup2(i_fd, STDIN_FILENO);
		}
		if (cmd_lst->outfile && !cmd_lst->append)
		{
			o_fd = open(cmd_lst->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(o_fd, STDOUT_FILENO);
		}
		else if (cmd_lst->outfile && cmd_lst->append)
		{
			o_fd = open(cmd_lst->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
			dup2(o_fd, STDOUT_FILENO);
		}
		ft_redir_n_exec(cmd_lst->args, envp);
		cmd_lst = cmd_lst->next;
	}
}
