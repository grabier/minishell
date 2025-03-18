/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:49:35 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:26:41 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_check_redirections(t_tkn *tokens)
{
	t_tkn	*prev;
	char	*error;

	prev = NULL;
	error = "Error: Redirection cannot be followed by another one\n";
	while (tokens)
	{
		if (tokens->type == R1 || tokens->type == R2)
		{
			if (!tokens->next || tokens->next->type != WORD)
				return (printf("Error: Missing file for redirection\n"), 0);
			if (tokens->next && (tokens->next->type == R1
					|| tokens->next->type == R2))
				return (printf("%s", error), 0);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}

int	ft_check_syntax(t_shell *ms, t_tkn *prev, t_tkn *head)
{
	while (ms->tkn_lst)
	{
		if (ms->tkn_lst->type == PI)
		{
			if (!prev || prev->type > 2 || !ms->tkn_lst->next)
				ms->tkn_lst = head;
		}
		if (ms->tkn_lst->type >= 4)
		{
			if (!ms->tkn_lst->next || ms->tkn_lst->next->type > 2)
				return (printf("Error: Missing file for redirection\n"), 2);
		}
		if ((ms->tkn_lst->type < 3) && !ms->tkn_lst->token)
			return (printf("Error: Empty token\n"), 2);
		prev = ms->tkn_lst;
		ms->tkn_lst = ms->tkn_lst->next;
	}
	ms->tkn_lst = head;
	return (0);
}

void	ft_get_tokens(t_shell *ms)
{
	int		i;

	i = 0;
	while (ms->input[i])
	{
		if ((ms->input[i]) == ' ')
			i++;
		else if (ms->input[i] == 34 || ms->input[i] == 39)
		{
			if (!ft_quote_tkn(&ms->tkn_lst, ms, &i))
				break ;
		}
		else if (ms->input[i] == '<' || ms->input[i] == '>')
			ft_redir_tkn(&ms->tkn_lst, ms->input, &i);
		else if (ms->input[i] == '|')
			ft_pipe_tkn(&ms->tkn_lst, ms->input, &i);
		else
		{
			if (!ft_word_tkn(&ms->tkn_lst, ms->input, &i))
				break ;
		}
	}
}

int	ft_check_words(t_tkn *tkn)
{
	int		cont;
	t_tkn	*prev;

	cont = 0;
	if (!tkn)
		return (0);
	if (tkn->type == 0)
		return (1);
	prev = tkn;
	tkn = tkn->next;
	while (tkn)
	{
		if (tkn->type == 0 && prev->type < 4)
			cont++;
		prev = tkn;
		tkn = tkn->next;
	}
	return (cont);
}

t_tkn	*ft_tokenize(t_shell *ms, char ***env)
{
	int		exit;
	t_tkn	*prev;
	t_tkn	*head;

	prev = NULL;
	if (!ms->input || ms->input[0] == 0)
		return (NULL);
	ft_get_tokens(ms);
	if (!ft_check_words(ms->tkn_lst))
		return (ft_free_tkn_lst(&ms->tkn_lst), NULL);
	head = ms->tkn_lst;
	if (!ft_check_redirections(ms->tkn_lst))
		exit = 1;
	else
		exit = ft_check_syntax(ms, prev, head);
	ms->tkn_lst = head;
	if (exit != 0)
	{
		ms->exitstat = exit;
		return (ft_free_tkn_lst(&ms->tkn_lst), NULL);
	}
	ft_quotes(ms, &ms->tkn_lst, env);
	ms->exitstat = exit;
	return (ms->tkn_lst);
}
