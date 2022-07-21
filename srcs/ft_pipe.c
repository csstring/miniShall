/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soo <soo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:05:12 by schoe             #+#    #+#             */
/*   Updated: 2022/07/20 21:36:24 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init(t_pipex *val, char **line, char ***envp, int i)
{
	val->line = ft_strdup(*line);
	*line = ft_trans_quot(*line, 0, 0);
	val->av = ft_split(*line, '|');
	while (val->av[i])
		i++;
	val->ac = i;
	val->origin_ev = envp;
	val->ev = *envp;
	val->exe_path = (char **)malloc(sizeof(char *) * (val->ac + 1));
	val->cmd = (char ***)malloc(sizeof(char **) * (val->ac + 1));
	val->indirec = (char ***)malloc(sizeof(char **) * (val->ac + 1));
	val->outdirec = (char ***)malloc(sizeof(char **) * (val->ac + 1));
	val->temp = (char ***)malloc(sizeof(char **) * (val->ac + 1));
	if (!val->cmd || !val->exe_path || !val->indirec || \
			!val->outdirec || !val->temp)
		exit(12);
	val->cmd[val->ac] = NULL;
	val->exe_path[val->ac] = NULL;
	val->indirec[val->ac] = NULL;
	val->outdirec[val->ac] = NULL;
	val->temp[val->ac] = NULL;
}

static void	ft_tc_re(void)
{	
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	signal(SIGQUIT, SIG_DFL);
}

static int	ft_pipex2(pid_t pid, t_pipex *val, int i, t_env *env)
{
	int	st;
	int	k;

	if (pid == 0)
		ft_tc_re();
	if (val->ac != 1)
		ft_close_fd(pid, val, i);
	if (pid == 0 && i == 0)
		ft_cmd_start(i, val, env);
	else if (pid == 0 && i == val->end)
		ft_cmd_end(i, val, env);
	else if (pid == 0)
		ft_cmd_mid1(i, val, env);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &st, 0);
	k = 0;
	while (k < val->end)
	{
		waitpid(0, NULL, 0);
		k++;
	}
	ft_tc();
	return (ft_exit_sig(st));
}

int	ft_pipex(int ac, t_pipex *val, t_env *env)
{
	pid_t	pid;
	int		i;

	i = 0;
	ft_make_here_doc(val->indirec);
	if (ac == 1 && ft_built_check(val->cmd[0][0]))
		return (ft_cmd_parent(i, val, env));
	else
	{
		while (ac > 0)
		{
			ac--;
			pid = fork();
			if (pid == -1)
			{
				perror("fork error ");
				exit(1);
			}
			if (pid == 0)
				break ;
			i++;
		}
	}
	return (ft_pipex2(pid, val, i, env));
}

int	ft_pipe(char *line, char ***envp, t_env *env)
{
	t_pipex	val;
	int		i;

	i = 0;
	ft_memset(&val, 0, sizeof(t_pipex));
	ft_init(&val, &line, envp, i);
	val.path = ft_ev_parsing(val.ev);
	ft_av_parsing(&val);
	while (val.cmd[i])
	{
		ft_tolower_str(val.cmd[i][0]);
		ft_access_check(val.cmd[i][0], &val, i);
		i++;
	}
	if (val.ac != 1)
		ft_make_pipe(&val);
	g_exit = ft_pipex(val.ac, &val, env);
	ft_pipe_clear(&val);
	free(line);
	return (0);
}
