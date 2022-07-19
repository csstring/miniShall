/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_find_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:20:10 by soo               #+#    #+#             */
/*   Updated: 2022/07/19 21:00:22 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_exit_code(char **sep_str, int exit_code)
{
	int		i;
	char	*str_exit_code;

	i = 0;
	while (sep_str[0][i + 1])
	{
		if (sep_str[0][i] == '$' && sep_str[0][i + 1] == '?')
		{
			str_exit_code = ft_itoa(exit_code);
			free(sep_str[1]);
			sep_str[1] = ft_strdup(str_exit_code);
			free(str_exit_code);
			break ;
		}
		++i;
	}
	return (sep_str[1]);
}

char	*find_env(t_env *env, char *str)
{
	t_env	*now;
	char	*sub_str;

	now = env;
	while (now->next)
	{
		if (!ft_strncmp(now->key, str, ft_strlen(str) + 1))
		{
			if (now->unset_flag)
				break ;
			sub_str = ft_strdup(now->value);
			return (sub_str);
		}
		now = now->next;
	}
	return (ft_strdup(""));
}

char	**refind_exit_code(char **sep_str, char **line, int *p, int exit_code)
{
	if (sep_str[1][0] == '\0')
	{
		free(sep_str[0]);
		sep_str[0] = ft_strndup(&line[0][p[0]], p[1] - p[0]);
		find_exit_code(sep_str, exit_code);
	}
	return (sep_str);
}

int	find_first_c(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

int	find_last_c(char *line, char c)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		--i;
	}
	return (0);
}
