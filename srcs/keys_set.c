/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:21:02 by froussel          #+#    #+#             */
/*   Updated: 2019/12/12 18:15:03 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	exit_success(t_info *info)
{
	free_all(info);
	exit(EXIT_SUCCESS);
	return (1);
}

static int	key_press_hook(int key, void *info)
{
	t_info	*ptr_info;

	ptr_info = (t_info *)info;
	if (key == ESC)
		exit_success(info);
	if (key == UP)
		ptr_info->player.walk_dir_u = 1;
	if (key == DOWN)
		ptr_info->player.walk_dir_d = 1;
	if (key == R_AROW)
		ptr_info->player.turn_dir_r = 1;
	if (key == L_AROW)
		ptr_info->player.turn_dir_l = 1;
	if (key == LEFT)
		ptr_info->player.straf_l = 1;
	if (key == RIGHT)
		ptr_info->player.straf_r = -1;
	if (key == SHIFHT)
	{
		ptr_info->player.move_speed += RUN_SPEED;
		ptr_info->player.rotate_speed += RUN_ROTATE_SPEED - ROTATE_SPEED;
	}
	return (0);
}

static int	key_release_hook(int key, void *info)
{
	t_info	*ptr_info;

	ptr_info = (t_info *)info;
	if (key == UP)
		ptr_info->player.walk_dir_u = 0;
	if (key == DOWN)
		ptr_info->player.walk_dir_d = 0;
	if (key == R_AROW)
		ptr_info->player.turn_dir_r = 0;
	if (key == L_AROW)
		ptr_info->player.turn_dir_l = 0;
	if (key == LEFT)
		ptr_info->player.straf_l = 0;
	if (key == RIGHT)
		ptr_info->player.straf_r = 0;
	if (key == SHIFHT)
	{
		ptr_info->player.move_speed -= RUN_SPEED;
		ptr_info->player.rotate_speed -= RUN_ROTATE_SPEED - ROTATE_SPEED;
	}
	return (0);
}

int			keys_set(t_info *info)
{
	mlx_hook(info->win_ptr, 2, 0, key_press_hook, info);
	mlx_hook(info->win_ptr, 3, 0, key_release_hook, info);
	mlx_hook(info->win_ptr, 17, 0, exit_success, info);
	return (0);
}
