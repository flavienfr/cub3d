#include "cub3d.h"

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
		ptr_info->player.walk_dir = 1;
	if (key == DOWN)
		ptr_info->player.walk_dir = -1;
	if (key == RIGHT)
		ptr_info->player.turn_dir = 1;
	if (key == LEFT)
		ptr_info->player.turn_dir = -1;
	return (0);
}

int		key_release_hook(int key, void *info)
{
	t_info	*ptr_info;

	ptr_info = (t_info *)info;
	if (key == UP)
		ptr_info->player.walk_dir = 0;
	if (key == DOWN)
		ptr_info->player.walk_dir = 0;
	if (key == RIGHT)
		ptr_info->player.turn_dir = 0;
	if (key == LEFT)
		ptr_info->player.turn_dir = 0;
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
