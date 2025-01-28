/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:41:54 by gmontoro          #+#    #+#             */
/*   Updated: 2025/01/28 16:28:22 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEO_H
# define PARSEO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include "../libft/libft.h"

/* typedef struct s_token
{
	char	*token;
	int		type;
	t_token	*next;
}			t_token; */

//parseo.c
int	ft_get_input(char *envp[]);


//quotes.c
int	ft_check_quotes(char *input);
char	*ft_expand(char *input, int start);
char	*ft_check_expands(char *input);
char *ft_quotes(char *input);

//aux
char	*ft_strinsert(char *str, char *word, int start, int end);
#endif