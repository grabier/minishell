/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:50:20 by gmontoro          #+#    #+#             */
/*   Updated: 2025/01/29 16:25:49 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

void	ft_tknprint(t_tkn *lst)
{
	while (lst)
	{
		printf("token: [%s]\t", lst->token);
		printf("type: [%i]\n", lst->type);
		lst = lst->next;
	}
}

void	ft_tknadd_back(t_tkn **lst, t_tkn *new)
{
	t_tkn *aux;

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

void	ft_tknadd_front(t_tkn **lst, t_tkn *new)
{
	new->next = *lst;
	*lst = new;
}

t_tkn	*ft_tknnew(char *content, int type)
{
	t_tkn	*new_node;

	new_node = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new_node)
		return (NULL);
	new_node->token = content;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

int	ft_tknsize(t_tkn *lst)
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