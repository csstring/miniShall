#include "pipex_bonus.h"

int	ft_indirec_syntax_check(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = ft_pass_quot(line, i);
		if (line[i] == '<')
		{
			count++;
			if (line[i + 1] == '>')
				return (ft_print_syntax(">", 258));
		}
		else
			count = 0;
		if (count == 3)
			return (ft_print_syntax("<", 258));
		if (line[i] != '<' && line[i] != ' ' && line[i + 1] == '<')
			return (ft_print_syntax("<", 258));
		i++;
	}
	return (ft_blank_check(line, "<"));
}

int	ft_outdirec_syntax_check(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i = ft_pass_quot(line, i);
		if (line[i] == '>')
		{
			count++;
			if (line[i + 1] == '<')
				return (ft_print_syntax("<", 258));
		}
		else
			count = 0;
		if (count == 3)
			return (ft_print_syntax(">", 258));
		if (line[i] != '>' && line[i] != ' ' && line[i + 1] == '>')
			return (ft_print_syntax(">", 258));
		i++;
	}
	return (ft_blank_check(line, ">"));
}

int	ft_syntax_check(char **line)
{
	int temp;

	temp = ft_quot_check(*line, 0, 0);
	if (temp)
		return (temp);
	*line = ft_add_space(*line, '>', 0, 0);
	*line = ft_add_space(*line, '<', 0, 0);
	temp = ft_bracket_check(*line, 0);
	if (temp)
		return (temp);
	temp = ft_indirec_syntax_check(*line);
	if (temp)
		return (temp);
	temp = ft_outdirec_syntax_check(*line);
	if (temp)
		return (temp);
	return (0);
}
