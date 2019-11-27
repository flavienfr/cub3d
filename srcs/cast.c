#include "cub3d.h"

float	norm_angle(float angle)
{
	angle = remainder(angle, M_PI * 2);//angle % (2 * pi) ?
	if (angle < 0)
		angle += M_PI * 2;
	return (angle);
}

float	dist_point(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

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

void	ray_horizontal(t_info *info, t_player *player, t_map *map ,t_ray *ray)
{
	float 	y_intercept;
	float 	x_intercept;
	float 	y_step;
	float 	x_step;

	y_intercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	y_intercept += ray->is_facing_down ? TILE_SIZE : 0;
	x_intercept = player->x + (y_intercept - player->y) / tan(ray->angle);


	y_step = TILE_SIZE;
	y_step *= ray->is_facing_up ? -1 : 1;
	x_step = TILE_SIZE / tan(ray->angle);
	x_step *= (ray->is_facing_left && x_step > 0) ? -1 : 1;
	x_step *= (ray->is_facing_right && x_step < 0) ? -1 : 1;

	ray->wall_x = x_intercept;
	ray->wall_y = y_intercept;
	while (ray->wall_x >= 0 && ray->wall_x <= info->res_x
	&& ray->wall_y >= 0 && ray->wall_y <= info->res_y)
	{
		if (is_wall(map, ray->wall_x, ray->wall_y + (ray->is_facing_up ? -1 : 0)))
			break ;// add wall content
		ray->wall_x += x_step;
		ray->wall_y += y_step;
	}
}

void	ray_vertical(t_info *info, t_player *player, t_map *map ,t_ray *ray)
{
	float 	y_intercept;
	float 	x_intercept;
	float 	y_step;
	float 	x_step;

	x_intercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
	x_intercept += ray->is_facing_right ? TILE_SIZE : 0;
	y_intercept = player->y + (x_intercept - player->x) * tan(ray->angle);

	x_step = TILE_SIZE;
	x_step *= ray->is_facing_left ? -1 : 1;
	y_step = TILE_SIZE * tan(ray->angle);
	y_step *= (ray->is_facing_up && y_step > 0) ? -1 : 1;
	y_step *= (ray->is_facing_down && y_step < 0) ? -1 : 1;

	ray->wall_x = x_intercept;
	ray->wall_y = y_intercept;
	while (ray->wall_x >= 0 && ray->wall_x <= info->res_x
	&& ray->wall_y >= 0 && ray->wall_y <= info->res_y)
	{
		if (is_wall(map, ray->wall_x + (ray->is_facing_left ? -1 : 0), ray->wall_y))
			break ;// add wall content
		ray->wall_x += x_step;
		ray->wall_y += y_step;
	}
}

void	cast_ray(t_info *info, t_player *player, t_map *map ,t_ray *ray)
{
	float	hor_x;
	float	hor_y;
	float	dist_hor;
	float	dist_ver;

	ray_horizontal(info, player, map , ray);
	hor_x = ray->wall_x;
	hor_y = ray->wall_y;
	ray_vertical(info, player, map , ray);
	if ((dist_ver = dist_point(player->x, player->y, ray->wall_x, ray->wall_y))
		> (dist_hor = dist_point(player->x, player->y, hor_x, hor_y)))
	{
		ray->wall_x  = hor_x;
		ray->wall_y = hor_y;
		ray->dist = dist_hor;
	}
	else
	{
		ray->is_vert = 1;
		ray->dist = dist_ver;
	}
}

void	caste_all_ray(t_info *info, t_player * player)
{
	float 	ray_angle;
	int 	id;

	id = -1;
	ray_angle = player->rotate_angle - (FOV / 2);
	while (++id < info->res_x)
	{
        ray[id] = inisialize_ray(ray[id], ray_angle);//&ray [id]
		cast_ray(info, player, info->map, &ray[id]);
		ray_angle += FOV / info->res_x;
	}
}