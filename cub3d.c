/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:41:17 by froussel          #+#    #+#             */
/*   Updated: 2019/11/20 18:55:38 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>//-> strerror
#include <errno.h>

#include <stdio.h>// -> <errno.h>
#define DP printf("%s : %d\n", __FILE__, __LINE__ );

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

//#define WINDOW_X 500
//#define WINDOW_Y 500
#define MAP_INFO "012NSEW"
#define PLAYER_INIT_POS "NSEW"

typedef struct	s_map
{
	char	**map;
	int		map_row;
	int		map_col;
	int		player_x;
	int		player_y;

}				t_map;

typedef struct		s_info
{
	void			*mlx_ptr;
	void			*win_ptr;

	int				res_x;
	int				res_y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int 			f[3];
	int 			c[3];
	struct s_map 	*map;
}					t_info;

//debug
void	print_info(t_info *info)
{
	printf("res=%d\n",info->res_x);
	printf("res=%d\n",info->res_y);
	printf("coord=%s\n",info->no);
	printf("coord=%s\n",info->so);
	printf("coord=%s\n",info->we);
	printf("coord=%s\n",info->ea);
	printf("coord=%s\n",info->s);
	printf("color: %d, %d, %d\n",info->f[0], info->f[1], info->f[2]);
	printf("color: %d, %d, %d\n",info->c[0], info->c[1], info->c[2]);
}

void	printf_map(t_info *info)
{
	int row;
	int col;

	row = -1;
	while (++row < info->map->map_row)
	{
		col = -1;
		while (++col < info->map->map_col)
			printf("%c", info->map->map[row][col]);
		printf("\n");
	}
}


void	info_free(t_info *info)
{
	if (info->no)
		free(info->no);
	if (info->so)
		free(info->so);
	if (info->we)
		free(info->we);
	if (info->ea)
		free(info->ea);
	if (info->s)
		free(info->s);
	if (info->map)
		free(info->map->map);
}

void	error_read_file_info(int fd, t_info *info)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	info_free(info);
	close(fd);
	exit(0);
}
void	error_global(char *s, t_info *info)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	info_free(info);
	exit(0);
}
void	error_strerror(t_info *info)
{
	ft_putstr_fd(strerror(errno), 2);
	info_free(info);
	exit(0);
}

t_map	*map_initialization(t_info *info)
{
	t_map *map;

	if (!(map = malloc(sizeof(*map))))
		error_strerror(info);
	map->map_row = 0;
	map->map_col = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->map = NULL;
	return (map);
}

t_info	*info_initialization()
{
	t_info *info;
	int i;

	if (!(info = malloc(sizeof(*info))))
		error_strerror(info);
	info->mlx_ptr = NULL;
	info->win_ptr = NULL;
	info->res_x = 0;
	info->res_y = 0;
	info->no = NULL;
	info->so = NULL;
	info->we = NULL;
	info->ea = NULL;
	info->s = NULL;
	i = -1;
	while (++i < 3)
	{
		info->f[i] = -1;
		info->c[i] = -1;
	}
	info->map = map_initialization(info);
	return (info);
}

//utils
int		first_in_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*read_path(char *line)
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
	str = ft_substr(line, i, len);//+1
	return (str);
}

void	read_resolution(char *line, t_info *info)
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

void	read_floor_ceiling(char *line, int *tab)
{
	int i;
	int pos;

	i = 0;
	pos = 0;
	tab[pos++] = ft_atoi(line);
	while (line[i] && pos != 3)
	{
		if (line[i] == ',' && line[i + 1])
			tab[pos++] = ft_atoi(&line[i + 1]);
		i++;
	}
}

int		parse_file_info(int fd, char *line, t_info *info)
{
	int		ret;
	int		end;

	end = 0;
	while (end != 8 && (ret = get_next_line(fd, &line)) > 0)
	{
		if (*line == 'R' && ++end)
			read_resolution(line, info);
		else if (line[0] == 'N' && line[1] == 'O' && ++end)
			info->no = read_path(&line[2]);
		else if (line[0] == 'S' && line[1] == 'O' && ++end)
			info->so = read_path(&line[2]);
		else if (line[0] == 'W' && line[1] == 'E' && ++end)
			info->we = read_path(&line[2]);
		else if (line[0] == 'E' && line[1] == 'A' && ++end)
			info->ea = read_path(&line[2]);
		else if (line[0] == 'S' && ++end)
			info->s = read_path(&line[1]);
		else if (*line == 'F' && ++end)
			read_floor_ceiling(&line[1], info->f);
		else if (*line == 'C' && ++end)
			read_floor_ceiling(&line[1], info->c);
		free(line);
	}
	return (ret);
}

char	*parse_info_player(t_map *map, int row, int *player, char *tmp_map)
{
	int		col;
	char	*str_row;

	col = -1;
	if (!(str_row = malloc(sizeof(*str_row) * map->map_col)))
		return (NULL);
	while (++col < map->map_col)
	{
		str_row[col] = tmp_map[col];
		if (first_in_set(str_row[col], PLAYER_INIT_POS))
		{
			map->player_x = row;
			map->player_y = col;
			(*player)++;
		}
		if (*player > 1)
		{
			map->player_x = -1;
			map->player_y = -1;
		}
	}
	return (str_row);
}

int		parse_file_map_2(int fd, char *line, char **map, int *row)
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

int		parse_file_map(int fd, char *line, t_info *info, t_map *map)
{
	char	*tmp_map;
	int		row;
	int		i;
	int		player;

	tmp_map = NULL;
	if ((map->map_col = parse_file_map_2(fd, line, &tmp_map, &map->map_row)) < 0)
		return (-1);
	if (!(map->map = (char **)malloc(sizeof(char *) * map->map_row)))
		return (-1);
	player = 0;
	row = -1;
	while (++row < map->map_row)
	{
		if (!(map->map[row] = parse_info_player(map, row, &player,
			&tmp_map[row * map->map_col])))
			return (-1);
	}
	free(tmp_map);
	//printf_map(info);
	return (1);
}

int		check_info_path_file(char *path)//necessaire d'ouvrir ?
{
	int fd;

	fd = open(path, O_RDONLY);
	close(fd);
	return (fd);
}

int		check_info_color(int *nb)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		if (nb[i] < 0 || nb[i] > 255)
			return (-1);
	}
	return (1);
}
int		check_info_map(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->map_col)
	{
		if (map->map[0][i] != '1' || map->map[map->map_row - 1][i] != '1')
			return (-1);
	}

	i = -1;
	while (++i < map->map_row)
		if (map->map[i][0] != '1' || map->map[i][map->map_col - 1] != '1')
			return (-1);
	return (1);
}

void	check_info(t_info *info, t_map *map)
{
	if ((info->res_x * info->res_y) <= 0)//definir min res
		error_global("Resolution is to small", info);
	/*if (check_info_path_file(info->no) < 0)
		error_global("NO", info);
	if (check_info_path_file(info->so) < 0)
		error_global("SO", info);
	if (check_info_path_file(info->we) < 0)
		error_global("WE", info);
	if (check_info_path_file(info->ea) < 0)
		error_global("EA", info);
	if (check_info_path_file(info->s) < 0)
		error_global("S", info);*/
	if (check_info_color(info->f) < 0)
		error_global("Unvalid floor color", info);
	if (check_info_color(info->c) < 0)
		error_global("Unvalid ceiling color", info);	
	if (map->player_x == -1 || map->player_y == -1)
		error_global("Unvalid player position on map", info);
	if ((map->map_row * map->map_col) <= 0)//definir min map
		error_global("Map is to small", info);	
	if (check_info_map(map) < 0)
		error_global("The map is not close", info);
}

void	read_file_info(char *file, 	t_info	*info)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	if (!(fd = open(file, O_RDONLY)))
		error_read_file_info(fd, info);
	if (parse_file_info(fd, line, info) < 0)
		error_read_file_info(fd, info);
	//print_info(info);//debug
	if (parse_file_map(fd, line, info, info->map) < 0)
		error_read_file_info(fd, info);
	check_info(info, info->map);
	close(fd);
}
// fonction escape
int		key_hook(int key, void *info)
{
	t_info*ptr_info = (t_info *)info;

	//printf("la touche =%d\n", key);
	if (key == 53)
	{
		mlx_destroy_window(ptr_info->mlx_ptr, ptr_info->win_ptr);
		exit(0);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_info	*info;

	info = info_initialization();
	read_file_info(av[1], info);
	if (!(info->mlx_ptr = mlx_init()))
		error_strerror(info);
	if (!(info->win_ptr = mlx_new_window(info->mlx_ptr,
		info->res_x, info->res_y, "cub3d")))
		error_strerror(info);
	mlx_key_hook(info->win_ptr, key_hook, (void *)info);
	mlx_loop(info->mlx_ptr);
	return (0);
}
