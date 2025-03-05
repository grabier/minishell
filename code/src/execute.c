/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:55:41 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/05 11:08:00 by gmontoro         ###   ########.fr       */
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

void	ft_add_shlvl(char **env[])
{
	int	lv;
	char	*aux;
	char	*aux2;

	printf("entra?\n");
	lv = ft_atoi(ft_getenv(*env, "SHLVL"));
	lv++;
	aux = ft_strjoin("SHLVL", "=");
	aux2 = ft_strjoin(aux, ft_itoa(lv));
	ft_insert_dp(*env, aux2);
	free(aux);
	free(aux2);
}

//hay que ejecutar los built ins por separado
int	ft_execute_cmd(t_shell *ms, char **envp[])
{
	//printf("args[0] : %s\n", ms->cmd_lst->args[0]);
	if (!access(ms->cmd_lst->args[0], X_OK) )//gestionamos si nos entra la ruta del comando
	{//echo ->>>> /usr/bin/echo
		//printf("entra1\n");
		char *aux = ft_strdup(ms->cmd_lst->args[0]);
		ms->cmd_lst->args[0] = ft_trim_path(ms->cmd_lst->args[0]);
		if (!ft_strcmp(ms->cmd_lst->args[0], "minishell"))
			ft_add_shlvl(envp);
		if (execve(aux, ms->cmd_lst->args, *envp) == -1)
		{
			printf("fuck 1\n");
			//ms->exitstat = 1;
			exit(127);
		}
	}
	if (execve(ft_find_path(ms->cmd_lst->args[0], *envp), ms->cmd_lst->args, *envp) == -1)
	{
		printf("fuck 2\n");
		//ms->exitstat = 1;
		exit(127);
	}
	return (0);
}

void	ft_exec_commands(t_shell *ms, char **envp[])
{
	int	i_fd;
	int	o_fd;
	//ft_cmdprint(ms->cmd_lst);
	if (!ms->cmd_lst->next)//las redirecciones son distintas si no hay pipas
	{
		if (ms->cmd_lst->is_bi)//los builtins tienen que ir por separado
			ft_exec_built_in(ms, envp);//ya que no deben ir en un fork
		else
			ft_exec_single_cmd(ms, envp);
	}
	else
	{
		
		printf("entra aki?\n");
		ft_exec_pipeline(ms, envp);
	}
}
