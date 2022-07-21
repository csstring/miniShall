/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_check_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:53:08 by schoe             #+#    #+#             */
/*   Updated: 2022/07/21 15:56:41 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_file(int i, t_pipex *val)
{
	int	j;

	j = 0;
	while (val->cmd[i][0][j] != 0)
	{
		if (val->cmd[i][0][j] == '/')
		{
			ft_eprintf("ss_shell: %s: %s\n", val->cmd[i][0], \
					strerror(2));
			exit(127);
		}
		j++;
	}
}

static int	ft_check_dir(int i, t_pipex *val)
{
	int	j;
	int	dot_count;

	j = 0;
	dot_count = 0;
	while (val->cmd[i][0][j] != 0)
	{
		if (val->cmd[i][0][j] != '/' && val->cmd[i][0][j] != '.')
			return (0);
		if (val->cmd[i][0][j] == '.')
			dot_count++;
		else if (val->cmd[i][0][j] == '/')
			dot_count = 0;
		if (dot_count > 2)
			return (0);
		j++;
	}
	ft_eprintf("ss_shell: %s: %s\n", val->cmd[i][0], \
			strerror(21));
	exit(21);
}

void	ft_error_check_exit(int i, t_pipex *val)
{
	if (val->cmd[i][0][0] == 0)
	{
		ft_eprintf("ss_shell: : command not found\n");
		exit(127);
	}
	ft_check_dir(i, val);
	if (val->exe_path[i][0] == 0)
	{
		ft_check_file(i, val);
		ft_eprintf("ss_shell: %s: command not found\n", \
				val->cmd[i][0]);
		exit(127);
	}
}
