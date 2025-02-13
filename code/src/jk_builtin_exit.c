/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jk_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubecka <jkubecka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:13:40 by jkubecka          #+#    #+#             */
/*   Updated: 2025/02/13 14:39:16 by jkubecka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parseo.h"

int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < 0 && str[i] > 9)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (args[1])
	{
		if (!ft_is_num(args[1]))
		{
			printf("minishell: exit: numeric argument required\n");
			exit(255);
		}
		exit_code = ft_atoi(args[1]);
		if (exit_code < 0 || exit_code > 255)
			exit_code = exit_code % 256;
		if (args[2])
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
	}
	exit((unsigned char)exit_code);
}
