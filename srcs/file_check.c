/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:53:44 by froussel          #+#    #+#             */
/*   Updated: 2019/12/11 15:58:32 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_info_map(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->map_col)
	{
		if (map->map[0][i] != '1' || map->map[map->map_row - 1][i] != '1')
			return (-1);
	}
	i = -1;
	while (++i < map->map_row)
		if (map->map[i][0] != '1' || map->map[i][map->map_col - 1] != '1')
			return (-1);
	return (1);
}

void		check_info(t_info *info, t_map *map)
{
	if (info->res_x > DEFAULT_WINDOW_X || info->res_y > DEFAULT_WINDOW_Y)
	{
		info->res_x = DEFAULT_WINDOW_X;
		info->res_y = DEFAULT_WINDOW_Y;
	}
	if (info->res_x < 100 || info->res_y < 100)
		error_preso("Resolution is to small", info);
	if (info->f < 0)
		error_preso("Unvalid floor color", info);
	if (info->c < 0)
		error_preso("Unvalid ceiling color", info);
	if (map->player_x == -1 || map->player_y == -1)
		error_preso("Unvalid player position on map", info);
	if ((map->map_row < 3 || map->map_col < 3))
		error_preso("Map is to small", info);
	if (check_info_map(map) < 0)
		error_preso("The map is not close", info);
}
