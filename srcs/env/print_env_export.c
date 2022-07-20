/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:59:16 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 18:00:58 by soo              ###   ########.fr       */
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
		if (!now->value_flag && !now->unset_flag)
			ft_printf("%s=%s\n", now->key, now->value);
		now = now->next;
	}
	return (0);
}

void	print_export(t_env *head)
{
	t_env	*now;

	now = head;
	while (now->next)
	{
		if (!now->unset_flag)
		{
			if (now->value_flag == 1)
				ft_printf("declare -x %s\n", now->key);
			else if (!ft_strncmp(now->value, "", 1))
				ft_printf("declare -x %s=\"\"\n", now->key);
			else
				ft_printf("declare -x %s=\"%s\"\n", now->key, now->value);
		}
		now = now->next;
	}
}
