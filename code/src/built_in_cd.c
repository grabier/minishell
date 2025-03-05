/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:21:12 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/02 20:14:08 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"
//entra $VAR y sale su contenido
char	*ft_getenv(char **env, char *var)
{
	int		i;
	char	*res;

	i = 0;
	//printf("var: %s\n", var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)) && env[i][ft_strlen(var)] == '=')
			return (ft_strdup(&env[i][ft_strlen(var) + 1]));
		i++;
	}
	return (NULL);
}

int	ft_cd_dot(char ***env, t_cmd *cmd)
{
	int	i;
	char	*aux;
	char	*aux2;

	free(cmd->args[1]);
	cmd->args[1] = getcwd(NULL, 0);
	*env = ft_unset(*env, "OLDPWD");
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("OLDPWD=", aux2);
	if (chdir(cmd->args[1]) == -1)
		return (free(aux), free(aux2), printf("cd: unable to chdir\n"), 0);
	*env = ft_insert_dp(*env, aux);
	(free(aux), free(aux2));
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("PWD=", aux2);
	*env = ft_unset(*env, "PWD");
	*env = ft_insert_dp(*env, aux);
	(free(aux), free(aux2));
	return (1);
}


int	ft_cd_minus(char ***env, t_cmd *cmd)//se va al directorio anterior
{//pero no en la ruta
	int	i;
	char	*aux;
	char	*aux2;

	free(cmd->args[1]);
	aux = ft_getenv(*env, "OLDPWD");
	cmd->args[1] = ft_strdup(aux);
	free(aux);
	*env = ft_unset(*env, "OLDPWD");
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("OLDPWD=", aux2);
	//printf("cmd->args1: %s\n", cmd->args[1]);
	if (chdir(cmd->args[1]) == -1)
		return (free(aux), free(aux2), printf("cd: unable to chdir\n"), 0);
	*env = ft_insert_dp(*env, aux);
	(free(aux), free(aux2));
	aux2 = getcwd(NULL, 0);
	aux = ft_strjoin("PWD=", aux2);
	*env = ft_unset(*env, "PWD");
	*env = ft_insert_dp(*env, aux);
	(free(aux), free(aux2));
	return (1);
}

int	ft_cd_normal(char ***env, char *path)
{
	int	i;
	char	*aux;
	char	*aux2;

	*env = ft_unset(*env, "OLDPWD");//eliminamos OLDPWD del env
	aux2 = getcwd(NULL, 0);//te devuelve el pwd y lo guardamos en aux2
	aux = ft_strjoin("OLDPWD=", aux2);//añdimos oldpwd delante
	if (chdir(path) == -1)//cambiamos de directorio
		return (free(aux), free(aux2), printf("cd: unable to chdir\n"), 0);
	*env = ft_insert_dp(*env, aux);//exportamos el OLDPWD al entorno
	(free(aux), free(aux2));
	aux2 = getcwd(NULL, 0);//recogemos la ruta actual 
	aux = ft_strjoin("PWD=", aux2);//le añadimos PWD delante
	*env = ft_unset(*env, "PWD");//eliminamos PWD del entorno
	*env = ft_insert_dp(*env, aux);//exportamos el nuevo PWD
	(free(aux), free(aux2));
	return (1);
}

int	ft_cd(char ***env, t_cmd *cmd)
{
	int	i;
	char	*aux;
	char	*aux2;

	if (cmd->args[1] == NULL || !ft_strcmp(cmd->args[1], "~"))
	{
		aux = ft_getenv(*env, "HOME");
		if (!ft_cd_normal(env, aux))
			return (free(aux), 0);
		return (free(aux), 1);
	}
	if (cmd->args[2] != NULL)
		return (printf("cd: too many arguments\n"), 0);
	else if (!ft_strcmp(cmd->args[1], "."))
	{
		if (!ft_cd_dot(env, cmd))
			return (0);
	}
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		if (!ft_cd_minus(env, cmd))
			return (0);
	}
	else if (!ft_cd_normal(env, cmd->args[1]))
			return (0);
	return (1);
}
