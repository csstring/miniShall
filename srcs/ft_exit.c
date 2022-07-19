/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:12:50 by schoe             #+#    #+#             */
/*   Updated: 2022/07/19 16:32:36 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
static void	ft_print_exit(char *cmd, char *str, int exit_code)
{
	ft_eprintf("ss_shell: exit: %s: %s\n", cmd, str);
	exit(exit_code);
}

static void	ft_check_numeric(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == 0)
		ft_print_exit(cmd, "numeric argument required", 255);
	while (cmd[i])
	{
		if ((cmd[i] >= 48 && cmd[i] <= 57) || cmd[i] == 32 || (cmd[i] >= 8 && cmd[i] <=12))
		{
			i++;
			continue ;
		}
		ft_print_exit(cmd, "numeric argument required", 255);
	}
}

int	ft_exit(char **cmd)
{
	unsigned char	exit_code;
	int				i;

	i = 0;
	exit_code = 0;
	ft_eprintf("exit\n");
	if (cmd[1] == NULL)
		exit(0);
	ft_check_numeric(cmd[1]);
	while (cmd[i])
		i++;
	if (i > 1)
	{
		ft_eprintf("ss_shell: exit: too many arguments");
		return (1);
	}
}
