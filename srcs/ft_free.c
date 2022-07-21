/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:06:38 by schoe             #+#    #+#             */
/*   Updated: 2022/07/19 18:27:53 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free3(void ***temp)
{
	int	i;

	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			ft_free2(temp[i]);
			i++;
		}
		free(temp);
	}
}

void	ft_free2(void **temp)
{
	int	i;

	i = 0;
	if (temp)
	{
		while (temp[i])
		{
			free(temp[i]);
			i++;
		}
		free(temp);
	}
}

void	ft_pipe_clear(t_pipex *val)
{
	ft_free2((void **)val->path);
	ft_free3((void ***)val->cmd);
	ft_free3((void ***)val->indirec);
	ft_free3((void ***)val->outdirec);
	ft_free2((void **)val->exe_path);
	ft_free2((void **)val->fd);
	ft_free2((void **)val->av);
	free(val->line);
	ft_free3((void ***)val->temp);
}
