/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:44:41 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/08 21:04:21 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"
//t_cmd	*ft_cmdnew()

int	ft_count_args(t_tkn	*tkn)
{
	int	i;

	i = 0;
	while (tkn && tkn->type == 0)
	{
		i++;
		tkn = tkn->next;
	}
	return (i);
}

int		ft_isbuiltin(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "cd"))
		return (1);
	else if (!ft_strcmp(str, "pwd"))
		return (1);
	else if (!ft_strcmp(str, "export"))
		return (1);
	else if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!ft_strcmp(str, "env"))
		return (1);
	else
		return (0);
} 

void	ft_add_cmd(t_tkn **tkn, t_cmd **cmd_lst)
{
	int	i;

	i = 0;
	
	(*cmd_lst)->args = malloc(sizeof(char *) * (ft_count_args(*tkn) + 1));
	while ((*tkn) && (*tkn)->type == 0)
	{
		(*cmd_lst)->args[i] = ft_strdup((*tkn)->token);
		//printf("args[%i]: %s\n", i, (*cmd_lst)->args[i]);
		i++;
		if ((*tkn)->next &&(*tkn)->next->type == 0)
			(*tkn) = (*tkn)->next;
		else
			break ;
	}
	(*cmd_lst)->args[i] = NULL;
	if (ft_isbuiltin((*cmd_lst)->args[0]))
		(*cmd_lst)->is_bi = 1;
	else
		(*cmd_lst)->is_cmd = 1;
}

void	ft_add_infile(t_tkn **tkn, t_cmd **cmd_lst)
{
	(*tkn) = (*tkn)->next;
	(*cmd_lst)->infile = ft_strdup((*tkn)->token);
}

void	ft_add_outfile(t_tkn **tkn, t_cmd **cmd_lst)
{
	(*tkn) = (*tkn)->next;
	(*cmd_lst)->outfile = ft_strdup((*tkn)->token);
}

void	ft_add_append(t_tkn **tkn, t_cmd **cmd_lst)
{
	(*tkn) = (*tkn)->next;
	(*cmd_lst)->outfile = ft_strdup((*tkn)->token);
	(*cmd_lst)->append = 1;
}

void	ft_add_here_doc(t_tkn **tkn, t_cmd **cmd_lst)
{
	(*tkn) = (*tkn)->next;
	(*cmd_lst)->outfile = ft_strdup((*tkn)->token);
	(*cmd_lst)->hd = 1;
}

t_cmd	*ft_get_commands(t_tkn *tkn)
{
	t_cmd	*new;
	t_cmd	*cmd_lst;
	
	cmd_lst = NULL;
	new = ft_cmdnew();
	while (tkn)
	{
		if (tkn->type == 3)// | pipa
		{
			ft_cmdadd_back(&cmd_lst, new);
			new = ft_cmdnew();
		}
		else if (tkn->type == 0)// word
			ft_add_cmd(&tkn, &new);
		else if (tkn->type == 6)// < infile
			ft_add_infile(&tkn, &new);
		else if (tkn->type == 4)// > outfile
			ft_add_outfile(&tkn, &new);
		else if (tkn->type == 5)// >> append
			ft_add_append(&tkn, &new);
		else if (tkn->type == 7)// << here_doc
			ft_add_here_doc(&tkn, &new);
			tkn = tkn->next;
		}
	return (ft_cmdadd_back(&cmd_lst, new), cmd_lst);
}
