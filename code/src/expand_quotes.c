/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:25:56 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/18 16:55:50 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_check_quotes(char *input)
{
	int	i;
	int	cont1;
	int	cont2;

	cont1 = 0;
	cont2 = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == 39)
			cont1++;
		if (input[i] == 34)
			cont2++;
		i++;
	}
	if (cont1 % 2 != 0 || cont2 % 2 != 0)
		return (0);
	return (1);
}

char	*ft_expand(char *input, int start)
{
	int		i;
	int		j;
	char	*name;
	char	*res;

	j = 0;
	i = start;
	while (input[i] != 34 && input[i] != ' ' && input[i] && input[i] != '$')
	{
		i++;
		j++; 
	}
	name = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(name, &input[start], j + 1);
	//printf("name %s\n", name);
	//printf("name: %s\n", name);
	if (!getenv(name))
		return (ft_strdup(""));
	res = ft_strinsert(input, getenv(name), start - 1, i - 1);
	free(input);
	free(name);
	return (res);
}

char	*ft_check_expands(char *input, int mode)
{
	int	i;
	char	*res;

	i = 0;
	res = NULL;
	while (input[i] && i >= 0)
	{
		if ((input[i] == 34 && input[i++ + 1] != '\0') || mode == 0)
		{
			while (input[i] != '$' && input[i] != 34 && input[i])
				i++;
			if (input[i] == '$')
			{
				free(res);
				res = ft_expand(input, i + 1);
				if (!res)
					return (NULL);
				input = ft_strdup(res);
				if (ft_strchr(input, '$'))
					i = -1;
				else
					break ;
			}
		}
		i++;
	}
	if (res)
		return (free(input), res);
	else
		return (free(res), input);
}

/* char *ft_do_quotes(char *input)
{
	char	*res;

	if (!ft_check_quotes(input))
		return (NULL);
	res = ft_check_expands(input, 1);
	if (!res)
		return (input);
	//printf("res: %s\n", res);
	return (res);
} */

void	ft_quotes(t_tkn **tkn)
{
	t_tkn	*first;

	first = *tkn;
	while (*tkn)
	{
		if ((*tkn)->type == 2 || (*tkn)->type == 1)
		{
			if ((*tkn)->type == 2)
			{
				(*tkn)->token = ft_check_expands((*tkn)->token, 1);
				(*tkn)->token = ft_delete_dquotes((*tkn)->token);
			}
			else
				(*tkn)->token = ft_delete_squotes((*tkn)->token);
			(*tkn)->type = 0;
		}
		(*tkn) = (*tkn)->next;
	}
	*tkn = first;
}
