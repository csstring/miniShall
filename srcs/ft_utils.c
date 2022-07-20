/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:01:51 by schoe             #+#    #+#             */
/*   Updated: 2022/07/20 20:12:27 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_add_space2(char *src, char c, char *str)
{
	int		i;
	int		k;
	char	temp;

	i = 0;
	k = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '\"')
		{
			str[k++] = src[i];
			temp = src[i++];
			while (src[i] != temp)
				str[k++] = src[i++];
		}
		str[k] = src[i];
		if (src[i] == c && src[i + 1] != c)
			str[++k] = ' ';
		k++;
		i++;
	}
	return (k);
}

char	*ft_add_space(char *src, char c, int i, int k)
{
	char	*str;

	while (src[i])
	{
		if (src[i] == c)
			k++;
		i++;
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(src) + k + 1));
	if (!str)
		exit(12);
	k = 0;
	k = ft_add_space2(src, c, str);
	str[k] = '\0';
	free(src);
	return (str);
}

int	ft_direc_count(char **str, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], c, ft_strlen(c)))
			count++;
		i++;
	}
	return (count);
}

void	ft_tolower_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
}

int	ft_taptosp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_pass_quot(str, i);
		if (str[i] == 9 || str[i] == 11)
			str[i] = 32;
		i++;
	}
	i = 0;
	while (str[i])
		if (str[i++] != 32)
			return (0);
	return (1);
}
