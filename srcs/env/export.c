/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:26:02 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 19:17:05 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*dup_env(t_env **now, t_env **new)
{
	(*now)->unset_flag = 0;
	(*now)->value_flag = (*new)->value_flag;
	free((*now)->value);
	(*now)->value = ft_strdup((*new)->value);
	free_node(new);
	return (*now);
}

t_env	*split_equal(char *line, t_env *new)
{
	char	**split_equal;

	split_equal = ft_split(line, '=');
	new->key = ft_strdup(split_equal[0]);
	if (find_equal(line) && !split_equal[1])
		new->value = ft_strdup("");
	else if (!split_equal[1])
		new->value_flag = 1;
	else
		new->value = ft_strdup(split_equal[1]);
	str_free(split_equal);
	return (new);
}

t_env	*add_env(t_env *head, t_env *new)
{
	t_env	*now;

	if (!ft_strncmp(new->key, "_", 2))
	{
		free_node(&new);
		return (head);
	}
	now = head;
	while (now->next && ft_strncmp(now->next->key, "_", 2))
	{
		if (!ft_strncmp(now->key, new->key, ft_strlen(new->key) + 1))
		{
			dup_env(&now, &new);
			return (head);
		}
		now = now->next;
	}
	if (!ft_strncmp(now->key, new->key, ft_strlen(new->key) + 1))
	{
		dup_env(&now, &new);
		return (head);
	}
	new->next = now->next;
	now->next = new;
	return (head);
}

int	make_new_env(t_env *head, char **split_blank)
{
	t_env	*new;
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	while (split_blank[i])
	{
		new = (t_env *)malloc(sizeof(t_env));
		if (!new)
			exit (12);
		ft_memset(new, 0, sizeof(t_env));
		if (!format_check(split_blank[i]))
		{
			ft_putstr_fd("ss_shell: export: '", 2);
			ft_putstr_fd(split_blank[i], 2);
			ft_putstr_fd("' : not a valid identifier\n", 2);
			++flag;
			++i;
			free(new);
			continue ;
		}
		add_env(head, split_equal(split_blank[i++], new));
	}
	return (flag);
}

int	export_env(t_env *head, char **line, char ***env_arr)
{
	if (!line)
		return (1);
	if (!line[1])
	{
		print_export(head);
		return (0);
	}
	if (make_new_env(head, line) > 0)
		return (1);
	edit_env_arr(head, env_arr);
	return (0);
}
