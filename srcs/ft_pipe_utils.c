/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:53:22 by schoe             #+#    #+#             */
/*   Updated: 2022/07/20 18:42:32 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_make_pipe(t_pipex *val)
{
	int	ac_temp;
	int	i;

	i = 0;
	ac_temp = val->ac;
	val->fd = (int **)malloc(sizeof(int *) * ac_temp);
	if (val->fd == NULL)
		exit(12);
	while (ac_temp - 1 > 0)
	{
		(val->fd)[i] = (int *)malloc(sizeof(int) * 2);
		if (val->fd[i] == NULL)
			exit(12);
		if (pipe(val->fd[i]) == -1)
		{
			perror("pipe error ");
			exit(1);
		}
		i++;
		ac_temp--;
	}
	val->fd[i] = NULL;
	val->end = i;
}

static void	ft_close_fd2(t_pipex *val, int i, int end_temp)
{
	if (i == val->end)
	{
		while (i - 2 >= 0)
		{
			close(val->fd[i - 2][P_W]);
			close(val->fd[i - 2][P_R]);
			i--;
		}
	}
	else
	{
		while (end_temp > 0)
		{
			end_temp--;
			if (end_temp == i || end_temp == i - 1)
				continue ;
			close(val->fd[end_temp][P_W]);
			close(val->fd[end_temp][P_R]);
		}
	}
}

void	ft_close_fd(pid_t pid, t_pipex *val, int i)
{
	int	end_temp;

	end_temp = val->end;
	if (pid > 0)
	{
		while (end_temp > 0)
		{
			end_temp--;
			close(val->fd[end_temp][P_W]);
			close(val->fd[end_temp][P_R]);
		}
	}
	else if (i == 0)
	{
		while (end_temp > 1)
		{
			end_temp--;
			close(val->fd[end_temp][P_W]);
			close(val->fd[end_temp][P_R]);
		}
	}
	else
		ft_close_fd2(val, i, end_temp);
}

int	ft_exit_sig(int st)
{
	if (st >= 256)
		return (st >> 8 & 0x000000ff);
	else if (st == 0)
		return (0);
	else
		return ((st & 0x000000ff) + 128);
}
