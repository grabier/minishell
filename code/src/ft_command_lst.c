/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:19:10 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/07 16:41:16 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

void	ft_cmdprint(t_cmd *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->args[i])
		{
			printf("args[%i]: [%s]\t", i, lst->args[i]);
			i++;
		}
		printf("infile: [%s]\t", lst->infile);
		printf("outfile: [%s]\t", lst->outfile);
		printf("append: [%i]\t", lst->append);
		printf("here_doc: [%i]\n", lst->hd);
		lst = lst->next;
	}
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd *aux;

	aux = *lst;
	if (!new)
		return ;
	if (!aux)
	{
		*lst = new;
		return ;
	}
	while (aux->next)
		aux = aux->next;
	aux->next = new;
}

void	ft_cmdadd_front(t_cmd **lst, t_cmd *new)
{
	new->next = *lst;
	*lst = new;
}

t_cmd	*ft_cmdnew()
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->args = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->append = 0;
	new_node->hd = 0;
	new_node->next = NULL;
	return (new_node);
}

int	ft_cmdsize(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}