#include "cub3d.h"

int		key_press_hook(int key, void *info)
{
	t_info	*ptr_info;
	
	ptr_info = (t_info *)info;

	printf("la touche =%d\n", key);
	if (key == ESC)
	{
		mlx_destroy_window(ptr_info->mlx_ptr, ptr_info->win_ptr);
		exit(0);//free info ici
	}
	if (key == UP)
		ptr_info->player.walk_dir_u = 1;
	if (key == DOWN)
		ptr_info->player.walk_dir_d = 1;
	if (key == RIGHT)
		ptr_info->player.turn_dir_r = 1;
	if (key == LEFT)
		ptr_info->player.turn_dir_l = 1;
	if (key == SHIFHT)
	{
		ptr_info->player.move_speed += 3;
		ptr_info->player.rotate_speed += 0.01;
	}
	return (0);
}

int		key_release_hook(int key, void *info)
{
	t_info	*ptr_info;

	ptr_info = (t_info *)info;
	if (key == UP)
		ptr_info->player.walk_dir_u = 0;
	if (key == DOWN)
		ptr_info->player.walk_dir_d = 0;
	if (key == RIGHT)
		ptr_info->player.turn_dir_r = 0;
	if (key == LEFT)
		ptr_info->player.turn_dir_l = 0;
	if (key == SHIFHT)
	{
		ptr_info->player.move_speed -= 3;
		ptr_info->player.rotate_speed -= 0.01;
	}
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
