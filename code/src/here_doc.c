/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:43:56 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:13:18 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

static void	wait_status(t_shell *msh, pid_t pid)
{
	int	exit_status;

	waitpid(pid, &exit_status, 0);
	if (WIFSIGNALED(exit_status))
		msh->prevexitstat = 128 + WTERMSIG(exit_status);
	else if (WIFEXITED(exit_status))
		msh->prevexitstat = WEXITSTATUS(exit_status);
	else
		msh->prevexitstat = 1;
}

int	ft_here_doc(char *limit, t_shell *ms)
{
	int		pid;
	char	*buff;

	ms->fd = open(".tempppp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	g_signal_flag = 2;
	if (pid == 0)
	{
		while (1)
		{
			buff = readline(">");
			if (!ft_strcmp(buff, limit) || buff == NULL)
			{
				if (buff == NULL)
					printf("warning: EOF found\n");
				break ;
			}
			write(ms->fd, buff, ft_strlen(buff));
			write(ms->fd, "\n", 1);
			free(buff);
		}
		exit(0);
	}
	g_signal_flag = 3;
	return (wait_status(ms, pid), close(ms->fd), open(".tempppp", O_RDONLY));
}
