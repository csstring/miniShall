/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:08:34 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 18:02:21 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_unset_env(t_env **env, char *del)
{
	t_env	*now;

	now = *env;
	while (now)
	{
		if (!ft_strncmp(now->key, del, ft_strlen(del) + 1) && \
			(ft_strncmp(now->key, "_", 2)))
		{
			now->unset_flag = 1;
			break ;
		}
		now = now->next;
	}
	return (*env);
}

int	split_del_key(t_env **env, char **split_key)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	while (split_key[i])
	{
		if (!format_check(split_key[i]))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(split_key[i], 2);
			ft_putstr_fd("' : not a valid identifier\n", 2);
			++flag;
			++i;
			continue ;
		}
		find_unset_env(env, split_key[i++]);
	}
	return (flag);
}

int	unset_env(t_env **head, char **del, char ***env_arr)
{
	if (!del)
		return (1);
	if (!del[1])
		return (0);
	if (split_del_key(head, del) > 0)
		return (1);
	edit_env_arr(*head, env_arr);
	return (0);
}
