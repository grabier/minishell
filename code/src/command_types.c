/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:14:39 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/17 15:02:24 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"
//agrega un nuevo argumento al comand o redireccion
void	ft_add_cmd(t_tkn **tkn, t_cmd **cmd_lst)
{
	int	i;

	i = 0;
	
	(*cmd_lst)->args = malloc(sizeof(char *) * (ft_count_args(*tkn) + 1));
	while ((*tkn) && (*tkn)->type == 0)//mientras que nos encontremos palabras, las vamos añadiendo a args[]
	{
		if (i == 0)
			((*tkn)->token) = ft_delete_squotes(((*tkn)->token));
		if ((*tkn)->token[0] == '$')
			((*tkn)->token) = ft_expand((*tkn)->token, 1);
		(*cmd_lst)->args[i] = ft_strdup((*tkn)->token);
		//printf("args[%i]: %s\n", i, (*cmd_lst)->args[i]);
		i++;
		if ((*tkn)->next  && (*tkn)->next->type == 0)
			(*tkn) = (*tkn)->next;
		else
			break ;
	}
	(*cmd_lst)->args[i] = NULL;
	if (ft_isbuiltin((*cmd_lst)->args[0]))//decidimos si es builtin o cmd
		(*cmd_lst)->is_bi = 1;
	else
		(*cmd_lst)->is_cmd = 1;
}

void	ft_add_infile(t_tkn **tkn, t_cmd **cmd_lst)
{
	int	fd;

	(*tkn) = (*tkn)->next;
	if (!(*cmd_lst)->infile)
		(*cmd_lst)->infile = ft_strdup((*tkn)->token);
	else
	{
		fd = open((*cmd_lst)->infile, O_RDONLY | O_CREAT, 0777);
		close(fd);
		(*cmd_lst)->infile = ft_strdup((*tkn)->token);
	}
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
	(*cmd_lst)->outfile = ft_strdup((*tkn)->token);
	(*cmd_lst)->append = 1;
}

void	ft_add_here_doc(t_tkn **tkn, t_cmd **cmd_lst)
{
	(*tkn) = (*tkn)->next;
	(*cmd_lst)->infile = ft_strdup((*tkn)->token);
	(*cmd_lst)->hd = 1;
}
