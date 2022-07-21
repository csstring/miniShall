/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:05:05 by soo               #+#    #+#             */
/*   Updated: 2022/07/21 15:55:11 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(char *line)
{
	ft_putstr_fd("ss_shell: cd: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

void	change_path(t_env *env, char ***env_arr, char **path, char *key)
{
	char	**c_path;

	c_path = (char **)malloc(sizeof(char *) * 3);
	if (!c_path)
		exit (12);
	c_path[2] = NULL;
	c_path[0] = ft_strdup("export");
	c_path[1] = ft_strjoin(key, *path);
	free(*path);
	export_env(env, c_path, env_arr);
	str_free(c_path);
}

int	chdir_execve(t_env *env, char **line, char **before, char **home)
{
	int	ret;

	*before = getcwd(NULL, 0);
	if (!line[1])
	{
		no_arg_cd_home(env, home);
		if (!*home || home[0][0] == '\0')
		{
			if (home[0][0] == '\0')
				free(*home);
			free(*before);
			return (1);
		}
	}
	else
		*home = check_cd_home(env, line[1], home);
	if (!*home)
		ret = chdir(line[1]);
	else
	{
		ret = chdir(*home);
		free(*home);
	}
	return (ret);
}

int	chdir_main(t_env *env, char **line, char ***env_arr)
{
	char	*home;
	char	*before;
	char	*after;
	int		ret;

	home = NULL;
	if (line[1] && !ft_strncmp(line[1], "-", 2))
		cd_hyphen(env, &before, &after, &ret);
	else
	{
		ret = chdir_execve(env, line, &before, &home);
		if (ret == -1)
		{
			free(before);
			return (print_error(line[1]));
		}
		if (ret == 1)
			return (1);
		after = getcwd(NULL, 0);
	}
	change_path(env, env_arr, &before, "OLDPWD=");
	change_path(env, env_arr, &after, "PWD=");
	return (0);
}
