/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:08:34 by soo               #+#    #+#             */
/*   Updated: 2022/07/21 14:15:44 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_unset_env(t_env **env, char *del)
{
	t_env	*now;

	now = *env;
	while (now)
	{
		if (!ft_strncmp(now->key, del, ft_strlen(del) + 1) && \
			(ft_strncmp(now->key, "_", 2)))
		{
			now->unset_flag = 1;
			return (1);
		}
		now = now->next;
	}
	return (0);
}

static int	unset_key_check(t_env **env, char *del)
{
	t_env	*now;
	int		i;

	i = 0;
	now = *env;
	if (del[0] >= '0' && del[0] <= '9')
		return (0);
	while (del[i])
		if (del[i++] == '=')
			return (0);
	while (now->next)
	{
		if (now->value && !ft_strncmp(now->value, del, ft_strlen(del) + 1))
		{
			if (find_unset_env(env, del))
				return (1);
			return (0);
		}
		now = now->next;
	}
	return (1);
}

int	split_del_key(t_env **env, char **split_key)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	while (split_key[i])
	{
		if (!unset_key_check(env, split_key[i]))
		{
			ft_putstr_fd("ss_shell: unset: '", 2);
			ft_putstr_fd(split_key[i], 2);
			ft_putstr_fd("' : not a valid identifier\n", 2);
			++flag;
			++i;
			continue ;
		}
		find_unset_env(env, split_key[i++]);
	}
	if (flag > 0)
		return (1);
	return (0);
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
