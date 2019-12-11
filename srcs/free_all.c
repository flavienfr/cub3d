/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:19:08 by froussel          #+#    #+#             */
/*   Updated: 2019/12/11 15:44:23 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_info *info)
{
	int i;

	i = -1;
	while (++i < info->map->map_row)
		free(info->map->map[i]);
	free(info->map->map);
	free(info->map);
	i = -1;
	while (++i < NB_TEXTURE)
	{
		mlx_destroy_image(info->mlx_ptr, info->tex[i].ptr);
		free(info->tex[i].path);
	}
	if (info->sprite)
		free_sprite(&info->sprite);
	mlx_destroy_image(info->mlx_ptr, info->img.img_ptr);
	mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	free(info);
}

void	free_info(t_info *info)
{
	int i;

	if (info->map->map)
	{
		i = 1;
		while (++i < info->map->map_row)
			free(info->map->map[i]);
		free(info->map->map);
	}
	free(info->map);
	free(info);
}

void	free_sprite(t_sprite **begin)
{
	t_sprite	*sp;
	t_sprite	*nxt;

	sp = *begin;
	while (sp)
	{
		nxt = sp->next;
		free(sp);
		sp = nxt;
	}
	*begin = NULL;
}
