/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:49:06 by schoe             #+#    #+#             */
/*   Updated: 2022/07/20 20:59:06 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_echo(t_pipex *val, int i, int k, int check)
{
	while (val->cmd[i][k])
	{
		if (val->cmd[i][k][0] != 0)
			write(1, val->cmd[i][k], ft_strlen(val->cmd[i][k]));
		k++;
		if (val->cmd[i][k] != NULL)
			write(1, " ", 1);
	}
	if (check < 1)
		write(1, "\n", 1);
}

static int	ft_check_n(char *str, char c)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_pipex *val, int i)
{
	int	check;
	int	k;

	k = 1;
	check = 0;
	while (val->cmd[i][k])
	{
		if (!ft_strncmp(val->cmd[i][k], "-n", 2))
		{
			if (ft_check_n(val->cmd[i][k], 'n'))
			{
				k++;
				check++;
				continue ;
			}
		}
		ft_print_echo(val, i, k, check);
		break ;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	buf[1024];

	getcwd(buf, 1024);
	printf("%s\n", buf);
	return (0);
}
