/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:09:59 by soo               #+#    #+#             */
/*   Updated: 2022/07/17 20:46:55 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**line_format(char *line, char *cmd)
{
	char	**str;
	char	**ret;
	int		i;

	i = 1;
	ret = (char **)malloc(sizeof(char *) * 3);
	str = ft_split(line, ' ');
	if (!ft_strncmp(str[0], cmd, ft_strlen(cmd + 1)))
		ret[0] = ft_strdup(str[0]);
	else
		return (NULL); // error command not found
	if (line[ft_strlen(ret[0])] == '\0')
		ret[1] = ft_strdup("");
	else
		ret[1] = ft_strdup(&line[ft_strlen(ret[0]) + 1]);
	ret[2] = NULL;
	str_free(str);
	return (ret);
}

int	format_check(char *line)
{
	int		e_flag;
	
	e_flag = 0;
	if (line[0] >= '0' && line[0] <= '9')
		return (0);
	if (line[0] == '=')
		return (0);
	e_flag = find_equal(line);
	if (e_flag)
	{
		if (find_first_ch(line, ' ') != -1 && (find_first_ch(line, ' ') < find_first_ch(line, '=')))
			return (0);
	}
	else
	{
		if (find_first_ch(line, ' ') != -1)
			return (0);
	}
	return (1);
}

int	find_first_ch(char *line, char c)
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

void str_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}