/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:21:44 by froussel          #+#    #+#             */
/*   Updated: 2019/12/11 18:13:47 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_mini_map(t_info *info, t_mini_map *m_map)
{
	int	ratio_x;
	int ratio_y;
	int diff;

	ratio_x = info->res_x / info->map.map_col;
	ratio_y = info->res_y / info->map.map_row;
	diff = ratio_x - ratio_y;
	m_map->map = ratio_y + (diff / 2);
	m_map->map += (m_map->map % 2) ? 1 : 0;
	m_map->player = m_map->map * 0.3;
	m_map->player = m_map->player < 10 ? 10 : m_map->player;
}

static void	print_rect(t_info *info, t_anchor anc, int color)
{
	int	h;
	int	w;

	h = anc.y;
	while (h < anc.y_goal)
	{
		w = anc.x;
		while (w < anc.x_goal)
		{
			info->img.data[h * info->res_x + w] = color;
			w++;
		}
		h++;
	}
}

void		render_player(t_info *info, t_player *player)
{
	t_anchor anc;

	anc.x = player->x * MINI_MAP * info->m_map.map;
	anc.y = player->y * MINI_MAP * info->m_map.map;
	anc.y_goal = anc.y + info->m_map.player * MINI_MAP;
	anc.x_goal = anc.x + info->m_map.player * MINI_MAP;
	print_rect(info, anc, GREEN);
}

void		render_map(t_info *info, t_map *map)
{
	int			row;
	int			col;
	t_anchor	anc;

	row = -1;
	while (++row < map->map_row)
	{
		col = -1;
		while (++col < map->map_col)
		{
			anc.x = col * info->m_map.map * MINI_MAP;
			anc.y = row * info->m_map.map * MINI_MAP;
			anc.y_goal = anc.y + info->m_map.map * MINI_MAP;
			anc.x_goal = anc.x + info->m_map.map * MINI_MAP;
			if (map->map[row][col] == '1')
				print_rect(info, anc, BLACK);
			else if (map->map[row][col] == '2')
				print_rect(info, anc, RED);
			else
				print_rect(info, anc, GREY);
		}
	}
}

void		render_ray(t_info *info)
{
	int id;

	id = -1;
	while (++id < info->res_x)
		info->img.data[((int)floor(info->ray[id].wall_y * info->m_map.map
		* MINI_MAP)) * info->res_x + ((int)floor(info->ray[id].wall_x
		* info->m_map.map * MINI_MAP))] = YELLOW;
}
