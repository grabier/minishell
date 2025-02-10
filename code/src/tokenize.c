/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:49:35 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/10 15:33:24 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

void	ft_free_tkn_lst(t_tkn **tkn)
{
	t_tkn *aux;

	while (*tkn)
	{
		aux = (*tkn)->next;
		free((*tkn)->token);
		free(*tkn);
		*tkn = aux;
	}
}

int ft_check_redirections(t_tkn *tokens)
{
	t_tkn *prev = NULL;

	 while (tokens)
	 {
		if (tokens->type == R1 || tokens->type == R2)
		{
			if (!tokens->next || tokens->next->type != WORD)
			{
				printf("Error: Missing file for redirection\n");
				return 0;
			}	
			if (tokens->next->next && (tokens->next->next->type == R1 
					|| tokens->next->next->type == R2))
			{
				printf("Error: Redirection after another redirection without a command in between\n");
				return 0;
			}
			if (tokens->next && (tokens->next->type == R1 || tokens->next->type == R2))
			{
				printf("Error: Redirection cannot be followed by another redirection directly\n");
				return 0;
			}
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}


int	ft_check_syntax(t_tkn *tokens)
{
	t_tkn *prev = NULL;

	if (!ft_check_redirections(tokens))
		return (1);
	while (tokens) {
		if (tokens->type == PI)
		{
			if (!prev || prev->type > 2 || !tokens->next || tokens->next->type == L1
					|| tokens->next->type == L2)
				return (printf("Error: Syntax near '|'\n"), 1);
		}
		if (tokens->type == R1 || tokens->type == R2 ||
			tokens->type == L1 || tokens->type == L2)
		{
			if (!tokens->next || tokens->next->type != WORD) 
				return (printf("Error: Missing file for redirection\n"), 1);
		}
		if ((tokens->type == WORD || tokens->type == QS || tokens->type == QD) && !tokens->token)
			return (printf("Error: Empty token\n"), 1);
		prev = tokens;
		tokens = tokens->next;
	}
	return 0; // No errores
}

t_tkn	*ft_tokenize(char *input)
{
	int		i;
	t_tkn	*tkn_lst;

	tkn_lst = NULL;
	i = 0;
	while (input[i])
	{
		if ((input[i]) == ' ')
			i++;
		else if (input[i] == 34 || input[i] == 39)
		{
			if (!ft_quote_tkn(&tkn_lst, input, &i))
				return (ft_free_tkn_lst(&tkn_lst), NULL);
		}
		else if (input[i] == '<' || input[i] == '>')
			ft_redir_tkn(&tkn_lst, input, &i);
		else if (input[i] == '|')
			ft_pipe_tkn(&tkn_lst, input, &i);
		else
		{
			if (!ft_word_tkn(&tkn_lst, input, &i))
				break;
		}
	}
	return (tkn_lst);
}
