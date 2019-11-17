/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:25:30 by froussel          #+#    #+#             */
/*   Updated: 2019/11/05 11:04:39 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	free_all(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (-1);
}

static int	is_line(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

static int	give_line(char **str, char **line, int ret)
{
	char	*s;
	int		len;

	s = NULL;
	if (!*str || !**str)
	{
		if (!(*line = ft_strdup("\0")))
			return (free_all(str));
	}
	else if ((len = is_line(*str)) >= 0)
	{
		if (!(*line = ft_substr(*str, 0, len)))
			return (free_all(str));
		if (!(s = ft_substr(*str, len + 1, ft_strlen(*str))))
			return (free_all(str));
		ret = 1;
	}
	else
	{
		if (!(*line = ft_substr(*str, 0, ft_strlen(*str))))
			return (free_all(str));
	}
	free_all(str);
	*str = s;
	return (ret);
}

int			get_next_line(int fd, char **line)
{
	static char	*str[10000];
	char		buff[BUFFER_SIZE + 1];
	char		*new_str;
	ssize_t		i;

	if (!line || fd < 0)
		return (free_all(&str[fd]));
	while ((i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[i] = '\0';
		if (!(new_str = ft_strjoin(str[fd], buff)))
			return (free_all(&str[fd]));
		free_all(&str[fd]);
		str[fd] = new_str;
		if (is_line(str[fd]) >= 0)
			break ;
	}
	if (i < 0)
		return (free_all(&str[fd]));
	return (give_line(&str[fd], line, 0));
}
