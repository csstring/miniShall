#include "minishell.h"

char	*ft_prompt(void)
{
	char	*line;

	line = readline("ss_shell$ ");
	if (line == NULL)
	{
		printf("\033[1A");
		printf("\033[10C");
		printf("exit\n");
		exit(g_exit);
	}
	else
	{
		add_history(line);
		return (line);
	}
}

static void	ft_module(int exit_code, char *line)
{
	g_exit = exit_code;
	signal(SIGINT, sig_handler);
	free(line);
}

void	main_loop(t_env *env, char **envp, int exit_code)
{
	char	*line;

	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		line = ft_prompt();
		exit_code = ft_syntax_check(&line);
		if (exit_code || ft_taptosp(line))
		{
			ft_module(exit_code, line);
			continue ;
		}
		exit_code = g_exit;
		quote_line(&line, exit_code, env);
		if (line[0] == 0)
		{	
			ft_module(exit_code, line);
			continue ;
		}
		ft_pipe(line, &envp, env);
		signal(SIGINT, sig_handler);
		free(line);
		// system("leaks minishell | grep 'leaks'");
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	g_exit = 0;
	env = (t_env *)malloc(sizeof(t_env));
	ft_memset(env, 0, sizeof(t_env));
	init_env(env, envp);
	ft_tc(ac, av);
	signal(SIGINT, sig_handler);
	main_loop(env, envp, 0);
	return (g_exit);
}
