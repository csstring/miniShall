/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:11:57 by schoe             #+#    #+#             */
/*   Updated: 2022/07/20 18:44:07 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_find_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			return (str[i + 1]);
		i++;
	}
	return (0);
}

static void	ft_sep_init(t_pipex *val, int i)
{
	int	k;

	k = 0;
	val->indirec[i] = (char **)malloc(sizeof(char *) * \
			(ft_direc_count(val->temp[i], "<") * 2 + 1));
	val->outdirec[i] = (char **)malloc(sizeof(char *) * \
			(ft_direc_count(val->temp[i], ">") * 2 + 1));
	if (val->indirec[i] == NULL || val->outdirec[i] == NULL)
		exit(12);
	while (val->temp[i][k])
		k++;
	val->cmd[i] = (char **)malloc(sizeof(char *) * (k + 1));
	if (val->cmd[i] == NULL)
		exit(12);
	val->indirec[i][ft_direc_count(val->temp[i], "<") * 2] = NULL;
	val->outdirec[i][ft_direc_count(val->temp[i], ">") * 2] = NULL;
}

static void	ft_sep_temp2(char **temp, char **direc, int *k, int *in_out)
{
	if (temp[*k][0] == '<')
	{
		if (temp[(*k)++][1] == '<')
			direc[(*in_out)++] = ft_strdup("<<");
		else
			direc[(*in_out)++] = ft_strdup("<");
		direc[(*in_out)++] = ft_strdup(temp[*k]);
	}
	else if (temp[*k][0] == '>')
	{
		if (temp[(*k)++][1] == '>')
			direc[(*in_out)++] = ft_strdup(">>");
		else
			direc[(*in_out)++] = ft_strdup(">");
		direc[(*in_out)++] = ft_strdup(temp[*k]);
	}
}

void	ft_sep_temp(t_pipex *val, int i, int in, int out)
{
	int	k;
	int	etc;

	k = 0;
	etc = 0;
	ft_sep_init(val, i);
	while (val->temp[i][k])
	{
		if (val->temp[i][k][0] == '<')
			ft_sep_temp2(val->temp[i], val->indirec[i], &k, &in);
		else if (val->temp[i][k][0] == '>')
			ft_sep_temp2(val->temp[i], val->outdirec[i], &k, &out);
		else if (ft_find_symbol(val->temp[i][k]))
		{
			val->cmd[i][etc++] = ft_re_trans_quot(val->line, \
					ft_find_symbol(val->temp[i][k]), 0, 0);
		}
		else
			val->cmd[i][etc++] = ft_strdup(val->temp[i][k]);
		k++;
	}
	val->cmd[i][etc] = NULL;
}
