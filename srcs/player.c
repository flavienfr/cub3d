#include "cub3d.h"

void	init_player_on_map(t_info *info, t_map *map, t_player *player)
{
	player->x = map->player_x * TILE_SIZE;
	player->y = map->player_y * TILE_SIZE;
	player->rotate_angle = deg_to_rad(map->player_dir);
	map->tile = info->res_x / map->map_col;
}

void	player_movement(t_map *map, t_player *player)
{
	float	move_step;
	float	new_x;
	float	new_y;
	int		turn_dir;
	int		walk_dir;
	
	turn_dir = 0;
	walk_dir = 0;
	if (player->turn_dir_l)
		turn_dir = -1;
	else if (player->turn_dir_r)
		turn_dir = 1;
	if (player->walk_dir_u)
		walk_dir = 1;
	else if (player->walk_dir_d)
		walk_dir = -1;
	player->rotate_angle += turn_dir * player->rotate_speed;
	move_step = walk_dir * player->move_speed;
	new_x = player->x + cos(player->rotate_angle) * move_step;
	new_y = player->y + sin(player->rotate_angle) * move_step;
	if(!is_wall(map, new_x, new_y))
	{
		//printf("Wall pass%f, %f\n", new_x, new_y);
		player->x = new_x;
		player->y = new_y;
	}
}