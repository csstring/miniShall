/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trans_quot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:15:39 by schoe             #+#    #+#             */
/*   Updated: 2022/07/20 18:42:02 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_re_trans_quot2_1(char *line, char *temp, int *i, int *k)
{
	while (line[*i] != '\'' && line[*i] != '\"' && line[*i] != '\0' \
			&& line[*i] != ' ')
		temp[(*k)++] = line[(*i)++];
}

static char	*ft_re_trans_quot2(char *line, int k, int i)
{
	char	*temp;
	char	c;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!temp)
		exit(12);
	ft_re_trans_quot2_1(line, temp, &i, &k);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			c = line[i++];
			while (line[i] != c)
				temp[k++] = line[i++];
			i++;
			ft_re_trans_quot2_1(line, temp, &i, &k);
			if (line[i] == '\'' || line [i] == '\"')
				continue ;
			else if (line[i] == ' ' || line[i] == '\0')
				break ;
		}
		i++;
	}
	temp[k] = '\0';
	return (temp);
}

char	*ft_re_trans_quot(char *line, int index, int k, int j)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == 32)
			j = i + 1;
		if (line[i] == '\'' || line[i] == '\"')
		{
			k = i + 1;
			while (line[k] != line[i])
				k++;
			count--;
			if (index == count)
				return (ft_re_trans_quot2(&line[j], 0, 0));
			i = k;
		}
		i++;
	}
	return (0);
}

char	*ft_trans_quot(char *line, int i, int k)
{
	int		count;
	char	*temp;
	char	c;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!temp)
		exit(12);
	count = -1;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			temp[k] = '(';
			c = line[i++];
			while (line[i] != c)
				i++;
			temp[++k] = count--;
		}
		else
			temp[k] = line[i];
		k++;
		i++;
	}
	temp[k] = line[i];
	return (temp);
}
