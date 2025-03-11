/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jk_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:02:36 by jkubecka          #+#    #+#             */
/*   Updated: 2025/03/11 13:34:51 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"


int		ft_check_flag(char *s)
{
	int	i;

	if (s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (i);
}

void	ft_do_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->args[i] && ft_check_flag(cmd->args[i]))
	{
		newline = 0;
		i ++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
//modificado el echo para que permita redirecciones
void	ft_echo(t_cmd *cmd)
{
	int		i_fd;
	int		o_fd;
	int		saved_stdin;
	int		saved_stdout;

	saved_stdin = dup(STDIN_FILENO);//las redirecciones in las gestionamos 
	saved_stdout = dup(STDOUT_FILENO);
	i_fd = ft_open_n_redir(cmd, 0, saved_stdin);//en la funcion open_n_redir, asi que hay que
	o_fd = ft_open_n_redir(cmd, 1, 0);
	dup2(o_fd, STDOUT_FILENO);
	ft_do_echo(cmd);
	if (i_fd != 0)
		close(i_fd);
	if (o_fd != 1)
		close(o_fd);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
}
