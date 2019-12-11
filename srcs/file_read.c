/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:08:11 by froussel          #+#    #+#             */
/*   Updated: 2019/12/11 15:47:08 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_info_player_dir(char coord)
{
	if (coord == 'N')
		return (270);
	else if (coord == 'W')
		return (180);
	else if (coord == 'S')
		return (90);
	else if (coord == 'E')
		return (0);
	return (-1);
}

static char	*parse_sprite_player(t_info *info, int row, int *player,
char *tmp_map)
{
	int		col;
	char	*str_row;

	col = -1;
	if (!(str_row = malloc(sizeof(*str_row) * info->map->map_col)))
		return (NULL);
	while (++col < info->map->map_col)
	{
		str_row[col] = tmp_map[col];
		if (first_in_set(str_row[col], PLAYER_INIT_POS))
		{
			info->map->player_dir = parse_info_player_dir(str_row[col]);
			info->map->player_x = col + 0.5;
			info->map->player_y = row + 0.5;
			(*player)++;
		}
		if (*player > 1)
		{
			info->map->player_x = -1;
			info->map->player_y = -1;
		}
		if (str_row[col] == '2')
			init_sprite(info, col, row);
	}
	return (str_row);
}

static int	parse_file_map_2(int fd, char *line, char **map, int *row)
{
	int		ret;
	int		last_idx;
	int		idx;
	int		i;

	last_idx = -1;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (first_in_set(*line, MAP_INFO))
		{
			i = -1;
			idx = 0;
			while (first_in_set(line[++i], MAP_INFO) || line[i] == ' ')
				if (first_in_set(line[i], MAP_INFO))
					line[idx++] = line[i];
			if (last_idx != idx && last_idx != -1)
				ft_strjoin(*map, "Map_Error");
			last_idx = idx;
			ft_strlcpy(line, line, idx + 1);
			*map = ft_strjoin(*map, line);
			(*row)++;
		}
		free(line);
	}
	return ((ret < 0) ? ret : idx);
}

static int	parse_file_map(int fd, char *line, t_info *info, t_map *map)
{
	char	*tmp_map;
	int		row;
	int		player;

	tmp_map = NULL;
	if ((map->map_col = parse_file_map_2(fd, line, &tmp_map, &map->map_row))
		< 0)
		return (-1);
	if (!(map->map = (char **)malloc(sizeof(char *) * map->map_row)))
		return (-1);
	player = 0;
	row = -1;
	while (++row < map->map_row)
	{
		if (!(map->map[row] = parse_sprite_player(info, row, &player,
			&tmp_map[row * map->map_col])))
			return (-1);
	}
	free(tmp_map);
	return (1);
}

void		read_file_info(char *file, char *param2, t_info *info)
{
	int		fd;
	int		i;

	i = 0;
	if (!(ft_strnstr(file, ".cub", ft_strlen(file))))
		error_preso("Unvailable file extension (.cub needed)", info);
	if (ft_strncmp(param2, "–save", ft_strlen(param2)))
		info->save = 1;
	if (!(fd = open(file, O_RDONLY)))
		error_global_close_fd(fd, info);
	if (parse_file_info(fd, NULL, info) < 0)
		error_global_close_fd(fd, info);
	if (parse_file_map(fd, NULL, info, info->map) < 0)
		error_global_close_fd(fd, info);
	check_info(info, info->map);
	close(fd);
}
