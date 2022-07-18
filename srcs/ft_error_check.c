/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:53:08 by schoe             #+#    #+#             */
/*   Updated: 2022/07/18 12:06:25 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"

static int	ft_check_file(int i, t_pipex *val)
{
	int	j;

	j = 0;
	while (val->cmd[i][0][j] != 0)
	{
		if (val->cmd[i][0][j] == '/')
		{
			ft_eprintf("ss_shell: %s: %s\n", val->av[i + val->check], \
					strerror(2));
			return (2);
		}
		j++;
	}
	return (0);
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
	ft_eprintf("ss_shell: %s: %s\n", val->av[i + val->check], \
			strerror(21));
	return (21);
}

int	ft_error_check(int i, t_pipex *val)
{
	if (val->cmd[i][0][0] == 0)
	{
		ft_eprintf("ss_shell: : command not found\n");
		return (127);
	}
	ft_check_dir(i, val);
	if (val->exe_path[i] == NULL)
	{
		if (ft_check_file(i, val))
			return (2);
		ft_eprintf("ss_shell: %s: command not found\n", \
				val->av[i + val->check]);
		return (127);
	}
	return (0);
}
