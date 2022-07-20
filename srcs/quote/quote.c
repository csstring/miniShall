/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:13:38 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 17:37:58 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	s_line_handler(char *line, int *idx, int *dollar_cnt)
{
	int	i;
	int	cnt;
	int	dollar;
	int	dollar_cnt_tmp;

	i = 0;
	cnt = 0;
	dollar = find_first_c(&line[*idx], '$') + *idx;
	dollar_cnt_tmp = 0;
	while (line[i] && i != dollar - 1)
		if (line[i++] == '\'')
			++cnt;
	if (dollar && line[dollar - 1] == '\'' && cnt % 2 == 0)
	{
		*idx = find_first_c(&line[dollar], '\'') + dollar;
		while (i < *idx)
			if (line[i++] == '$' && *dollar_cnt)
				++dollar_cnt_tmp;
		if (dollar_cnt_tmp > 1)
			*dollar_cnt -= (dollar_cnt_tmp - 1);
		return (0);
	}
	return (1);
}

char	*d_line_handler(t_env *env, char **origin, int exit_code)
{
	int		dollar;
	int		idx;

	dollar = cnt_c(*origin, '$');
	if (!dollar)
		return (NULL);
	idx = 0;
	while (dollar--)
	{
		if (!s_line_handler(*origin, &idx, &dollar))
			continue ;
		substitution_env(env, origin, exit_code, &idx);
	}
	return (*origin);
}

char	*quote_line(char **origin, int exit_code, t_env *env)
{
	d_line_handler(env, origin, exit_code);
	return (*origin);
}
