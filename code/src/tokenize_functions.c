/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:07:37 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/10 11:56:50 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"
//funciones para crear tokens de distintos tipos
t_tkn	*ft_quote_tkn(t_tkn **tkn_lst, t_shell *ms, int *i)
{
	int		end;

	if (ms->input[*i] == 34)
	{
		end = ft_find_end_dq(&ms->input[*i]);
		if (!end)
		{
			ms->exitstat = 2;
			return (printf("End quote not found\n"), NULL);
		}
		ft_tknadd_back(tkn_lst, ft_tknnew(ft_substr(&ms->input[*i], 0, end), 2));
	}
	else if (ms->input[*i] == 39)
	{
		end = ft_find_end_sq(&ms->input[*i]);
		if (!end)
		{
			ms->exitstat = 2;
			return (printf("End quote not found\n"), NULL);//cambion end por *i+end
		}
		ft_tknadd_back(tkn_lst, ft_tknnew(ft_substr(ms->input, *i, end), 1));
	}
	*i += end;
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
			*i += 2;
		}
		else
		{
			ft_tknadd_back(tkn_lst, ft_tknnew(ft_strdup(">"), 4));
			*i += 1;
		}
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
	//printf("input: %s\n", &input[*i]);
	str = ft_substr(&input[*i], 0, end);
	tkn = ft_tknnew(str, 0);
	//free(str);
	//printf("str: %s\n", str);
	ft_tknadd_back(tkn_lst, tkn);
	*i += end;
	//printf("i: %i\n", *i);
	if (!(*i))
		return (NULL);
	//printf("que conio sale?: %s\n", (*tkn_lst)->token);
	return (*tkn_lst);
}

t_tkn	*ft_pipe_tkn(t_tkn **tkn_lst, char *input, int *i)
{
	t_tkn	*tkn;

	tkn = ft_tknnew(ft_strdup("|"), 3);
	ft_tknadd_back(tkn_lst, tkn);
	*i += 1;
	return (*tkn_lst);
}
