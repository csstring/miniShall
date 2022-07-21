/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:09:13 by schoe             #+#    #+#             */
/*   Updated: 2022/07/20 17:52:40 by soo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# define P_W	1
# define P_R	0
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <string.h>
# include <fcntl.h>

int	g_exit;

typedef struct s_pipex
{
	char	**path;
	char	***indirec;
	char	***outdirec;
	char	***temp;
	char	***cmd;
	char	**exe_path;
	char	*line;
	int		**fd;
	int		end;
	int		ac;
	char	**av;
	char	**ev;
	char	***origin_ev;
}	t_pipex;

//ft_cmd
void	ft_cmd_end(int i, t_pipex *val, t_env *env);
void	ft_cmd_mid1(int i, t_pipex *val, t_env *env);
void	ft_cmd_start(int i, t_pipex *val, t_env *env);
int		ft_cmd_parent(int i, t_pipex *val, t_env *env);
//ft_error_check
int		ft_error_check(int i, t_pipex *val);
void	ft_error_check_exit(int i, t_pipex *val);
//ft_parsing
int		ft_access_check(char *cmd, t_pipex *val, int check);
void	ft_av_parsing(t_pipex *val);
void	ft_sep_temp(t_pipex *val, int i, int in, int out);
char	**ft_ev_parsing(char **enpv);
//ft_pipex
void	ft_make_pipe(t_pipex *val);
void	ft_close_fd(pid_t pid, t_pipex *val, int i);
int		ft_pipex(int ac, t_pipex *val, t_env *env);
int		ft_exit_sig(int st);
//main
int		ft_pipe(char *line, char ***envp, t_env *env);
void	sig_handler(int signum);
void	ft_tc(void);
//etc
int		ft_dire_in(char **indirec, int index);
int		ft_dire_out(char **outdirec);
void	ft_error_print(char *str, int no);
char	*ft_add_space(char *src, char c, int i, int k);
int		ft_direc_count(char **str, char *c);
void	ft_tolower_str(char *str);
int		ft_built_check(char *str);
int		ft_taptosp(char *line);
int		ft_in_built(t_pipex *val, int i, t_env *env);
//syntax
int		ft_pass_quot(char *line, int i);
int		ft_syntax_check(char **line);
//syntax_utils
int		ft_print_syntax(char *str, int exit_code);
int		ft_pass_quot(char *line, int i);
int		ft_quot_check(char *line, int single_quot, int double_quot);
int		ft_bracket_check(char *line, int check);
int		ft_blank_check(char *line, char *c);
//free
void	ft_free2(void **temp);
void	ft_free3(void ***temp);
void	ft_pipe_clear(t_pipex *val);
//echo,pwd,exit
void	ft_print_echo(t_pipex *val, int i, int k, int check);
int		ft_echo(t_pipex *val, int i);
int		ft_pwd(void);
int		ft_exit(char **str);
//trans_quot
char	*ft_trans_quot(char *line, int i, int k);
char	*ft_re_trans_quot(char *line, int index, int k, int j);
//here_doc
void	ft_make_here_doc(char ***indirec);
#endif
