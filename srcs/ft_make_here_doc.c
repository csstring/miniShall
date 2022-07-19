/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:50:51 by schoe             #+#    #+#             */
/*   Updated: 2022/07/19 18:28:02 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_doc_prompt(void)
{
	char	*line;

	line = readline("> ");
	return (line);
}

static int	ft_open_here_doc(int index, int count)
{
	char	*temp;
	char	*name;
	int		fd;

	temp = ft_strjoin_free(ft_itoa(index), ft_itoa(count));
	name = ft_strjoin("...", temp);
	free(temp);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		ft_eprintf("ss_shell: %s\n", strerror(errno));
		exit(errno);
	}
	free(name);
	return (fd);
}

static void	ft_make_here_doc2(char *indirec, int index, int count)
{
	int		fd;
	char	*line;
	char	*temp;

	fd = ft_open_here_doc(index, count);
	while (1)
	{
		line = ft_doc_prompt();
		if (line == NULL)
			break ;
		temp = line;
		line = ft_strjoin(temp, "\n");
		if (!ft_strncmp(temp, indirec, ft_strlen(temp) + 1))
		{
			free(temp);
			free(line);
			break ;
		}
		free(temp);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

void	ft_make_here_doc(char ***indirec)
{
	int	i;
	int	count;
	int	k;

	k = 0;
	while (indirec[k])
	{
		count = 0;
		i = 0;
		while (indirec[k][i])
		{
			if (!ft_strncmp(indirec[k][i], "<", 2))
				i++;
			else
			{
				i++;
				ft_make_here_doc2(indirec[k][i], k, count);
				count++;
			}
			i++;
		}
		k++;
	}
}
