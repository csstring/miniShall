/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:51:46 by schoe             #+#    #+#             */
/*   Updated: 2022/07/18 19:35:55 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	sig_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
	g_exit = 1;
}

void	dfl_handler(int sigquit)
{
	if (sigquit != SIGQUIT)
		return ;
	write(STDOUT_FILENO, "^\\Quit: 3\n", 10);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ft_tc(int ac, char **av)
{
	struct termios termios;

    tcgetattr(STDIN_FILENO, &termios);
    termios.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	(void)ac;
	(void)av;
}
