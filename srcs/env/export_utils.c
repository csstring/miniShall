/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:25:57 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 18:00:12 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_equal(char *line)
{
	while (*line)
	{
		if (*line == '=')
			return (1);
		++line;
	}
	return (0);
}

void	free_node(t_env **node)
{
	free((*node)->key);
	free((*node)->value);
	free(*node);
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
		if (find_first_c(line, ' ') != -1 && \
			(find_first_c(line, ' ') < find_first_c(line, '=')))
			return (0);
	}
	else
	{
		if (find_first_c(line, ' ') != -1)
			return (0);
	}
	return (1);
}
