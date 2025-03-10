/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:14:39 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/10 14:05:58 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"
//agrega un nuevo argumento al comand o redireccion
void	ft_add_cmd(t_shell *ms, t_tkn **tkn, t_cmd **cmd_lst, char **env[])
{
	int	i;

	i = 0;
	if (!(*cmd_lst)->args)
		(*cmd_lst)->args = (char **)ft_calloc(sizeof(char *) , (ft_count_args(*tkn) + 1));
	else
	{
		while ((*cmd_lst)->args[i])
			i++;
	}
	while ((*tkn) && ((*tkn)->type == 0 || (*tkn)->type == QS))//mientras que nos encontremos palabras, las vamos añadiendo a args[]
	{
		if (i == 0)
			((*tkn)->token) = ft_delete_squotes(((*tkn)->token));
		if (ft_strchr((*tkn)->token, '$') && (*tkn)->type != QS)
			((*tkn)->token) = ft_check_expands(ms, (*tkn)->token,  0, env);
		//ft_putendl_fd(ft_itoa(i), 2);
		//printf("token: %s\n", (*tkn)->token);
		(*cmd_lst)->args[i] = ft_strdup((*tkn)->token);
		i++;
		if ((*tkn)->next  && ((*tkn)->next->type == 0 || (*tkn)->next->type == QS))
			(*tkn) = (*tkn)->next;
		else
			break ;
	}
	(*cmd_lst)->args[i] = NULL;
	if (ft_isbuiltin((*cmd_lst)->args[0]))//decidimos si es builtin o cmd
		(*cmd_lst)->is_bi = 1;
}

char	*ft_add_infile(t_tkn **tkn, t_cmd **cmd_lst)
{
	int	fd;

	(*tkn) = (*tkn)->next;
	if (!(*cmd_lst)->infile)
	{
		if (!access((*tkn)->token, R_OK))
			(*cmd_lst)->infile = ft_strdup((*tkn)->token);
		else
			return (printf("%s: no file\n",(*tkn)->token), NULL);
	}
	else
	{
		free((*cmd_lst)->infile);
		(*cmd_lst)->infile = ft_strdup((*tkn)->token);
	}
	return (".");
}
//comprobamos si hay un outfile existente. si lo hay creamos el archivo 
//y nos olvidamos de el
void	ft_add_outfile(t_tkn **tkn, t_cmd **cmd_lst)
{
	int	fd;

	(*tkn) = (*tkn)->next;
	if (!(*cmd_lst)->outfile)
		(*cmd_lst)->outfile = ft_strdup((*tkn)->token);
	else
	{
		fd = open((*cmd_lst)->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		close(fd);
		free((*cmd_lst)->outfile);
		(*cmd_lst)->outfile = ft_strdup((*tkn)->token);
	}
	(*cmd_lst)->append = 0;
}

void	ft_add_append(t_tkn **tkn, t_cmd **cmd_lst)
{
	int	fd;
	
	(*tkn) = (*tkn)->next;
	if (!(*cmd_lst)->outfile)
		(*cmd_lst)->outfile = ft_strdup((*tkn)->token);
	else
	{
		fd = open((*cmd_lst)->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		close(fd);
		(*cmd_lst)->outfile = ft_strdup((*tkn)->token);
	}
	free((*cmd_lst)->outfile);
	(*cmd_lst)->outfile = ft_strdup((*tkn)->token);
	(*cmd_lst)->append = 1;
}

void	ft_add_here_doc(t_tkn **tkn, t_cmd **cmd_lst)
{
	(*tkn) = (*tkn)->next;
	if (!(*cmd_lst)->infile)
		(*cmd_lst)->infile = ft_strdup((*tkn)->token);
	else
	{
		free((*cmd_lst)->infile);
		(*cmd_lst)->infile = ft_strdup((*tkn)->token);
	}
	(*cmd_lst)->hd = 1;
}
