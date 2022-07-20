/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:07:48 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 16:25:57 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_hyphen(t_env *env, char **before, char **after, int *ret)
{
	*before = find_env(env, "PWD");
	*after = find_env(env, "OLDPWD");
	*ret = chdir(*after);
}

char	*check_cd_home(t_env *env, char *line, char **home)
{
	t_env	*now;

	now = env;
	if (!line)
	{
		*home = no_arg_cd_home(env);
		if (!*home)
			return (NULL);
	}
	else if (!ft_strncmp(line, "~", 2))
	{
		while(now)
		{
			if (!ft_strncmp(now->key, "HOME", 5))
			{
				*home = ft_strdup(now->value);
				return (*home);
			}
			now = now->next;
		}
	}
	return (*home);
}

char	*no_arg_cd_home(t_env *env)
{
	char	*home_path;

	home_path = find_env(env, "HOME");
	if (home_path[0] == '\0')
	{
		ft_putstr_fd("ss_shell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (home_path);
}

