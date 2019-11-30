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
	
	player->rotate_angle += player->turn_dir * player->rotate_speed;
	move_step = player->walk_dir * player->move_speed;
	new_x = player->x + cos(player->rotate_angle) * move_step;
	new_y = player->y + sin(player->rotate_angle) * move_step;
	//printf("trun dir=%d, player->walk_dir=%d\n", player->turn_dir,player->walk_dir);
	if(!is_wall(map, new_x, new_y))
	{
		//printf("Wall pass%f, %f\n", new_x, new_y);
		player->x = new_x;
		player->y = new_y;
	}
}