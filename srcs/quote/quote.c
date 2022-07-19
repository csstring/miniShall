/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:13:38 by soo               #+#    #+#             */
/*   Updated: 2022/07/19 20:58:39 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//!!널가드 추가

char	*no_quote_line(char **origin)
{
	char	*cmd_tmp;
	char	*newline;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (origin[0][i] && origin[0][i] != ' ')
		++i;
	if (origin[0][i] == '\0')
		return (NULL);
	++i;
	cmd_tmp = ft_strndup(*origin, i);
	newline = (char *)malloc(ft_strlen(&origin[0][i]) + 3);
	newline[0] = '\"';
	while (origin[0][i])
		newline[++j] = origin[0][i++];
	newline[++j] = '\"';
	newline[++j] = '\0';
	free(*origin);
	*origin = ft_strjoin(cmd_tmp, newline);
	free(cmd_tmp);
	free(newline);
	return (*origin);
}

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
	while (i != dollar - 1)
		if (line[i++] == '\'')
			++cnt;
	if (line[dollar - 1] == '\'' && cnt % 2 == 0)
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

char	*no_quote_line_handler(char **origin, int exit_code, t_env *env)
{
	int	dollar;
	int	idx;

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
	if ((find_first_c(*origin, '\"') == -1) && \
		(find_first_c(*origin, '\'') == -1))
		no_quote_line(origin);
	d_line_handler(env, origin, exit_code);
	return (*origin);
}
