/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:05:12 by schoe             #+#    #+#             */
/*   Updated: 2022/07/17 19:56:12 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#include "libft.h"
#include <stdio.h>

void	ft_init(t_pipex *val)
{
	val->check = 0;
	val->exe_path = (char **)malloc(sizeof(char *) * (val->ac + 1));
	val->cmd = (char ***)malloc(sizeof(char **) * (val->ac + 1));
	val->indirec = (char ***)malloc(sizeof(char **) * (val->ac + 1));
	val->outdirec = (char ***)malloc(sizeof(char **) * (val->ac + 1));
	val->temp = (char ***)malloc(sizeof(char **) * (val->ac + 1));
	if (!val->cmd || !val->exe_path || !val->indirec || !val->outdirec || !val->temp)
		exit(1);
	val->cmd[val->ac] = NULL;
	val->exe_path[val->ac] = NULL;
	val->indirec[val->ac] = NULL;
	val->outdirec[val->ac] = NULL;
	val->temp[val->ac] = NULL;
}

int	ft_pipe(char *line, char ***envp, t_env *env, int *exit_code)
{
	t_pipex	val;
	int		i;

	i = 0;
	ft_memset(&val, 0 , sizeof(t_pipex));
	val.line = ft_strdup(line);
	line = ft_trans_quot(line);
	val.av = ft_split(line, '|');
	while (val.av[i])
		i++;
	val.ac = i;
	val.origin_ev = envp;//fix
	val.ev = *envp;//free 해줘야 할듯
	ft_init(&val);
	val.path = ft_ev_parsing(val.ev);
	ft_av_parsing(&val);
	i = 0;
	while (val.cmd[i])
	{
		ft_tolower_str(val.cmd[i][0]);
		ft_access_check(val.cmd[i][0], &val, i);
		i++;
	}
	if (val.ac != 1)
		ft_make_pipe(&val);
	*exit_code = ft_pipex(val.ac, &val , env);
//	ft_pipe_clear(&val, &input);
	return (*exit_code);
}
