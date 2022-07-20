/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:06:58 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 20:04:25 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	int				value_flag;
	int				unset_flag;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//env
t_env	*init_env(t_env *head, char **envp);
t_env	*head_node_init(t_env **head, t_env **new);

//export
int		export_env(t_env *head, char **line, char ***env_arr);
int		make_new_env(t_env *head, char **split_blank);
t_env	*add_env(t_env *head, t_env *new);
t_env	*split_equal(char *line, t_env *new);
t_env	*dup_env(t_env **now, t_env **new);

//unset
int		unset_env(t_env **head, char **del, char ***env_arr);
int		split_del_key(t_env **env, char **split_key);
int		find_unset_env(t_env **env, char *del);

//utils
void	ft_error_print(char *str, int no);
void	str_free(char **str);

//env_arr
char	**edit_env_arr(t_env *head, char ***env_arr);
char	**make_new_arr(char **new, t_env *head);

//export_utils
int		find_equal(char *line);
void	free_node(t_env **node);
int		format_check(char *line);

//print_env_export
int		print_env(t_env	*head, char **line);
void	print_export(t_env *head);

#endif
