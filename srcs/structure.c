/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:13:43 by froussel          #+#    #+#             */
/*   Updated: 2019/11/27 14:21:46 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_player	*player_initialization(t_info *info)
{
	t_player *player;

	if (!(player = malloc(sizeof(*player))))
		error_strerror(info);
	player->y = 0;
	player->x = 0;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->rotate_angle = 0.0;
	player->move_speed = MOVE_SPEED;
	player->rotate_speed = ROTATE_SPEED * (M_PI / 180);
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
	info->no = NULL;
	info->so = NULL;
	info->we = NULL;
	info->ea = NULL;
	info->s = NULL;
	info->f = -1;
	info->c = -1;
	info->map = map_initialization(info);
	info->player = player_initialization(info);
	info->last_frame = 0.0;
	info->save = 0;
	info->buf_rgb = 0;
	//tile_size = info->res_x / map->map_col = 0;
	return (info);
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
