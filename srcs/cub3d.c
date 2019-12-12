/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:41:17 by froussel          #+#    #+#             */
/*   Updated: 2019/12/12 13:21:10 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		loop_cub3d(t_info *info)
{
	player_movement(&info->map, &info->player);
	caste_all_ray(info, &info->player);
	generete_wall(info, &info->player);
	generete_sprite(info, &info->player);
	render_map(info, &info->map);
	render_player(info, &info->player);
	render_ray(info);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img.img_ptr,
	0, 0);
	return (0);
}

void	window_initialization(t_info *info, t_img *img)
{
	if (!(info->mlx_ptr = mlx_init()))
		error_global(info);
	if (!(info->win_ptr = mlx_new_window(info->mlx_ptr,
		info->res_x, info->res_y, "cub3d")))
		error_global(info);
	img->img_ptr = mlx_new_image(info->mlx_ptr, info->res_x, info->res_y);
	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
	&img->size_l, &img->endian);
}

int		main(int ac, char **av)
{
	t_info	*info;

	if (ac < 2 || ac > 3)
		error_preso("Wrong number of argument", NULL);
	info = info_initialization();
	read_file_info(av[1], (ac == 3 ? av[2] : NULL), info);
	set_mini_map(info, &info->m_map);
	window_initialization(info, &info->img);
	init_player_on_map(&info->map, &info->player);
	init_textute(info);
	keys_set(info);
	mlx_loop_hook(info->mlx_ptr, loop_cub3d, info);
	if (info->save)
		screen_shot(info);
	else
		mlx_loop(info->mlx_ptr);
	return (EXIT_SUCCESS);
}
