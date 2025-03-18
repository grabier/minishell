/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:07:37 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:26:33 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

t_tkn	*ft_quote_tkn(t_tkn **tkn_lst, t_shell *ms, int *i)
{
	int		e;

	e = 0;
	if (ms->input[*i] == 34)
	{
		e = ft_find_end_dq(&ms->input[*i]);
		if (!e)
		{
			ms->exitstat = 2;
			return (printf("%s", ms->em), ft_free_tkn_lst(&ms->tkn_lst), NULL);
		}
		ft_tknadd_back(tkn_lst, ft_tknnew(ft_substr(&ms->input[*i], 0, e), 2));
	}
	else if (ms->input[*i] == 39)
	{
		e = ft_find_end_sq(&ms->input[*i]);
		if (!e)
		{
			ms->exitstat = 2;
			return (printf("%s", ms->em), ft_free_tkn_lst(&ms->tkn_lst), NULL);
		}
		ft_tknadd_back(tkn_lst, ft_tknnew(ft_substr(ms->input, *i, e), 1));
	}
	*i += e;
	return (*tkn_lst);
}

t_tkn	*ft_redir_tkn(t_tkn **tkn_lst, char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			ft_tknadd_back(tkn_lst, ft_tknnew(ft_strdup("<<"), 7));
			*i += 2;
		}
		else
		{
			ft_tknadd_back(tkn_lst, ft_tknnew(ft_strdup("<"), 6));
			*i += 1;
		}
	}
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			ft_tknadd_back(tkn_lst, ft_tknnew(ft_strdup(">>"), 5));
			*i += 1;
		}
		else
			ft_tknadd_back(tkn_lst, ft_tknnew(ft_strdup(">"), 4));
		*i += 1;
	}
	return (*tkn_lst);
}

int	ft_find_end_word(char *input)
{
	int	i;

	i = 1;
	while (input[i] != 34 && input[i] != '<'
		&& input[i] != '>' && input[i] != '|' && input[i] != ' '
		&& input[i] != '\0' && input[i] != '\'')
		i++;
	return (i);
}

t_tkn	*ft_word_tkn(t_tkn **tkn_lst, char *input, int *i)
{
	t_tkn	*tkn;
	char	*str;
	int		end;

	end = ft_find_end_word(&input[*i]);
	str = ft_substr(&input[*i], 0, end);
	tkn = ft_tknnew(str, 0);
	ft_tknadd_back(tkn_lst, tkn);
	*i += end;
	if (!(*i))
		return (NULL);
	return (*tkn_lst);
}

t_tkn	*ft_pipe_tkn(t_tkn **tkn_lst, char *input, int *i)
{
	t_tkn	*tkn;

	(void)input;
	tkn = ft_tknnew(ft_strdup("|"), 3);
	ft_tknadd_back(tkn_lst, tkn);
	*i += 1;
	return (*tkn_lst);
}
