/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_str_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:18:15 by soo               #+#    #+#             */
/*   Updated: 2022/07/19 16:24:36 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//!!널가드 추가

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

char	*arrange_str(char **sep_str, char **line, int *p, int *idx)
{
	char	**split_line;
	
	split_line = (char **)malloc(sizeof(char *) * 3);
	if (line[0][p[0] - 1] == '\"' && line[0][p[1] + 1] == '\"' && \
		sep_str[1][0] == '\0')
	{
		printf("??\n");
		split_line[0] = ft_strndup(*line, p[0] - 1);
		split_line[1] = ft_strdup(&line[0][p[1] + 2]);
	}
	else
	{
		split_line[0] = ft_strndup(*line, p[0]);
		if (line[0][p[1]] + 1 == '\0')
			split_line[1] = ft_strdup("");
		else if(line[0][p[1]] == '\'')
			split_line[1] = ft_strdup(&line[0][p[1]]);
		else
			split_line[1] = ft_strdup(&line[0][p[1] + 1]);
	}
	split_line[2] = NULL;
	free(*line);
	*idx = ft_strlen(split_line[0]) + ft_strlen(sep_str[1]);
	*line = (char *)malloc(ft_strlen(split_line[0]) + \
			ft_strlen(split_line[1]) + ft_strlen(sep_str[1]) + 1);
	*line = arrange_str_cpy(*line, split_line[0], sep_str[1], split_line[1]);
	str_free(split_line);
	return (*line);
}

int		find_end(char *line)
{
	int	dollar;
	int	space;
	int	quote;

	dollar = find_first_c(line, '$');
	space =  find_first_c(line, ' ');
	quote =  find_first_c(line, '\"');
	if (dollar == -1 && space == -1 && quote == -1)
		return (ft_strlen(line));
	if ((quote != -1) && (space == -1 || (quote < space)) && (dollar == -1 || quote < dollar))
		return (quote);
	else if ((dollar != -1) && (quote == -1 || (dollar < quote)) && (space == -1 || dollar < space))
		return (dollar);
	return (space);
}

char	*substitution_env(t_env *env, char **line, int exit_code, int *idx, int *dollar_cnt)
{
	char	**sep_str;
	int		dollar;
	int		end;
	int		p[2];

	int i = 0;
	int	cnt = 0;
	if ((int)ft_strlen(*line) < *idx)
	{
		return (NULL);
	}
	dollar = find_first_c(&line[0][*idx], '$') + *idx;
	while (i != dollar - 1)
	{
		if (line[0][i] == '\'')
			++cnt;
		++i;
	}
	if (line[0][dollar - 1] == '\'' && cnt % 2 == 0)
	{
		int	dollar_cnt_tmp = 0;
		*idx = find_first_c(&line[0][dollar], '\'') + dollar;
		while (i < *idx)
		{
			if (line[0][i] == '$' && *dollar_cnt)
				++dollar_cnt_tmp;
			++i;
		}
		if (dollar_cnt_tmp > 1)
			*dollar_cnt -= 1;
		return (*line);
	}
	end = find_end(&line[0][dollar + 1]) + dollar;
	p[0] = dollar;
	p[1] = end;
	sep_str = (char **)malloc(sizeof(char *) * 3);
	sep_str[0] = ft_strndup(&line[0][dollar + 1], end - dollar); // 치환할 키
	sep_str[1] = find_env(env, sep_str[0]); // 치환된 value
	if (sep_str[1][0] == '\0') // "$유효하지 않은 value"일 때 치환하기 전 달러 포함 문자 복사
	{
		if ((find_first_c(sep_str[0], '\'') != -1))
		{
			free(sep_str[0]);
			sep_str[0] = ft_strndup(&line[0][dollar + 1], end - dollar - 1);
			free(sep_str[1]);
			sep_str[1] = find_env(env, sep_str[0]);
			if (sep_str[1][0] == '\0')
			{
				free(sep_str[0]);
				sep_str[0] = ft_strndup(&line[0][dollar], end - dollar);
				find_exit_code(sep_str, exit_code);
			}
			arrange_str(sep_str, line, p, idx);
			str_free(sep_str);
			return (*line);
		}
		free(sep_str[0]);
		sep_str[0] = ft_strndup(&line[0][dollar], end - dollar + 1);
		if (find_first_c(sep_str[0], '\'') == -1)
			find_exit_code(sep_str, exit_code);
		else
		{
			free(sep_str[1]);
			sep_str[1] = ft_strndup(sep_str[0], ft_strlen(sep_str[0]) - 1);
		}
	}
	sep_str[2] = NULL;
	arrange_str(sep_str, line, p, idx); // 치환 문자 기준 앞 문자열 + 치환문자열 + 뒤 문자열
	str_free(sep_str);
	return (*line);
}

// char	*split_dup_quote(char *origin, char **split, char c)
// {
// 	char	*str;
// 	int		start;
// 	int		end;

// 	start = find_first_c(origin, c);
// 	end = find_last_c(origin, c);
// 	split[0] = ft_strndup(origin, start);
// 	split[1] = ft_strdup(&origin[end + 1]);
// 	str = ft_strndup(&origin[start], end - start + 1);
// 	return (str);
// }

