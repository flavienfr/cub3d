#include "cub3d.h"

void	player_movement(t_map *map, t_player *player)
{
	float	move_step;
	float	new_x;
	float	new_y;
	
	player->rotate_angle += player->turn_dir * player->rotate_speed;
	move_step = player->walk_dir * player->move_speed;
	new_x = player->x + cos(player->rotate_angle) * move_step;
	new_y = player->y + sin(player->rotate_angle) * move_step;
	printf("trun dir=%d, player->walk_dir=%d\n", player->turn_dir,player->walk_dir);
	if(!is_wall(map, new_x, new_y))
	{
		//printf("Wall pass%f, %f\n", new_x, new_y);
		player->x = new_x;
		player->y = new_y;
	}
}

int 	loop_cub3d(t_info *info)
{
	player_movement(info->map, info->player);
    caste_all_ray(info, info->player);

	render_map(info, info->map);
	render_player(info, info->player, 1);
	render_ray(info, ray, 1);
	
	generete_wall(info, info->player);
	//clear_buf_rgb(info, BLACK);
	//write_buf_rgb(info);
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	return (0);
}

int		key_press_hook(int key, void *info)
{
	t_info	*ptr_info;
	
	ptr_info = (t_info *)info;

	//printf("la touche =%d\n", key);
	if (key == ESC)
	{
		mlx_destroy_window(ptr_info->mlx_ptr, ptr_info->win_ptr);
		exit(0);//free info ici
	}
	if (key == UP)
		ptr_info->player->walk_dir = 1;
	if (key == DOWN)
		ptr_info->player->walk_dir = -1;
	if (key == RIGHT)
		ptr_info->player->turn_dir = 1;
	if (key == LEFT)
		ptr_info->player->turn_dir = -1;
	//loop_cub3d(ptr_info);
	return (0);
}

int		key_release_hook(int key, void *info)
{
	t_info	*ptr_info;

	ptr_info = (t_info *)info;
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

int		keys_set(t_info *info)//chnger de nom
{
	/*add more cpmme exit cred cross*/
	mlx_hook(info->win_ptr, 2, 0, key_press_hook, info);
	mlx_hook(info->win_ptr, 3, 0, key_release_hook, info);
	//mlx_loop_hook(info->win_ptr, loop_cub3d, info);

	return (0);
}
