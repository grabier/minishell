/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:25:56 by gmontoro          #+#    #+#             */
/*   Updated: 2025/03/18 18:22:21 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

char	*ft_expand_exit(t_shell *ms, char *input, int start)
{
	char	*aux;

	(void)start;
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
	if (input[1] == '?')
		return (ft_expand_exit(ms, input, start));
	while (input[i] != 34 && input[i] != ' ' && input[i] && input[i] != '$'
		&& input[i++] != '\'')
		j++;
	name = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(name, &input[start], j + 1);
	aux = ft_getenv(*env, name);
	if (!aux)
		return (free(name), free(aux), NULL);
	res = ft_strinsert(input, aux, start - 1, i - 1);
	free(input);
	free(name);
	free(aux);
	return (res);
}

char	*ft_copy_to_dollar(char *input)
{
	int		i;
	char	*res;

	i = 1;
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

char	*ft_check_expands(t_shell *ms, char *in, int mode, char **env[])
{
	ms->aux = NULL;
	while (in[++ms->i] && in[ms->i + 1] && ms->i >= 0)
	{
		if ((in[ms->i] == 34 && in[ms->i + 1] != '\0') || mode == 0)
		{
			if (mode != 0)
				ms->i++;
			while (!f(in[ms->i], in[ms->i], 0, 0) && ms->i < ft_strlen(in) - 1)
				ms->i++;
			if (!f(in[ms->i], in[ms->i + 1], in[ms->i + 1], 1) && in[ms->i + 1])
			{
				if (ms->aux)
					free(ms->aux);
				ms->aux = ft_expand(ms, in, ms->i + 1, env);
				if (!ms->aux)
					return (ft_copy_to_dollar(in));
				in = ft_strdup(ms->aux);
				if (ft_strchr(in, '$'))
					ms->i = -1;
				else if (!ft_strchr(in, '$') || ms->i < ft_strlen(in) - 1)
					break ;
			}
		}
	}
	return (ft_check_return(in, ms->aux));
}

void	ft_quotes(t_shell *ms, t_tkn **tkn, char **env[])
{
	t_tkn	*first;

	first = *tkn;
	while (*tkn)
	{
		if ((*tkn)->type == QD || (*tkn)->type == QS)
		{
			if ((*tkn)->type == QD)
			{
				ms->i = -1;
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
