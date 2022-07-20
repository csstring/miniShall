/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 18:06:21 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 16:15:53 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "env.h"

//cd_main
int	chdir_main(t_env *env, char **line, char ***env_arr);
void	change_path(t_env *env, char ***env_arr, char **path, char *key);

//cd_utils
void	cd_hyphen(t_env *env, char **before, char **after, int *ret);
char	*check_cd_home(t_env *env, char *line, char **home);
char	*no_arg_cd_home(t_env *env);


#endif
