/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:06:21 by soo               #+#    #+#             */
/*   Updated: 2022/07/17 21:42:02 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "env.h"

char	*no_arg_cd_home(t_env *env);
void	change_path(t_env *env, char ***env_arr, char **path, char *key);
int chdir_main(t_env *env, char **line, char ***env_arr);

#endif
