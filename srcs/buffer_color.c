/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:19:55 by froussel          #+#    #+#             */
/*   Updated: 2019/12/07 19:24:03 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_buf_rgb(t_info *info, int color)
{
	int x;
	int y;

	y = -1;
	while (++y < info->res_y)
	{
		x = -1;
		while (++x < info->res_x)
			info->buf_rgb[x][y] = color;
	}
}

void	write_buf_rgb(t_info *info)
{
	int x;
	int y;

	y = -1;
	while (++y < info->res_y)
	{
		x = -1;
		while (++x < info->res_x)
			mlx_pixel_put(info->mlx_ptr, info->win_ptr,
			x, y, info->buf_rgb[x][y]);
	}
}
