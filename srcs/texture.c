/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:22:01 by froussel          #+#    #+#             */
/*   Updated: 2019/12/07 19:08:41 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	take_texture(t_info *info, t_tex *tex)
{
	int y;
	int x;

	if (!(tex->ptr = mlx_xpm_file_to_image(info->mlx_ptr,
		tex->path, &tex->width, &tex->height)))
		return (-1);
	if (!(tex->data = (int *)mlx_get_data_addr(tex->ptr,
		&tex->bpp, &tex->size_l, &tex->endian)))
		return (-1);
	y = -1;
	while (++y < TEXTURE_SIZE)
	{
		x = -1;
		while (++x < TEXTURE_SIZE)
			tex->tex[x][y] = (int)tex->data[y * TEXTURE_SIZE + x];
	}
	return (1);
}

void		init_textute(t_info *info)
{
	if (take_texture(info, &info->tex[TEX_NO]) < 0)
		error_preso("loadinf of north texture failed", info);
	if (take_texture(info, &info->tex[TEX_SO]) < 0)
		error_preso("loadinf of south texture failed", info);
	if (take_texture(info, &info->tex[TEX_WE]) < 0)
		error_preso("loadinf of weath texture failed", info);
	if (take_texture(info, &info->tex[TEX_EA]) < 0)
		error_preso("loadinf of east texture failed", info);
	if (take_texture(info, &info->tex[TEX_S]) < 0)
		error_preso("loadinf of south texture failed", info);
}
