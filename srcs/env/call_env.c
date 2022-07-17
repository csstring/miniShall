/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:59:16 by soo               #+#    #+#             */
/*   Updated: 2022/07/17 20:47:00 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_env	*head, char **line)
{
	t_env	*now;
	
	if (line[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(line[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	now = head;
	while (now)
	{
		if(!now->value_flag && !now->unset_flag)
			ft_printf("%s=%s\n", now->key, now->value);
		now = now->next;
	}
	return (0);
}