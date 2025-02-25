/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:25:56 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/25 13:18:34 by gmontoro         ###   ########.fr       */
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
	printf("input: %s\n", input);
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

char	*ft_expand(char *input, int start, char **env[])
{
	int		i;
	int		j;
	char	*name;
	char	*res;
	char	*aux;

	j = 0;
	i = start;
	while (input[i] != 34 && input[i] != ' ' && input[i] && input[i] != '$'
		&& input[i] != '\'')
	{
		i++;
		j++; 
	}
	name = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(name, &input[start], j + 1);
	//printf("name %s\n", name);
	//print_env(*env);
	//printf("-------------------\n");
	aux = ft_getenv(*env, name);
	//printf("aux: %s\n", aux);
	if (!aux)
		return (free(name), ft_strdup(""));
	res = ft_strinsert(input, aux, start - 1, i - 1);
	free(input);
	free(name);
	free(aux);
	return (res);
}

char	*ft_check_expands(char *input, int mode, char **env[])//input = "'$HOME'"
{
	int	i;
	char	*res;

	i = 0;
	res = NULL;
	while (input[i] && i >= 0)
	{
		if ((input[i] == 34 && input[i + 1] != '\0') || mode == 0)//34 es doble
		{
			if (mode != 0)
				i++;
			//printf("mode: %i\n",mode);
			while (input[i] != '$' && input[i] != 34 && input[i])
				i++;
			if (input[i] == '$')
			{
				//printf("entra?\n");
				free(res);
				//printf("input: %s\n", input);
				res = ft_expand(input, i + 1, env);
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
	//printf("res: %s\n", res);
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

void	ft_quotes(t_tkn **tkn, char **env[])
{
	t_tkn	*first;

	first = *tkn;
	//print_env(*env);
	while (*tkn)
	{
		if ((*tkn)->type == QD || (*tkn)->type == QS)
		{
			if ((*tkn)->type == QD)
			{
				
				(*tkn)->token = ft_check_expands((*tkn)->token, 1, env);
				(*tkn)->token = ft_delete_dquotes((*tkn)->token);
			}
			else
				(*tkn)->token = ft_delete_squotes((*tkn)->token);
			if ((*tkn)->type == 2)
				(*tkn)->type = 0;
		}
		(*tkn) = (*tkn)->next;
	}
	*tkn = first;
}
