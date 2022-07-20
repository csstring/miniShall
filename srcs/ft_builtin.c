/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:29:34 by schoe             #+#    #+#             */
/*   Updated: 2022/07/20 20:22:47 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_built_check(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strncmp(str, "cd", 3) && \
			ft_strncmp(str, "echo", 5) && \
			ft_strncmp(str, "pwd", 4) && \
			ft_strncmp(str, "export", 7) && \
			ft_strncmp(str, "unset", 6) && \
			ft_strncmp(str, "env", 4) && \
			ft_strncmp(str, "exit", 5))
		return (0);
	return (1);
}

int	ft_in_built(t_pipex *val, int i, t_env *env)
{
	if (val->cmd[i] == NULL)
		return (0);
	if (!ft_strncmp(val->cmd[i][0], "cd", 3))
		return (chdir_main(env, val->cmd[i], val->origin_ev));
	else if (!ft_strncmp(val->cmd[i][0], "echo", 5))
		return (ft_echo(val, i));
	else if (!ft_strncmp(val->cmd[i][0], "pwd", 4))
		return (ft_pwd());
	else if (!ft_strncmp(val->cmd[i][0], "export", 7))
		return (export_env(env, val->cmd[i], val->origin_ev));
	else if (!ft_strncmp(val->cmd[i][0], "unset", 6))
		return (unset_env(&env, val->cmd[i], val->origin_ev));
	else if (!ft_strncmp(val->cmd[i][0], "env", 4))
		return (print_env(env, val->cmd[i]));
	else if (!ft_strncmp(val->cmd[i][0], "exit", 5))
		return (ft_exit(val->cmd[i]));
	return (0);
}
