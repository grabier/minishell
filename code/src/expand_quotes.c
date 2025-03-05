/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:25:56 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/05 19:36:54 by gmontoro         ###   ########.fr       */
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

char	*ft_expand_exit(t_shell *ms, char *input, int start)
{
	char	*aux;
	int		i;

	//printf("itoa: %i\n", ms->exitstat);
	aux = ft_itoa(ms->prevexitstat);
	free(input);
	return (aux);
}

char	*ft_expand(t_shell *ms, char *input, int start, char **env[])
{
	int		i;
	int		j;
	char	*name;
	char	*res;
	char	*aux;

	j = 0;
	i = start;
	//printf("input: %s\n", input);
	if (input[1] == '?')
		return (ft_expand_exit(ms, input, start));
	while (input[i] != 34 && input[i] != ' ' && input[i] && input[i] != '$'
		&& input[i++] != '\'')
		j++; 
	name = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(name, &input[start], j + 1);
	aux = ft_getenv(*env, name);
	if (!aux)
		return (free(name),free(aux), NULL);
	res = ft_strinsert(input, aux, start - 1, i - 1);
	free(input);
	free(name);
	free(aux);
	return (res);
}

static char	*ft_copy_to_dollar(char *input)
{
	int		i;
	char	*res;

	i = 0;
	while (input[i] && input[i] != '$')
		i++;
	if (i == 0)
		return (free(input), NULL);
	res = malloc(i + 1);
	i = 0;
	while (input[i] && input[i] != '$')
	{
		res[i] = input[i];
		i++;
	}
	res[i] = '\0';
	free(input);
	return (res);
}

char	*ft_check_expands(t_shell *ms,char *input, int mode, char **env[])//input = "'$HOME'"
{
	int	i;
	char	*res;

	i = 0;
	res = NULL;
	//printf("entra?\n");
	while (input[i] && i >= 0)
	{
		if ((input[i] == 34 && input[i + 1] != '\0') || mode == 0)//34 es doble
		{
			if (mode != 0)
				i++;
			//printf("mode: %i\n",mode);
			while (input[i] != '$' && input[i] != 34 && input[i])
				i++;
			if (input[i] == '$' && input[i + 1] != ' ' && input[i + 1] != '\"' && input[i + 1])
			{
				//printf("entra?\n");
				free(res);
				//printf("input: %s\n", input);
				res = ft_expand(ms, input, i + 1, env);
				//printf("res: %s\n", res);
				if (!res)
					return (ft_copy_to_dollar(input));
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

void	ft_quotes(t_shell *ms, t_tkn **tkn, char **env[])
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
				
				(*tkn)->token = ft_check_expands(ms, (*tkn)->token, 1, env);
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
