/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:53:44 by froussel          #+#    #+#             */
/*   Updated: 2019/12/04 16:34:49 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int  check_info_path_file(t_info *info/*, t_tex *tex*/)
{
	t_tex tex;

	printf("path=%s\n", tex.path);
	if (!(tex.ptr = mlx_xpm_file_to_image (info->win_ptr, "./texture/bluestone.XPM", &tex.width, &tex.height)))
		return (-1);
	//if (!(tex->data = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->size_l, &tex->endian)))
	//	return (-1);
	return (1);
}

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
	if (check_info_path_file(info/*, &info->tex[TEX_NO]*/) < 0)
		error_global("NO", info);
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
