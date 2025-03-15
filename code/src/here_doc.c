/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:43:56 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/14 20:25:29 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"


static void	wait_status(t_shell *msh, pid_t pid)
{
	int exit_status;
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
	int		fd;
	int		pid;
	char	*buff;
	pid_t pids;

	fd = open(".tempppp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	//forkear el heredoc para que tire con señales
	signal_flag = 2;
	if (pid == 0)
	{
		//signal(SIGINT, SIG_DFL);
		while (1)
		{
			buff = readline(">");
			if (!ft_strcmp(buff, limit) || buff == NULL)
			{
				if (buff == NULL)
					printf("warning: EOF found\n");
				break ;
			}
			write(fd, buff, ft_strlen(buff));
			write(fd, "\n", 1);
			free(buff);
		}
		exit(0);
	}
	else
	{
		signal_flag = 3;
		wait_status(ms, pid);
		//waitpid(pid, NULL, 0);
	}
	/* if (WIFEXITED(ms->exitstat))
	{
		ms->exitstat = WEXITSTATUS(ms->exitstat);  // Extraer correctamente el exit status
		printf("wifexited: %i\n", ms->exitstat);
	}
	else if (WIFSIGNALED(ms->exitstat))
	{
		ms->exitstat = 130;
		printf("wifsignaled: %i\n", ms->exitstat);
	} */
	return (close(fd), open(".tempppp", O_RDONLY));
}
