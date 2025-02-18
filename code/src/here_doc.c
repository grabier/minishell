/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubecka <jkubecka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:43:56 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/18 19:42:47 by jkubecka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_here_doc(char *limit)
{
	int		fd;
	char	*buff;

	fd = open(".tempppp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		buff = readline("heredoc:");
		if (!ft_strcmp(buff, limit))
			break ;
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
	}
	free(buff);
	close(fd);
	return (open(".tempppp", O_RDONLY));
}