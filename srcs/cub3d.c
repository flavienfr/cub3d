/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:41:17 by froussel          #+#    #+#             */
/*   Updated: 2019/11/23 12:38:45 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int		is_wall(t_map *map, int x, int y);
void	player_movement(t_map *map, t_player *player);

//debug----------------------------------------
void	print_info(t_info *info)
{
	printf("res=%d\n",info->res_x);
	printf("res=%d\n",info->res_y);
	printf("coord=%s\n",info->no);
	printf("coord=%s\n",info->so);
	printf("coord=%s\n",info->we);
	printf("coord=%s\n",info->ea);
	printf("coord=%s\n",info->s);
	printf("color: %d\n",info->f);
	printf("color: %d\n",info->c);
}

void	printf_map(t_info *info)
{
	int row;
	int col;

	row = -1;
	while (++row < info->map->map_row)
	{
		col = -1;
		while (++col < info->map->map_col)
			printf("%c", info->map->map[row][col]);
		printf("\n");
	}
}
//-------------------------------------

//utils maths----------
float	deg_to_rad(float deg)
{
	return (deg * (M_PI / 180));
}
float	rad_to_deg(float rad)
{
	return (rad * (M_PI / 180));
}
//------------------------

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

void	init_player_on_map(t_info *info, t_map *map, t_player *player)
{
	printf("JE SUI ICI X=%d Y=%d\n", map->player_x, map->player_y);
	player->x = (map->player_x / info->res_x) * info->res_x;/** TILE_SIZE;*/
	player->y = map->player_y * TILE_SIZE;
	player->rotate_angle = deg_to_rad(map->player_dir);
	map->tile = info->res_x / map->map_col;
}

int		key_release_hook(int key, void *info)
{
	t_info	*ptr_info;
	
	ptr_info = (t_info *)info;
	key++;
	if (key == UP)
		ptr_info->player->walk_dir = 0;
	if (key == DOWN)
		ptr_info->player->walk_dir = 0;
	if (key == RIGHT)
		ptr_info->player->turn_dir = 0;
	if (key == LEFT)
		ptr_info->player->turn_dir = 0;
	return (0);
}

int		key_press_hook(int key, void *info)
{
	t_info	*ptr_info;
	
	ptr_info = (t_info *)info;
	
	printf("la touche =%d\n", key);
	if (key == ESC)
	{
		mlx_destroy_window(ptr_info->mlx_ptr, ptr_info->win_ptr);
		exit(0);
	}
	if (key == UP)
		ptr_info->player->walk_dir = 1;
	if (key == DOWN)
		ptr_info->player->walk_dir = -1;
	if (key == RIGHT)
		ptr_info->player->turn_dir = 1;
	if (key == LEFT)
		ptr_info->player->turn_dir = -1;
	//printf("walk=%d turn=%d\n",ptr_info->player->walk_dir, ptr_info->player->turn_dir);
	player_movement(ptr_info->map, ptr_info->player);
	printf("player_x=%d player_y =%d\n",ptr_info->player->x, ptr_info->player->y);
	mlx_pixel_put (ptr_info->mlx_ptr, ptr_info->win_ptr, ptr_info->player->x / TILE_SIZE, ptr_info->player->y/ TILE_SIZE, ptr_info->c);
	return (0);
}

int		keys_set(t_info *info)
{
	mlx_hook(info->win_ptr, 2, 0, key_press_hook, info);
	mlx_hook(info->win_ptr, 3, 0, key_release_hook, info);

	return (0);
}

int		is_wall(t_map *map, int col, int row) //j'ai inverse x y carc dans map c l'inverse
{
	//printf("x=%d, y=%d\n", x/30, y/30);
	//printf("%c\n", map->map[x / TILE_SIZE][y / TILE_SIZE]);//4513
	if (map->map[row / TILE_SIZE][col / TILE_SIZE] == '1'/*|| map->map[x / TILE_SIZE][y / TILE_SIZE] == '2'*/)
		return (1);
	return (0);
}

void	player_movement(t_map *map, t_player *player)
{
	float	move_step;
	int		new_x;
	int		new_y;
	
	//printf("walk=%d\n", player->walk_dir);
	player->rotate_angle += player->turn_dir * player->rotate_speed;
	move_step = player->walk_dir * player->move_speed;
	new_x = player->x + cos(player->rotate_angle) * move_step;
	new_y = player->y + sin(player->rotate_angle) * move_step;
	if(!is_wall(map, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void 	cub3d_hub(t_info *info)
{
	init_player_on_map(info, info->map, info->player);
	printf("x=%d y=%d\n",info->player->x,info->player->y);
	//mlx_pixel_put (info->mlx_ptr, info->win_ptr, info->player->x, info->player->y, info->c);
	keys_set(info);
	//player_movement(info->map, info->player);
}

int		main(int ac, char **av)
{
	t_info	*info;

	if (ac < 2 || ac > 3)
		return (-1);
	info = info_initialization();
	read_file_info(av[1], av[2], info);
	//print_info(info);
	if (!(info->mlx_ptr = mlx_init()))
		error_strerror(info);
	if (!(info->win_ptr = mlx_new_window(info->mlx_ptr,
		info->res_x, info->res_y, "cub3d")))
		error_strerror(info);
	printf_map(info);
	cub3d_hub(info);
	mlx_loop(info->mlx_ptr);
	return (0);
}





/*
//debug----------------------------------------
void	print_info(t_info *info)
{
	printf("res=%d\n",info->res_x);
	printf("res=%d\n",info->res_y);
	printf("coord=%s\n",info->no);
	printf("coord=%s\n",info->so);
	printf("coord=%s\n",info->we);
	printf("coord=%s\n",info->ea);
	printf("coord=%s\n",info->s);
	printf("color: %d, %d, %d\n",info->f[0], info->f[1], info->f[2]);
	printf("color: %d, %d, %d\n",info->c[0], info->c[1], info->c[2]);
}

void	printf_map(t_info *info)
{
	int row;
	int col;

	row = -1;
	while (++row < info->map->map_row)
	{
		col = -1;
		while (++col < info->map->map_col)
			printf("%c", info->map->map[row][col]);
		printf("\n");
	}
}
//-------------------------------------
*/