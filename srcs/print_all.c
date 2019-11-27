#include "cub3d.h"

typedef struct  s_anchor
{
	int 	x;
	int 	y;
	int 	y_goal;
	int 	x_goal;
}		        t_anchor;

void	print_rect(t_info *info, t_anchor anc, int color)
{
	int row;
	int col;

	row = anc.y;
	while (row < anc.y + anc.y_goal)
	{
		col = anc.x;
		while (col < anc.x + anc.y_goal)
		{
			mlx_pixel_put (info->mlx_ptr, info->win_ptr, col, row, color);
			col++;
		}
		row++;
	}	
}

void	render_player(t_info *info, t_player *player, int write)
{
	t_anchor anc;


	anc.x = player->x * MINI_MAP;
	anc.y = player->y * MINI_MAP;
	anc.y_goal = anc.x_goal = PLAYER_WIDTH * MINI_MAP;
	print_rect(info, anc, write ? 65280 : 16777215);

}

void	render_map(t_info *info, t_map *map)
{
	int row;
	int col;
	t_anchor anc;

	row = -1;
	while (++row < info->map->map_row)
	{
		col = -1;
		while (++col < info->map->map_col)
		{
			anc.x = col * TILE_SIZE * MINI_MAP;
			anc.y = row * TILE_SIZE * MINI_MAP;
			anc.y_goal = anc.x_goal = TILE_SIZE * MINI_MAP;
			//TILE *= MINI_MAP;
			print_rect(info, anc, map->map[row][col] == '1' ? 16711680 : 16777215);
		}
	}
}

void	render_ray(t_info *info, t_ray *ray, int print)
{
	int id;

	id = -1;
	if (!ray->wall_x)
		return ;
	while (++id < info->res_x)
		mlx_pixel_put (info->mlx_ptr, info->win_ptr, ray[id].wall_x * MINI_MAP,
		ray[id].wall_y * MINI_MAP, print ? 255 : 16777215);
}

void	print_ceiling_floor(t_info *info)
{
	int x;
	int y;

	y = -1;
	while (++y < info->res_y / 2)
	{
		x = -1;
		while (++x < info->res_x)
			mlx_pixel_put (info->mlx_ptr, info->win_ptr, x, y, info->c);
	}
	y = (info->res_y / 2) - 1;
	while (++y < info->res_y)
	{
		x = -1;
		while (++x < info->res_x)
			mlx_pixel_put (info->mlx_ptr, info->win_ptr, x, y, info->f);
	}
}
