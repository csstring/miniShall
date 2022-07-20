/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_str_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:18:15 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 18:52:17 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*arrange_str_cpy(char *ret, char *s1, char *s2, char *s3)
{
	int	i;

	i = 0;
	while (*s1)
		ret[i++] = *s1++;
	while (*s2)
		ret[i++] = *s2++;
	while (*s3)
		ret[i++] = *s3++;
	ret[i] = '\0';
	return (ret);
}

char	**arrange_split(char **split_line, char **sep_str, char **line, int *p)
{
	if (p[0] && p[1] + 1 && line[0][p[0] - 1] == '\"' && \
	line[0][p[1] + 1] == '\"' && sep_str[1][0] == '\0')
	{
		split_line[0] = ft_strndup(*line, p[0]);
		split_line[1] = ft_strdup(&line[0][p[1] + 1]);
	}
	else if (p[1] + 1)
	{
		split_line[0] = ft_strndup(*line, p[0]);
		if (line[0][p[1]] + 1 == '\0')
			split_line[1] = ft_strdup("");
		else if (line[0][p[1]] == '\'')
			split_line[1] = ft_strdup(&line[0][p[1]]);
		else
			split_line[1] = ft_strdup(&line[0][p[1] + 1]);
	}
	split_line[2] = NULL;
	return (split_line);
}

char	*arrange_str(char **sep_str, char **line, int *p, int *idx)
{
	char	**split_line;

	split_line = (char **)malloc(sizeof(char *) * 3);
	split_line = arrange_split(split_line, sep_str, line, p);
	free(*line);
	*idx = ft_strlen(split_line[0]) + ft_strlen(sep_str[1]);
	*line = (char *)malloc(ft_strlen(split_line[0]) + \
			ft_strlen(split_line[1]) + ft_strlen(sep_str[1]) + 1);
	*line = arrange_str_cpy(*line, split_line[0], sep_str[1], split_line[1]);
	str_free(split_line);
	return (*line);
}

void	substitution_env2(char **sep_str, char **line, int *p, int exit_code)
{
	free(sep_str[0]);
	sep_str[0] = ft_strndup(&line[0][p[0]], p[1] - p[0] + 1);
	if (find_first_c(sep_str[0], '\'') == -1)
		find_exit_code(sep_str, exit_code);
	else
	{
		free(sep_str[1]);
		sep_str[1] = ft_strndup(sep_str[0], ft_strlen(sep_str[0]) - 1);
	}
}

char	*substitution_env(t_env *env, char **line, int exit_code, int *idx)
{
	char	**sep_str;
	int		p[2];

	p[0] = find_first_c(&line[0][*idx], '$') + *idx;
	p[1] = find_end(&line[0][p[0] + 1]) + p[0];
	sep_str = sep_str_init(env, line, p);
	if (sep_str[1][0] == '\0')
	{
		if ((find_first_c(sep_str[0], '\'') != -1))
		{
			undefine_key(env, sep_str, line, p);
			refind_exit_code(sep_str, line, p, exit_code);
			arrange_str(sep_str, line, p, idx);
			str_free(sep_str);
			return (*line);
		}
		substitution_env2(sep_str, line, p, exit_code);
	}
	arrange_str(sep_str, line, p, idx);
	str_free(sep_str);
	return (*line);
}
