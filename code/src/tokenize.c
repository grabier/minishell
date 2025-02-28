/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:49:35 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/27 19:04:19 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int ft_check_redirections(t_tkn *tokens)
{
	t_tkn *prev = NULL;

	 while (tokens)
	 {
		if (tokens->type == R1 || tokens->type == R2)
		{
			if (!tokens->next || tokens->next->type != WORD)
				return (printf("Error: Missing file for redirection\n"), 0);
			/* if (tokens->next->next && (tokens->next->next->type == R1 
					|| tokens->next->next->type == R2))
				return (printf("Error: Redirection after another redirection without a command in between\n"), 0); */
			if (tokens->next && (tokens->next->type == R1 || tokens->next->type == R2))
				return (printf("Error: Redirection cannot be followed by another redirection directly\n"), 0);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}

//checkeamos la sintaxis de los tokens: no puede haber dos pipas ni redirs seguidas, 
int	ft_check_syntax(t_tkn *tokens)
{
	t_tkn *prev = NULL;

	if (!ft_check_redirections(tokens))
		return (1);
	while (tokens)
	{
		if (tokens->type == PI)
		{
			if (!prev || prev->type > 2 || !tokens->next)
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

//transformamos el input en una lista enlazada de tokens
//los tokens seran de los tipo que vienen en el .h
t_tkn	*ft_get_tokens(char *input)
{
	int		i;
	t_tkn	*tkn_lst;

	tkn_lst = NULL;
	i = 0;
	while (input[i])
	{
		if ((input[i]) == ' ')
			i++;
		else if (input[i] == 34 || input[i] == 39)//creamos token de tipo comilla
		{
			if (!ft_quote_tkn(&tkn_lst, input, &i))//ARREGLAR
				return (ft_free_tkn_lst(&tkn_lst), NULL);
		}
		else if (input[i] == '<' || input[i] == '>')//tokens de tipo redireccion
			ft_redir_tkn(&tkn_lst, input, &i);
		else if (input[i] == '|')//tokens de tipo pipa
			ft_pipe_tkn(&tkn_lst, input, &i);
		else
		{
			if (!ft_word_tkn(&tkn_lst, input, &i))//si no es ninguno de los anteriores creamos token de tipo palabra
				break;
		}
	}
	return (tkn_lst);
}

int	ft_check_words(t_tkn *tkn)
{
	int cont;
	t_tkn *prev;

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

t_tkn	*ft_tokenize(char *input, char ***env)
{
	t_tkn	*tkn_lst;

	if (!input || input[0] == 0)
		return (NULL);
	tkn_lst = ft_get_tokens(input);//transformamos el input en lista de tokens
	/* printf("---------before quotes--------\n");
	ft_tknprint(tkn_lst); */
	if (!ft_check_words(tkn_lst))
		return (ft_free_tkn_lst(&tkn_lst), NULL);
	if (ft_check_syntax(tkn_lst) != 0)//checkeamos el orden de los tokens para sintaxis
		return (ft_free_tkn_lst(&tkn_lst), NULL);
	ft_quotes(&tkn_lst, env);//lidiamos con comillas
	
	/* printf("---------after quotes--------\n");
	ft_tknprint(tkn_lst); */
	return (tkn_lst);
}
