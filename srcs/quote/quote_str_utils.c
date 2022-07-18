/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_str_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:18:15 by soo               #+#    #+#             */
/*   Updated: 2022/07/18 21:28:00 by soo              ###   ########.fr       */
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
	// printf("%c\n", line[0][p[0] - 1])
	if (line[0][p[0] - 1] == '\"' && line[0][p[1] + 1] == '\"' && \
		sep_str[1][0] == '\0')
	{
		split_line[0] = ft_strndup(*line, p[0] - 1);
		split_line[1] = ft_strdup(&line[0][p[1] + 2]);
	}
	else
	{
		split_line[0] = ft_strndup(*line, p[0]);
		split_line[1] = ft_strdup(&line[0][p[1] + 1]);
	}
	split_line[2] = NULL;
	free(*line);
	printf("split_line0 : %s\n", split_line[0]);
		printf("split_line1 : %s\n", split_line[1]);
	printf("1%d\n", ft_strlen(split_line[0]));
	printf("2%d\n",ft_strlen(sep_str[1]));
	printf("3%d\n",ft_strlen(split_line[1]));
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

	printf("find_end_line : %s\n", line);
	dollar = find_first_c(line, '$');
	space =  find_first_c(line, ' ');
	quote =  find_first_c(line, '\"');
	printf("d : %d s : %d q : %d\n", dollar, space, quote);
	if (dollar == -1 && space == -1 && quote == -1)
		return (ft_strlen(line));
	if ((quote != -1) && (space == -1 || (quote < space)) && (dollar == -1 || quote < dollar))
		return (quote);
	else if ((dollar != -1) && (quote == -1 || (dollar < quote)) && (space == -1 || dollar < space))
		return (dollar);
	return (space);
}

char	*substitution_env(t_env *env, char **line, int exit_code, int *idx)
{
	char	**sep_str;
	int		dollar;
	int		end;
	int		p[2];

	printf("while line : %s\n", &line[0][*idx]);
	int i = 0;
	int	cnt = 0;
	while (i != *idx)
	{
		if (line[0][i] == '\'')
			++cnt;
		++i;
	}
	dollar = find_first_c(&line[0][*idx], '$') + *idx;
	end = find_end(&line[0][dollar + 1]) + dollar;
	p[0] = dollar;
	p[1] = end;
	sep_str = (char **)malloc(sizeof(char *) * 3);
	printf("dollar %d, end %d\n", dollar, end);
	sep_str[0] = ft_strndup(&line[0][dollar + 1], end - dollar); // 치환할 키
	sep_str[1] = find_env(env, sep_str[0]); // 치환된 value
	if (sep_str[1][0] == '\0') // "$유효하지 않은 value"일 때 치환하기 전 달러 포함 문자 복사
	{
		if ((find_first_c(sep_str[0], '\'') != -1) && (cnt % 2 == 0))
		{
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			free(sep_str[0]);
			sep_str[0] = ft_strndup(&line[0][dollar + 1], end - dollar - 1);
			printf("1111111%s\n", sep_str[0]);
			free(sep_str[1]);
			sep_str[1] = find_env(env, sep_str[0]);
			if (sep_str[1][0] == '\0')
			{
				printf("---------%s\n", sep_str[1]);
				free(sep_str[0]);
				sep_str[0] = ft_strndup(&line[0][dollar], end - dollar);
				printf("2222222%s\n", sep_str[0]);
				find_exit_code(sep_str, exit_code);
			}
			else
			{
				free(sep_str[1]);
				sep_str[1] = ft_strdup(sep_str[0]);
			}
			arrange_str(sep_str, line, p, idx);
			// str_free(sep_str);
			printf("return line : %s\n", *line);
			return (*line);
		}
		free(sep_str[0]);
		sep_str[0] = ft_strndup(&line[0][dollar], end - dollar + 1);
		printf("!!!!!!!!!%s\n", sep_str[0]);
		if (find_first_c(sep_str[0], '\'') == -1)
			find_exit_code(sep_str, exit_code);
		else
		{
			free(sep_str[1]);
			sep_str[1] = ft_strdup(sep_str[0]);
		}
	}
	sep_str[2] = NULL;
	printf("1%s\n2%s\n3%s\n", sep_str[0], *line, sep_str[1]);
	arrange_str(sep_str, line, p, idx); // 치환 문자 기준 앞 문자열 + 치환문자열 + 뒤 문자열
	str_free(sep_str);
	return (*line);
}

char	*split_dup_quote(char *origin, char **split, char c)
{
	char	*str;
	int		start;
	int		end;

	start = find_first_c(origin, c);
	end = find_last_c(origin, c);
	split[0] = ft_strndup(origin, start);
	split[1] = ft_strdup(&origin[end + 1]);
	str = ft_strndup(&origin[start], end - start + 1);
	return (str);
}

