/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:21:31 by froussel          #+#    #+#             */
/*   Updated: 2019/12/07 18:52:57 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_player_on_map(t_info *info, t_map *map, t_player *player)
{
	player->x = map->player_x;
	player->y = map->player_y;
	player->rotate_angle = deg_to_rad(map->player_dir);
	map->tile = info->res_x / map->map_col;
}

static void	player_acutal(t_map *map, t_player *player, float n_x, float n_y)
{
	if (!is_wall(map, n_x, n_y))
	{
		player->x = n_x;
		player->y = n_y;
	}
	else
	{
		if (!is_wall(map, player->x, n_y))
			player->y = n_y;
		else if (!is_wall(map, n_x, player->y))
			player->x = n_x;
	}
}

void		player_movement(t_map *map, t_player *player)
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
	player_acutal(map, player, new_x, new_y);
}
