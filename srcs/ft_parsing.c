/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:53:16 by schoe             #+#    #+#             */
/*   Updated: 2022/07/20 18:14:33 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_access_check2(char *cmd, t_pipex *val, int check, int i)
{
	char		*temp;
	char		*str;
	struct stat	buf;

	ft_memset(&buf, 0, sizeof(buf));
	stat(cmd, &buf);
	if (buf.st_mode & S_IXUSR && buf.st_mode & S_IFREG)
	{
		val->exe_path[check] = ft_strdup(cmd);
		return (0);
	}
	else
	{
		temp = ft_strjoin(val ->path[i], "/");
		str = ft_strjoin(temp, cmd);
		free(temp);
		stat(str, &buf);
		if (buf.st_mode & S_IXUSR && buf.st_mode & S_IFREG)
		{
			val -> exe_path[check] = str;
			return (0);
		}
		free(str);
	}
	return (1);
}

int	ft_access_check(char *cmd, t_pipex *val, int check)
{
	int		i;

	i = 0;
	if (cmd == NULL)
	{
		val->exe_path[check] = ft_strdup("");
		return (0);
	}
	while (val->path && val -> path[i])
	{
		if (ft_access_check2(cmd, val, check, i) == 0)
			return (0);
		i++;
	}
	val->exe_path[check] = ft_strdup("");
	return (0);
}

void	ft_av_parsing(t_pipex *val)
{
	int	ac_temp;
	int	i;

	i = 0;
	ac_temp = val->ac;
	while (ac_temp > 0)
	{
		val -> temp[i] = ft_split(val->av[i], ' ');
		ft_sep_temp(val, i, 0, 0);
		i++;
		ac_temp--;
	}
}

char	**ft_ev_parsing(char **enpv)
{
	char	*str;
	char	**line;
	int		i;

	i = 0;
	while (enpv[i] != NULL)
	{
		str = ft_strnstr(enpv[i++], "PATH=", 5);
		if (str != NULL)
		{
			str = ft_strtrim(str, "PATH=");
			line = ft_split(str, ':');
			free(str);
			return (line);
		}
	}
	return (NULL);
}
