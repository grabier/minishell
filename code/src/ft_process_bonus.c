/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:03:30 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/08 19:54:03 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

char	*ft_free(char *buffer)
{
	free(buffer);
	buffer = NULL;
	return (NULL);
}

int	ft_infile_process(char *argv[], char *envp[], int *fds)
{
	int	i_fd;

	close (fds[0]);
	i_fd = open(argv[1], O_RDONLY, 0777);
	if (i_fd == -1)
		return (0);
	if (dup2(i_fd, STDIN_FILENO) < 0)
		return (0);
	close(i_fd);
	if (dup2(fds[1], STDOUT_FILENO) < 0)
		return (0);
	close(fds[1]);
	if (!ft_execute_cmd(argv[2], envp))
		exit(1);
	return (1);
}

int	ft_midle_process(int *fds, int *fds2)
{
	close (fds[1]);
	close(fds2[0]);
	if (dup2(fds[0], STDIN_FILENO) < 0)
		return (3);
	close(fds[0]);
	if (dup2(fds2[1], STDOUT_FILENO) < 0)
		return (4);
	close(fds2[1]);
	return (1);
}

int	ft_outfile_process(char *argv[], char *envp[], int *fds, int argc)
{
	int	o_fd;

	close (fds[1]);
	o_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (o_fd == -1)
		return (1);
	if (dup2(fds[0], STDIN_FILENO) < 0)
		return (2);
	if (dup2(o_fd, STDOUT_FILENO) < 0)
		return (3);
	if (!ft_execute_cmd(argv[argc - 2], envp))
		exit(1);
	return (4);
}
