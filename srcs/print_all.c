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

	int h;
	int w;

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

void	render_player(t_info *info, t_player *player)
{
	t_anchor anc;


	anc.x = player->x * MINI_MAP;
	anc.y = player->y * MINI_MAP;
	anc.y_goal = anc.y + PLAYER_WIDTH * MINI_MAP;
	anc.x_goal = anc.x + PLAYER_WIDTH * MINI_MAP;
	print_rect(info, anc, GREEN);
}

void	render_map(t_info *info, t_map *map)
{
	int row;
	int col;
	t_anchor anc;

	row = -1;
	while (++row < map->map_row)
	{
		col = -1;
		while (++col < map->map_col)
		{
			anc.x = col * TILE_SIZE * MINI_MAP;
			anc.y = row * TILE_SIZE * MINI_MAP;
			anc.y_goal =  anc.y + TILE_SIZE * MINI_MAP;
			anc.x_goal = anc.x + TILE_SIZE * MINI_MAP;
			print_rect(info, anc, map->map[row][col] == '1' ? BLACK : GREY);
		}
	}
}

void	render_ray(t_info *info)
{
	int id;

	id = -1;
	//if (!ray->wall_x)
	//	return ;
	while (++id < info->res_x)
    	info->img.data[((int)floor(ray[id].wall_y * MINI_MAP)) * info->res_x + ((int)floor(ray[id].wall_x * MINI_MAP))] = YELLOW;
	//info->buf_rgb[(int)floor(ray[id].wall_x * MINI_MAP)][(int)floor(ray[id].wall_y * MINI_MAP)] = YELLOW;
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
			info->buf_rgb[x][y] = info->c;
	}
	y = (info->res_y / 2) - 1;
	while (++y < info->res_y)
	{
		x = -1;
		while (++x < info->res_x)
			info->buf_rgb[x][y] = info->f;
	}
}
