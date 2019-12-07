/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:20:08 by froussel          #+#    #+#             */
/*   Updated: 2019/12/07 19:41:11 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_horizontal(t_info *info, t_player *player, t_map *map, t_ray *ray)
{
	float y_intercept;
	float x_intercept;
	float y_step;
	float x_step;

	y_intercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	y_intercept += ray->face_ud == FAC_DOWN ? TILE_SIZE : 0;
	x_intercept = player->x + (y_intercept - player->y) / tan(ray->angle);
	y_step = TILE_SIZE;
	y_step *= ray->face_ud == FAC_UP ? -1 : 1;
	x_step = TILE_SIZE / tan(ray->angle);
	x_step *= (ray->face_lr == FAC_LEFT && x_step > 0) ? -1 : 1;
	x_step *= (ray->face_lr == FAC_RIGHT && x_step < 0) ? -1 : 1;
	ray->wall_x = x_intercept;
	ray->wall_y = y_intercept;
	while (ray->wall_x >= 0 && ray->wall_x < info->map->map_col
		&& ray->wall_y >= 0 && ray->wall_y < info->map->map_row)
	{
		if (is_wall(map, ray->wall_x, ray->wall_y +
			(ray->face_ud == FAC_UP ? -1 : 0)))
			break ;
		ray->wall_x += x_step;
		ray->wall_y += y_step;
	}
}

void	ray_vertical(t_info *info, t_player *player, t_map *map, t_ray *ray)
{
	float y_intercept;
	float x_intercept;
	float y_step;
	float x_step;

	x_intercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
	x_intercept += ray->face_lr == FAC_RIGHT ? TILE_SIZE : 0;
	y_intercept = player->y + (x_intercept - player->x) * tan(ray->angle);
	x_step = TILE_SIZE;
	x_step *= ray->face_lr == FAC_LEFT ? -1 : 1;
	y_step = TILE_SIZE * tan(ray->angle);
	y_step *= (ray->face_ud == FAC_UP && y_step > 0) ? -1 : 1;
	y_step *= (ray->face_ud == FAC_DOWN && y_step < 0) ? -1 : 1;
	ray->wall_x = x_intercept;
	ray->wall_y = y_intercept;
	while (ray->wall_x >= 0 && ray->wall_x < info->map->map_col
	&& ray->wall_y >= 0 && ray->wall_y < info->map->map_row)
	{
		if (is_wall(map, ray->wall_x +
			(ray->face_lr == FAC_LEFT ? -1 : 0), ray->wall_y))
			break ;
		ray->wall_x += x_step;
		ray->wall_y += y_step;
	}
}

void	cast_ray(t_info *info, t_player *player, t_map *map, t_ray *ray)
{
	float	hor_x;
	float	hor_y;
	float	dist_hor;
	float	dist_ver;

	ray_horizontal(info, player, map, ray);
	hor_x = ray->wall_x;
	hor_y = ray->wall_y;
	ray_vertical(info, player, map, ray);
	if ((dist_ver = dist_point(player->x, player->y, ray->wall_x, ray->wall_y))
		> (dist_hor = dist_point(player->x, player->y, hor_x, hor_y)))
	{
		ray->wall_x = hor_x;
		ray->wall_y = hor_y;
		ray->dist = dist_hor;
	}
	else
	{
		ray->is_vert = 1;
		ray->dist = dist_ver;
	}
}

void	caste_all_ray(t_info *info, t_player *player)
{
	float	ray_angle;
	int		id;

	id = -1;
	ray_angle = player->rotate_angle - (info->fov / 2);
	while (++id < info->res_x)
	{
		info->ray[id] = inisialize_ray(info->ray[id], ray_angle);
		cast_ray(info, player, info->map, &info->ray[id]);
		ray_angle += info->fov / info->res_x;
	}
}
