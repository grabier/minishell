/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:08:48 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/08 21:01:51 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_here_doc(char *limit)
{
	int		fd;
	char	*buff;

	fd = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		buff = get_next_line(0);
		if (!ft_strncmp(buff, limit, ft_strlen(limit)))
			break ;
		write(fd, buff, ft_strlen(buff));
		free(buff);
	}
	free(buff);
	close(fd);
	return (open(".temp", O_RDONLY));
}

static int	ft_redir_n_exec(char *cmd, char *envp[])
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

static int	ft_redir_last(char *cmd, char *envp[], int o_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		dup2(o_fd, STDOUT_FILENO);
		ft_execute_cmd(cmd, envp);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

int	pipex_bonus(int argc, char *argv[], char *envp[])
{
	int	i_fd;
	int	o_fd;
	int	i;

	if (!ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])))
	{
		i_fd = ft_here_doc(argv[2]);
		i = 3;
		o_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	else
	{
		i_fd = open(argv[1], O_RDONLY, 0777);
		i = 2;
		o_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	(dup2(i_fd, STDIN_FILENO), ft_redir_n_exec(argv[i], envp));
	i++;
	while (i < argc - 2)
		ft_redir_n_exec(argv[i++], envp);
	(ft_redir_last(argv[argc - 2], envp, o_fd), close(o_fd), close(i_fd));
	if (!ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])))
		unlink(".temp");
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	j;

	if (argc < 1)
		return (printf("argc not valid\n"), 0);
	j = ft_check_args_bonus(argv, envp, argc);
	if (j != 0)
		return (0);
	pipex_bonus(argc, argv, envp);
	return (0);
}
