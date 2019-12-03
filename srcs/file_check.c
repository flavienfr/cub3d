/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:53:44 by froussel          #+#    #+#             */
/*   Updated: 2019/12/03 17:04:12 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
static int  check_info_path_file(t_info *info, char *path)
{
	void	*image_pointer;
	
	image_pointer = mlx_new_image(info->mlx_ptr, TEXTURE_WIDTH, TEXTURE_HEIGHT);//protection
	info->no = mlx_get_data_addr(image_pointer, &bpp, &size_line, &endian);

}*/

static int check_info_map(t_map *map)
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

void        check_info(t_info *info, t_map *map)
{
	if ((info->res_x * info->res_y) <= 0)//definir min res
		error_global("Resolution is to small", info);
	/*if (check_info_path_file(info->no) < 0)
		error_global("NO", info);
	if (check_info_path_file(info->so) < 0)
		error_global("SO", info);
	if (check_info_path_file(info->we) < 0)
		error_global("WE", info);
	if (check_info_path_file(info->ea) < 0)
		error_global("EA", info);
	if (check_info_path_file(info->s) < 0)
		error_global("S", info);*/
	if (info->f < 0)
		error_global("Unvalid floor color", info);
	if (info->c < 0)
		error_global("Unvalid ceiling color", info);	
	if (map->player_x == -1 || map->player_y == -1)
		error_global("Unvalid player position on map", info);
	if ((map->map_row * map->map_col) <= 0)//definir min map
		error_global("Map is to small", info);	
	if (check_info_map(map) < 0)
		error_global("The map is not close", info);
}
