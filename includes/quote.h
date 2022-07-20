/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:14:19 by soo               #+#    #+#             */
/*   Updated: 2022/07/20 18:52:17 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_H
# define QUOTE_H

//quote
int		s_line_handler(char *line, int *idx, int *dollar_cnt);
char	*d_line_handler(t_env *env, char **origin, int exit_code);
char	*quote_line(char **origin, int exit_code, t_env *env);

//quote_utils
int		cnt_c(char *line, char c);
int		find_end(char *line);
char	**undefine_key(t_env *env, char **sep_str, char **line, int *p);
char	**sep_str_init(t_env *env, char **line, int *p);

//quote_find_utils
char	*find_exit_code(char **sep_str, int exit_code);
char	*find_env(t_env *env, char *str);
char	**refind_exit_code(char **sep_str, char **line, int *p, int exit_code);
int		find_first_c(char *line, char c);
int		find_last_c(char *line, char c);

//quote_str_utill
char	*arrange_str_cpy(char *ret, char *s1, char *s2, char *s3);
char	**arrange_split(char **split_line, char **sep_str, char **line, int *p);
char	*arrange_str(char **sep_str, char **line, int *p, int *idx);
char	*substitution_env(t_env *env, char **line, int exit_code, int *idx);
void	substitution_env2(char **sep_str, char **line, int *p, int exit_code);

#endif