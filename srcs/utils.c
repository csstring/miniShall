/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:09:59 by soo               #+#    #+#             */
/*   Updated: 2022/07/19 21:03:41 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_print(char *str, int no)
{
	ft_eprintf("ss_shell: %s: %s\n", str, strerror(no));
	exit(no);
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
		if (find_first_ch(line, ' ') != -1 && \
			(find_first_ch(line, ' ') < find_first_ch(line, '=')))
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

void	str_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
