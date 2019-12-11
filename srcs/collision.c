/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:48:41 by froussel          #+#    #+#             */
/*   Updated: 2019/12/11 17:10:14 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_sprite(t_map *map, float x, float y)
{
	int row;
	int col;

	row = floor(y / TILE_SIZE);
	col = floor(x / TILE_SIZE);
	if (map->map[row][col] == '2')
		return (1);
	return (0);
}

int		is_wall(t_map *map, float x, float y)
{
	int row;
	int col;

	row = floor(y / TILE_SIZE);
	col = floor(x / TILE_SIZE);
	if (map->map[row][col] == '1')
		return (1);
	return (0);
}
