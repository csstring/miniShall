/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:05:05 by soo               #+#    #+#             */
/*   Updated: 2022/07/19 12:03:14 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	change_path(t_env *env, char ***env_arr, char **path, char *key)
{
	char **c_path;
	
	c_path = (char **)malloc(sizeof(char *) * 3);
	c_path[2] = NULL;
	c_path[0] = ft_strdup("export");
	c_path[1] = ft_strjoin(key, *path);
	free(*path);
	export(env, c_path, env_arr);
	str_free(c_path);
}

static int print_error(char *line)
{
	ft_putstr_fd("ss_shell: cd: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

char	*check_cd_home(t_env *env, char *line, char **home)
{
	if (!line)
	{
		*home = no_arg_cd_home(env);
		if (!*home)
			return (NULL);
	}
	else if (!ft_strncmp(line, "~", 2))
		*home = ft_strdup("/Users/soo"); // /Users/schoe
	return (*home);
}

void	cd_hyphen(t_env *env, char **before, char **after, int *ret)
{
	*before = find_env(env, "PWD");
	*after = find_env(env, "OLDPWD");
	*ret = chdir(*after);
}

//void	cd_hi
int chdir_main(t_env *env, char **line, char ***env_arr)
{
	char	*home;
	char	*before;
	char	*after;
	int		ret;

	home = NULL;
	if (!ft_strncmp(line[1], "-", 2))
		cd_hyphen(env, &before, &after, &ret);
	else
	{
		before = getcwd(NULL, 0);
		home = check_cd_home(env, line[1], &home);
		if (!home)
			ret = chdir(line[1]);
		else
		{
			ret = chdir(home);
			free(home);
		}
		if (ret == -1)
		{
			free(before);
			return (print_error(line[1]));
		}
		after = getcwd(NULL, 0);
	}
	change_path(env, env_arr, &before, "OLDPWD=");
	change_path(env, env_arr, &after, "PWD=");
	return (0);
}
