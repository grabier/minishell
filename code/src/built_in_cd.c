/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:21:12 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:29:07 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_cd_dot(char ***env, t_cmd *cmd)
{
	char	*aux;
	char	*aux2;
	char	**insert;

	free(cmd->args[1]);
	cmd->args[1] = getcwd(NULL, 0);
	*env = ft_unset_in_cd(*env, "OLDPWD");
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("OLDPWD=", aux2);
	if (chdir(cmd->args[1]) == -1)
		return (free(aux), free(aux2), printf("cd: unable to chdir\n"), 0);
	insert = ft_get_dp(aux);
	*env = ft_export(*env, insert);
	(free(aux), free(aux2), ft_free_split(insert));
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("PWD=", aux2);
	*env = ft_unset_in_cd(*env, "PWD");
	insert = ft_get_dp(aux);
	*env = ft_export(*env, insert);
	(free(aux), free(aux2), ft_free_split(insert));
	return (1);
}

int	ft_cd_minus(char ***env, t_cmd *cmd)
{
	char	*aux;
	char	*aux2;
	char	**insert;

	free(cmd->args[1]);
	aux = ft_getenv(*env, "OLDPWD");
	cmd->args[1] = ft_strdup(aux);
	free(aux);
	*env = ft_unset_in_cd(*env, "OLDPWD");
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("OLDPWD=", aux2);
	if (chdir(cmd->args[1]) == -1)
		return (free(aux), free(aux2), printf("cd: unable to chdir\n"), 0);
	insert = ft_get_dp(aux);
	*env = ft_export(*env, insert);
	(free(aux), free(aux2), ft_free_split(insert));
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("PWD=", aux2);
	*env = ft_unset_in_cd(*env, "PWD");
	insert = ft_get_dp(aux);
	*env = ft_export(*env, insert);
	(free(aux), free(aux2), ft_free_split(insert));
	return (1);
}

int	ft_cd_normal(char ***env, char *path)
{
	char	*aux;
	char	*aux2;
	char	**insert;

	*env = ft_unset_in_cd(*env, "OLDPWD");
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("OLDPWD=", aux2);
	if (chdir(path) == -1)
		return (free(aux), free(aux2), printf("cd: unable to chdir\n"), 0);
	insert = ft_get_dp(aux);
	*env = ft_export(*env, insert);
	ft_free_split(insert);
	(free(aux), free(aux2));
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("PWD=", aux2);
	*env = ft_unset_in_cd(*env, "PWD");
	insert = ft_get_dp(aux);
	*env = ft_export(*env, insert);
	ft_free_split(insert);
	(free(aux), free(aux2));
	return (1);
}

int	ft_cd(char ***env, t_cmd *cmd)
{
	char	*aux;

	if (cmd->args[1] == NULL || !ft_strcmp(cmd->args[1], "~"))
	{
		aux = ft_getenv(*env, "HOME");
		if (!ft_cd_normal(env, aux))
			return (free(aux), 1);
		return (free(aux), 0);
	}
	if (cmd->args[2] != NULL)
		return (printf("cd: too many arguments\n"), 1);
	else if (!ft_strcmp(cmd->args[1], "."))
	{
		if (!ft_cd_dot(env, cmd))
			return (1);
	}
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		if (!ft_cd_minus(env, cmd))
			return (1);
	}
	else if (!ft_cd_normal(env, cmd->args[1]))
		return (1);
	return (0);
}
