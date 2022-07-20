/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:45:04 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 18:38:26 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cnt_size(t_env *head)
{
	t_env	*now;
	int		size;

	size = 0;
	now = head;
	while (now)
	{
		if (now->unset_flag == 1)
		{
			if (now->next)
				now = now->next;
			else
				break ;
			continue ;
		}
		now = now->next;
		++size;
	}
	return (size);
}

char	**make_new_arr(char **new, t_env *head)
{
	t_env	*now;
	int		i;
	char	*tmp;

	i = 0;
	now = head;
	while (now)
	{
		if (now->unset_flag == 1)
		{
			if (now->next)
				now = now->next;
			else
				break ;
			continue ;
		}
		tmp = ft_strjoin(now->key, "=");
		new[i++] = ft_strjoin(tmp, now->value);
		free(tmp);
		now = now->next;
	}
	return (new);
}

char	**edit_env_arr(t_env *head, char ***env_arr)
{
	int			size;
	char		**new;
	static int	free_count;

	free_count++;
	size = cnt_size(head);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		exit (12);
	new[size] = NULL;
	make_new_arr(new, head);
	if (free_count != 1)
		str_free(*env_arr);
	*env_arr = new;
	return (*env_arr);
}
