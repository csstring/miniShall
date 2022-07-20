/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:07:48 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 21:09:17 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_hyphen(t_env *env, char **before, char **after, int *ret)
{
	*before = find_env(env, "PWD");
	*after = find_env(env, "OLDPWD");
	*ret = chdir(*after);
}

char	*check_home_path(char **home, char *line)
{
	char	*ret;

	if (!line[1])
		return (*home);
	ret = ft_strjoin(*home, &line[1]);
	if (!ret)
		exit (12);
	free(*home);
	*home = ft_strdup(ret);
	free(ret);
	return (*home);
}

char	*no_arg_cd_home(t_env *env, char **home)
{
	*home = find_env(env, "HOME");
	if (home[0][0] == '\0')
	{
		ft_putstr_fd("ss_shell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (*home);
}

char	*check_cd_home(t_env *env, char *line, char **home)
{
	t_env	*now;

	now = env;
	if (line && line[0] == '~')
	{
		while (now)
		{
			if (!ft_strncmp(now->key, "HOME", 5))
			{
				*home = ft_strdup(now->value);
				break ;
			}
			now = now->next;
		}
		check_home_path(home, line);
	}
	return (*home);
}
