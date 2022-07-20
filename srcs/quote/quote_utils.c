/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:07:16 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 18:52:03 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_c(char *line, char c)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			++cnt;
		++i;
	}
	return (cnt);
}

int	find_end(char *line)
{
	int	dollar;
	int	space;
	int	quote;

	dollar = find_first_c(line, '$');
	space = find_first_c(line, ' ');
	quote = find_first_c(line, '\"');
	if (dollar == -1 && space == -1 && quote == -1)
		return (ft_strlen(line));
	if ((quote != -1) && (space == -1 || (quote < space)) && \
		(dollar == -1 || quote < dollar))
		return (quote);
	else if ((dollar != -1) && (quote == -1 || (dollar < quote)) && \
		(space == -1 || dollar < space))
		return (dollar);
	return (space);
}

char	**undefine_key(t_env *env, char **sep_str, char **line, int *p)
{
	free(sep_str[0]);
	sep_str[0] = ft_strndup(&line[0][p[0] + 1], p[1] - p[0] - 1);
	free(sep_str[1]);
	sep_str[1] = find_env(env, sep_str[0]);
	return (sep_str);
}

char	**sep_str_init(t_env *env, char **line, int *p)
{
	char	**sep_str;

	sep_str = (char **)malloc(sizeof(char *) * 3);
	if (!sep_str)
		exit (12);
	sep_str[0] = ft_strndup(&line[0][p[0] + 1], p[1] - p[0]);
	sep_str[1] = find_env(env, sep_str[0]);
	sep_str[2] = NULL;
	return (sep_str);
}
