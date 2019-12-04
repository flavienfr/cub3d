/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:13:43 by froussel          #+#    #+#             */
/*   Updated: 2019/12/04 15:39:42 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray   inisialize_ray(t_ray ray, float ray_angle)
{
	ray.angle = norm_angle(ray_angle);
	ray.wall_x = 0;
	ray.wall_y = 0;
	ray.dist = 0;
	ray.is_vert = 0;
	ray.is_facing_down = ray.angle  > 0 && ray.angle  < M_PI;
	ray.is_facing_up = !ray.is_facing_down;
	ray.is_facing_right = ray.angle  < 0.5 * M_PI || ray.angle  > 1.5 * M_PI;
	ray.is_facing_left = !ray.is_facing_right;
    return (ray);
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
	map->tile = 0;
	return (map);
}

t_player	player_initialization()
{
	t_player player;

	//if (!(player = malloc(sizeof(*player))))
	//	error_strerror(info);
	player.y = 0;
	player.x = 0;
	player.turn_dir_r = 0;
	player.turn_dir_l = 0;
	player.walk_dir_u = 0;
	player.walk_dir_d = 0;
	player.rotate_angle = 0.0;
	player.move_speed = MOVE_SPEED;
	player.rotate_speed = ROTATE_SPEED * (M_PI / 180);
	return (player);
}

t_info	*info_initialization()
{
	t_info *info;

	if (!(info = malloc(sizeof(*info))))
		error_strerror(info);
	info->mlx_ptr = NULL;
	info->win_ptr = NULL;
	info->res_x = 0;
	info->res_y = 0;
	info->f = -1;
	info->c = -1;
	info->map = map_initialization(info);
	info->player = player_initialization();
	info->last_frame = 0.0;
	info->save = 0;
	clear_buf_rgb(info, BLUE);
	//info->buf_rgb[DEFAULT_WINDOW_X][DEFAULT_WINDOW_Y];
	//tile_size = info->res_x / map->map_col = 0;
	return (info);
}

void	info_free(t_info *info)
{
	int i;

	i = -1;
	if (info->map)
		free(info->map->map);
	while (++i < NB_TEXTURE)
		free(info->tex[i].path);
}
