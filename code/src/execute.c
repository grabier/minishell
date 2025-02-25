/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:55:41 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/24 16:27:54 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

char	*ft_trim_path(char *s)
{
	int		i;
	int		j;
	char	*res;

	i = ft_strlen(s) - 1;
	j = 0;
	//rintf("i : %d\n", i);
	while (s[i] && s[i] != '/')
		i--;
	i++;
	res = malloc(ft_strlen(s) - i + 1);
	//printf("size : %lu\n", ft_strlen(s) - i);
	//printf("s : %s\n", &s[i]);
	while (s[i])
	{
		res[j] = s[i];
		j++;
		i++;
	}
	res[j] = '\0';
	free(s);
	return (res);
}

//hay que ejecutar los built ins por separado
int	ft_execute_cmd(t_cmd *cmd, char **envp[])
{
	//printf("args[0] : %s\n", cmd->args[0]);
	if (!access(cmd->args[0], X_OK) )//gestionamos si nos entra la ruta del comando
	{//echo ->>>> /usr/bin/echo
		//printf("entra\n");
		char *aux = ft_strdup(cmd->args[0]);
		cmd->args[0] = ft_trim_path(cmd->args[0]);
		if (execve(aux, cmd->args, *envp) == -1)
		{
			printf("fuck\n");
			cmd->exit_status = 1;
			exit(1);
		}
	}
	if (execve(ft_find_path(cmd->args[0], *envp), cmd->args, *envp) == -1)
		exit(1);
	return (0);
}

void	ft_exec_commands(t_cmd *cmd_lst, char **envp[])
{
	int	i_fd;
	int	o_fd;
	//printf("llega\n");
	if (!cmd_lst->next)//las redirecciones son distintas si no hay pipas
	{
		if (cmd_lst->is_bi)//los builtins tienen que ir por separado
			ft_exec_built_in(cmd_lst, envp);//ya que no deben ir en un fork
		else
			ft_exec_single_cmd(cmd_lst, envp);
	}
	else
		ft_exec_pipeline(cmd_lst, envp);
}
