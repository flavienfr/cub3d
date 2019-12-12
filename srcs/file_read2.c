/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:13:31 by froussel          #+#    #+#             */
/*   Updated: 2019/12/12 14:15:46 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_path(char *line)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (line[i] == ' ')
		i++;
	len = i;
	while (line[len] && line[len] != ' ')
		len++;
	str = ft_substr(line, i, len);
	return (str);
}

static void	read_resolution(char *line, t_info *info)
{
	int	i;

	i = 1;
	info->res_x = ft_atoi(&line[i]);
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	info->res_y = ft_atoi(&line[i]);
}

static int	read_floor_ceiling(char *line)
{
	int i;
	int pos;
	int color;
	int tmp;

	i = 0;
	pos = 0;
	if ((color = ft_atoi(line)) > 255 || color < 0)
		return (-1);
	while (line[i] && pos != 3)
	{
		if (line[i] == ',' && line[i + 1])
		{
			if ((tmp = ft_atoi(&line[i + 1])) > 255 || tmp < 0)
				return (-1);
			color <<= 8;
			color += tmp;
		}
		i++;
	}
	return (color);
}

int			parse_file_info(int fd, char *line, t_info *info)
{
	int		ret;
	int		end;

	end = 0;
	while (end != 8 && (ret = get_next_line(fd, &line)) > 0)
	{
		if (*line == 'R' && ++end)
			read_resolution(line, info);
		else if (line[0] == 'N' && line[1] == 'O' && ++end)
			info->tex[TEX_NO].path = read_path(&line[2]);
		else if (line[0] == 'S' && line[1] == 'O' && ++end)
			info->tex[TEX_SO].path = read_path(&line[2]);
		else if (line[0] == 'W' && line[1] == 'E' && ++end)
			info->tex[TEX_WE].path = read_path(&line[2]);
		else if (line[0] == 'E' && line[1] == 'A' && ++end)
			info->tex[TEX_EA].path = read_path(&line[2]);
		else if (line[0] == 'S' && ++end)
			info->tex[TEX_S].path = read_path(&line[1]);
		else if (*line == 'F' && ++end)
			info->f = read_floor_ceiling(&line[1]);
		else if (*line == 'C' && ++end)
			info->c = read_floor_ceiling(&line[1]);
		free(line);
	}
	return (ret);
}
