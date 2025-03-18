/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:55:41 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 17:06:57 by gmontoro         ###   ########.fr       */
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
	while (i > 0 && s[i] != '/')
		i--;
	i++;
	res = malloc(ft_strlen(s) - i + 1);
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
	int		lv;
	char	*aux;
	char	*aux2;
	char	**insert;

	aux = ft_getenv(*env, "SHLVL");
	insert = malloc(3 * sizeof(char *));
	if (!aux)
	{
		free(aux);
		return ;
	}
	insert[0] = ft_strdup("export ");
	lv = ft_atoi(aux);
	free(aux);
	lv++;
	aux = ft_strjoin("SHLVL", "=");
	aux2 = ft_strjoin(aux, ft_itoa(lv));
	insert[1] = ft_strdup(aux2);
	insert[2] = NULL;
	ft_export(*env, insert);
	free(aux);
	free(aux2);
}

int	ft_execute_cmd(t_shell *ms, char **envp[])
{
	char	*aux;
	char	*aux2;

	if (!ms->cmd_lst->args)
		exit(2);
	if (!access(ms->cmd_lst->args[0], X_OK))
	{
		aux = ft_strdup(ms->cmd_lst->args[0]);
		ms->cmd_lst->args[0] = ft_trim_path(ms->cmd_lst->args[0]);
		if (!ft_strcmp(ms->cmd_lst->args[0], "minishell"))
			ft_add_shlvl(envp);
		if (execve(aux, ms->cmd_lst->args, *envp) == -1)
			exit(127);
	}
	aux2 = ft_find_path(ms->cmd_lst->args[0], *envp);
	if (execve(aux2, ms->cmd_lst->args, *envp) == -1)
		exit(127);
	return (0);
}

void	ft_exec_commands(t_shell *ms, char **envp[])
{
	int	i;

	i = 0;
	if (!ms->cmd_lst->next)
	{
		if (ms->cmd_lst->is_bi)
			ft_exec_built_in(ms, envp);
		else
			ft_exec_single_cmd(ms, envp);
	}
	else
		ft_exec_pipeline(ms, envp, i);
}
