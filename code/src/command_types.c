/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:14:39 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:27:24 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

void	ft_add_cmd(t_shell *ms, t_tkn **t, t_cmd **cmd_lst, char **env[])
{
	int	i;

	i = 0;
	if (!(*cmd_lst)->args)
		(*cmd_lst)->args = ft_calloc(sizeof(char *), (ft_count_args(*t) + 1));
	else
		while ((*cmd_lst)->args[i])
			i++;
	while ((*t) && ((*t)->type == 0 || (*t)->type == QS))
	{
		if (i == 0)
			((*t)->token) = ft_delete_squotes(((*t)->token));
		ms->i = -1;
		if (ft_strchr((*t)->token, '$') && (*t)->type != QS)
			((*t)->token) = ft_check_expands(ms, (*t)->token, 0, env);
		if ((*t)->token)
			(*cmd_lst)->args[i] = ft_strdup((*t)->token);
		i++;
		if ((*t)->next && ((*t)->next->type == 0 || (*t)->next->type == QS))
			(*t) = (*t)->next;
		else
			break ;
	}
	if (ft_isbuiltin((*cmd_lst)->args[0]))
		(*cmd_lst)->is_bi = 1;
}

char	*ft_add_infile(t_tkn **tkn, t_cmd **cmd_lst, t_shell *ms)
{
	(*tkn) = (*tkn)->next;
	if (!(*cmd_lst)->infile)
	{
		if (!access((*tkn)->token, R_OK))
			(*cmd_lst)->infile = ft_strdup((*tkn)->token);
		else
		{
			ms->exitstat = 1;
			return (printf("%s: no file\n", (*tkn)->token), NULL);
		}
	}
	else
	{
		free((*cmd_lst)->infile);
		(*cmd_lst)->infile = ft_strdup((*tkn)->token);
	}
	return (".");
}

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
