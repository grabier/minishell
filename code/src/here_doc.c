/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:43:56 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/10 14:38:43 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_here_doc(char *limit)
{
	int		fd;
	int		pid;
	char	*buff;

	fd = open(".tempppp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	//forkear el heredoc para que tire con señales
	if (pid == 0)
	{
		signal_flag = 2;
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			buff = readline("heredoc:");
			if (!ft_strcmp(buff, limit))
				break ;
			write(fd, buff, ft_strlen(buff));
			write(fd, "\n", 1);
			free(buff);
		}
		exit(130);
	}
	else
		signal_flag = 2;
	//signal(SIGQUIT, SIG_IGN);
	//signal(SIGINT, ft_handle_c);
	waitpid(pid, NULL, 0);
	//free(buff);
	close(fd);
	return (open(".tempppp", O_RDONLY));
}
