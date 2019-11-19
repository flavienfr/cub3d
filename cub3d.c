/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:41:17 by froussel          #+#    #+#             */
/*   Updated: 2019/11/19 18:41:45 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>//-> strerror
#include <stdio.h>// -> <errno.h>
#include <errno.h>

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

//#define WINDOW_X 500
//#define WINDOW_Y 500
#define MAP_INFO "012NSEW"
#define PLAYER_INIT_POS "NSEW"

typedef struct		s_info
{
	void	*mlx_ptr;
	void	*win_ptr;

	int		res_x;
	int		res_y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int 	f[3];
	int 	c[3];
	//mettre dans une autre liste ?
	char	**map;
	int		map_row;
	int		map_col;

	int		player_x;
	int		player_y;
}					t_info;

void	error_read_file_info(int fd, t_info *info)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	if (info->map)
		free(info->map);
	close(fd);
	exit(0);
}
void	error_global(char *s, t_info *info)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	if (info->map)
		free(info->map);
	exit(0);
}
void	error_strerror(t_info *info)
{
	ft_putstr_fd(strerror(errno), 2);
	if (info->map)
		free(info->map);
	exit(0);
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

t_info	*info_initialization(t_info	*info)
{
	int i;

	i = -1;
	info->mlx_ptr = NULL;
	info->win_ptr = NULL;
	if (!(info = malloc(sizeof(*info))))
		exit(0);
	info->res_x = 0;
	info->res_y = 0;
	info->no = NULL;
	info->so = NULL;
	info->we = NULL;
	info->ea = NULL;
	info->s = NULL;
	while (++i < 3)
	{
		info->f[i] = -1;
		info->c[i] = -1;
	}
	info->map = NULL;//pas le droit ?
	info->map_row = 0;
	info->map_col = 0;
	info->player_x = -1;
	info->player_y = -1;
	return (info);
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
	if (!(str = malloc(sizeof(*str))))
		return (NULL);
	str = ft_substr(str, i, len);
	return (str);
}

void	read_resolution(char *line, t_info *info)
{
	int	i;

	i = 0;
	info->res_x = ft_atoi(&line[1]);
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
			info->no = read_path(line);
		else if (line[0] == 'S' && line[1] == 'O' && ++end)
			info->so = read_path(line);
		else if (line[0] == 'W' && line[1] == 'E' && ++end)
			info->we = read_path(line);
		else if (line[0] == 'E' && line[1] == 'A' && ++end)
			info->ea = read_path(line);
		else if (line[0] == 'S' && ++end)
			info->s = read_path(line);
		else if (*line == 'F' && ++end)
			read_floor_ceiling(line, info->f);
		else if (*line == 'C' && ++end)
			read_floor_ceiling(line, info->c);
		free(line);
	}
	return (ret);
}
		//i = -1;
		//col = 0;
		//while (line[++i] && (first_in_set(line[i], MAP_INFO)))
		//	col++;
int		parse_file_map_2(int fd, char *line, char *map, int *row)
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
				if (first_in_set(*line, MAP_INFO))
					line[idx++] = line[i];
			if (last_idx != idx && last_idx != -1)
				ft_strjoin(map, "Map_Error");
			last_idx = idx;
			ft_strjoin(map, line);
			(*row)++;
		}
		free(line);
	}
	return ((ret < 0) ? ret : idx);
}

void	parse_info_player(t_info *info, int row, int col, int *player)
{
	if (*player > 0)
	{
		info->player_x = -1;
		info->player_y = -1;
		return ;
	}
	if (first_in_set(info->map[row][col], PLAYER_INIT_POS))
	{
		info->player_x = row;
		info->player_y = col;
	}
}

int		parse_file_map(int fd, char *line, t_info *info)
{
	char	*tmp_map;
	int		col;
	int		row;
	int		i;
	int		player;

	if ((info->map_col = parse_file_map_2(fd, line, tmp_map, &info->map_row)) < 0)
		return (-1);
	if (!(info->map = (char **)malloc(sizeof(char *) * info->map_row)))
		return (-1);
	i = 0;
	row = 0;
	player = 0;
	while (row < info->map_row)
	{
		col = 0;
		while (col < info->map_col)
		{
			info->map[row][col] = tmp_map[i++];
			parse_info_player(info, row, col, &player);
			col++;
		}
		row++;
	}
	return (1);
}

int		check_info_path_file(char *path)
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
int		check_info_map(t_info *info)
{
//check info->map[0][*]
//check info->map[map_row - 1][*]
//Regarder map_row au lieu map_row - 1
}

int		check_info(t_info *info)
{
	if ((info->res_x * info->res_y) <= 0)//definir min res
		error_global("Resolution is to small", info);
	if (check_info_path_file(info->no) < 0)
		error_global("NO", info);
	if (check_info_path_file(info->so) < 0)
		error_global("SO", info);
	if (check_info_path_file(info->we) < 0)
		error_global("WE", info);
	if (check_info_path_file(info->ea) < 0)
		error_global("EA", info);
	if (check_info_path_file(info->s) < 0)
		error_global("S", info);
	if (check_info_color(info->f) < 0)
		error_global("Bad floor color", info);
	if (check_info_color(info->c) < 0)
		error_global("Bad ceiling color", info);
	if ((info->map_row * info->map_col) <= 0)//definir min map
		error_global("Map is to small", info);	
	if (check_info_map(info) < 0)
		error_global("The map is not close", info);
}

void	read_file_info(char *file, 	t_info	*info)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	info_initialization(info);
	if (!(fd = open(file, O_RDONLY)))
		error_read_file_info(fd, info);
	if (parse_file_info(fd, line, info) < 0)
		error_read_file_info(fd, info);
	if (parse_file_map(fd, line, info) < 0)
		error_read_file_info(fd, info);
	if (check_info(info))
		error_read_file_info(fd, info);
	close(fd);
}
// Donction escape
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
	t_info	info;

	read_file_info(av[1], &info);
	if (!(info.mlx_ptr = mlx_init()))
		error_strerror(&info);
	if (!(info.win_ptr = mlx_new_window(info.mlx_ptr,
		info.res_x, info.res_y, "cub3d")))
		error_strerror(&info);

	mlx_key_hook(info.win_ptr, key_hook, (void *)&info);
	mlx_loop(info.mlx_ptr);
	return (0);
}