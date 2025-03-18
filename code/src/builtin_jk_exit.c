/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jk_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:13:40 by jkubecka          #+#    #+#             */
/*   Updated: 2025/03/18 18:28:08 by gmontoro         ###   ########.fr       */
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
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_shell *ms)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (ms->cmd_lst->args[1])
	{
		if (!ft_is_num(ms->cmd_lst->args[1]))
		{
			printf("minishell: exit: numeric argument required\n");
			ft_free_shell(ms);
			free(ms);
			exit(2);
		}
		exit_code = ft_atoi(ms->cmd_lst->args[1]);
		if (exit_code < 0 || exit_code > 255)
			exit_code = exit_code % 256;
		if (ms->cmd_lst->args[2])
		{
			printf("minishell: exit: too many arguments\n");
			ms->exitstat = 1;
			return ;
		}
	}
	(ft_free_shell(ms), free(ms));
	exit((unsigned char)exit_code);
}
