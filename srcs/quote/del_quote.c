/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:21:47 by soo               #+#    #+#             */
/*   Updated: 2022/07/19 16:22:02 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	del_quote_cnt(char *origin, char c)
{
	int		o_idx;
	int		cnt;
	
	o_idx = 1;
	cnt = 0;
	
	if (origin[0] == '\0')
		return (0);
	while (origin[o_idx + 2])
	{
		if (origin[o_idx] == c && origin[o_idx + 1] == c)
		{
			o_idx += 2;
			cnt += 2;
		}
		else
			++o_idx;
	}
	return (cnt);
}

char	*del_quote(char *origin, char c)
{
	int		i;
	int		o_idx;
	int		cnt;
	char	*ret;

	i = 0;
	cnt = del_quote_cnt(origin, c);
	if (!cnt)
		return (NULL);
	ret = (char *)malloc(ft_strlen(origin) - cnt + 2);
	o_idx = 0;
	while (origin[o_idx + 2])
	{
		if (origin[o_idx] == c && origin[o_idx + 1] == c)
			o_idx += 2;
		else
			ret[i++] = origin[o_idx++];
	}
	if (origin[o_idx] != '\0')
		ret[i++] = origin[o_idx]; 
	ret[i++] = origin[ft_strlen(origin) - 1];
	ret[i] = '\0';
	return (ret);
}
