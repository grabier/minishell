/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:19:10 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/14 20:25:54 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

void	ft_free_cmd_lst(t_cmd **cmd)
{
	t_cmd *aux;

	//printf("entra a free_cmd_lst\n");
	//ft_cmdprint(*cmd);
	if (!*cmd)
		return ;
	while (*cmd)
	{
		//printf("freed cmd\n");
		aux = (*cmd)->next;
		if ((*cmd)->args)
			ft_free_split((*cmd)->args);
		else
			free((*cmd)->args);
		if ((*cmd)->infile)
			free((*cmd)->infile);
		if ((*cmd)->outfile)
			free((*cmd)->outfile);
		free(*cmd);
		*cmd = aux;
	}
}

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
