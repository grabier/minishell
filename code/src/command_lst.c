/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:44:41 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 16:58:31 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->args = NULL;
	new_node->exit_status = 0;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->append = 0;
	new_node->hd = 0;
	new_node->is_cmd = 0;
	new_node->is_bi = 0;
	new_node->next = NULL;
	return (new_node);
}

int	ft_count_args(t_tkn	*tkn)
{
	int	i;

	i = 0;
	while (tkn && (tkn->type == 0 || (tkn)->type == QS || (tkn)->type == L1
			|| (tkn)->type == R1 || (tkn)->type == R2))
	{
		if ((tkn)->type == L1 || (tkn)->type == R1 || (tkn)->type == R2)
			tkn = tkn->next->next;
		else
		{
			i++;
			tkn = tkn->next;
		}
	}
	return (i);
}

int	ft_isbuiltin(char *str)
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
	else if (!ft_strcmp(str, "exit"))
		return (1);
	else
		return (0);
}

static void	ft_free_in_cmd(t_cmd *new, char **s, t_cmd **lst)
{
	ft_free_split(s);
	free(new);
	ft_free_cmd_lst(lst);
}

t_cmd	*ft_get_commands(t_shell *ms, t_tkn *tkn, char **env[])
{
	t_cmd	*new;
	t_cmd	*cmd_lst;

	cmd_lst = NULL;
	new = ft_cmdnew();
	while (tkn)
	{
		if (tkn->type == PI)
		{
			ft_cmdadd_back(&cmd_lst, new);
			new = ft_cmdnew();
		}
		else if (tkn->type == WORD || tkn->type == QS)
			ft_add_cmd(ms, &tkn, &new, env);
		else if (tkn->type == L1 && !ft_add_infile(&tkn, &new, ms))
			return (ft_free_in_cmd(new, new->args, &cmd_lst), NULL);
		else if (tkn->type == R1)
			ft_add_outfile(&tkn, &new);
		else if (tkn->type == R2)
			ft_add_append(&tkn, &new);
		else if (tkn->type == L2)
			ft_add_here_doc(&tkn, &new);
		tkn = tkn->next;
	}
	return (ft_cmdadd_back(&cmd_lst, new), cmd_lst);
}
