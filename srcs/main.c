#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include "pipex_bonus.h"
#include "libft.h"
#include "cd.h"
#include "env.h"
#include "quote.h"

void	sig_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	dfl_handler(int sigquit)
{
	write(1,"111",3);
	if (sigquit != SIGQUIT)
		return ;
	write(STDOUT_FILENO, "^\\Quit: 3\n", 10);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

char	*ft_prompt(void)
{
	char	*line;

	line = readline("ss_shell$ ");
	if (line == NULL)
	{
		printf("\033[1A");
		printf("\033[10C");
		printf("exit\n");
		exit(-1);
	}
	else
	{
		add_history(line);
		return (line);
	}
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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	int	exit_code;	
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	ft_memset(env, 0, sizeof(t_env));
	init_env(env, envp);
	ft_tc(ac, av);
    exit_code = 0;
	signal(SIGINT, sig_handler);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		line = ft_prompt();
		if (ft_syntax_check(&line, &exit_code) || ft_taptosp(line))
		{
//			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, sig_handler);
			free(line);
			continue ;
		}
		quote_line(&line, exit_code, env);
		ft_pipe(line, &envp, env, &exit_code);
		signal(SIGINT, sig_handler);
		free(line);
//		system("leaks minishell");
	}
}
