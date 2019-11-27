/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:41:17 by froussel          #+#    #+#             */
/*   Updated: 2019/11/27 16:52:33 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//utils maths----------
float	deg_to_rad(float deg)
{
	return (deg * (M_PI / 180));
}
float	rad_to_deg(float rad)
{
	return (rad * (M_PI / 180));
}
//------------------------
int		is_wall(t_map *map, float x, float y)
{
	int row;
	int col;

	row = floor(y / TILE_SIZE);
	col = floor(x / TILE_SIZE);
	if (map->map[row][col] == '1')/*|| map->./map[x / TILE_SIZE][y / TILE_SIZE] == '2'*/
		return (1);
	return (0);
}

void	init_player_on_map(t_info *info, t_map *map, t_player *player)
{
	player->x = map->player_x * TILE_SIZE;
	player->y = map->player_y * TILE_SIZE;
	player->rotate_angle = deg_to_rad(map->player_dir);
	map->tile = info->res_x / map->map_col;
}
void	window_initialization(t_info *info)
{
	if (!(info->mlx_ptr = mlx_init()))
		error_strerror(info);
	if (!(info->win_ptr = mlx_new_window(info->mlx_ptr,
		info->res_x, info->res_y, "cub3d")))
		error_strerror(info);
}
int		main(int ac, char **av)
{
	t_info	*info;

	if (ac < 2 || ac > 3)
		return (-1);
	info = info_initialization();//why pas dans les params
	read_file_info(av[1], (ac == 3 ? av[2] : NULL), info);
	window_initialization(info);
	init_player_on_map(info, info->map, info->player);
	
	keys_set(info);
	mlx_loop_hook(info->mlx_ptr, loop_cub3d, info);
	//render_map(info, info->map);
	//render_player(info, info->player, 1);

	mlx_loop(info->mlx_ptr);
	return (0);
}

/*
//debug----------------------------------------
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
//-------------------------------------
*/
// other
/*void	update(t_info *info)
{
	float delta_time;
	time_t seconds;
    seconds = time (NULL);

	while (seconds < info->last_frame / FPS)
		seconds = time (NULL);
	delta_time = (seconds - info->last_frame);
	info->last_frame = seconds;

	//move_player(delta_time);
	//caste_all_ray()
}*/