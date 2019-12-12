/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:13:43 by froussel          #+#    #+#             */
/*   Updated: 2019/12/12 17:07:18 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_map	map_initialization(void)
{
	t_map map;

	map.map_row = 0;
	map.map_col = 0;
	map.player_x = -1;
	map.player_y = -1;
	map.map = NULL;
	return (map);
}

static t_player	player_initialization(void)
{
	t_player player;

	player.y = 0;
	player.x = 0;
	player.turn_dir_r = 0;
	player.turn_dir_l = 0;
	player.walk_dir_u = 0;
	player.walk_dir_d = 0;
	player.straf_r = 0;
	player.straf_l = 0;
	player.rotate_angle = 0.0;
	player.move_speed = MOVE_SPEED;
	player.rotate_speed = ROTATE_SPEED * (M_PI / 180);
	return (player);
}

t_ray			inisialize_ray(t_ray ray, float ray_angle)
{
	ray.angle = norm_angle(ray_angle);
	ray.wall_x = 0;
	ray.wall_y = 0;
	ray.dist = 0;
	ray.is_vert = 0;
	ray.face_ud = (ray.angle > 0 && ray.angle < M_PI) ? FAC_DOWN : FAC_UP;
	ray.face_lr = (ray.angle < 0.5 * M_PI || ray.angle > 1.5 * M_PI) ?
	FAC_RIGHT : FAC_LEFT;
	return (ray);
}

t_info			*info_initialization(void)
{
	t_info *info;

	if (!(info = malloc(sizeof(*info))))
		error_global(info);
	info->mlx_ptr = NULL;
	info->win_ptr = NULL;
	info->res_x = 0;
	info->res_y = 0;
	info->f = -1;
	info->c = -1;
	info->num_sprite = 0;
	info->sprite = NULL;
	info->map = map_initialization();
	info->player = player_initialization();
	info->fov = (FOV * (M_PI / 180));
	info->save = 0;
	return (info);
}
