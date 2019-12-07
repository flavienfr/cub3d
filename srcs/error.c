/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:13:18 by froussel          #+#    #+#             */
/*   Updated: 2019/12/07 19:27:18 by froussel         ###   ########.fr       */
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

void	error_preso(char *s, t_info *info)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	free_info(info);
	exit(EXIT_FAILURE);
}

void	error_global(t_info *info)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	free_info(info);
	exit(EXIT_FAILURE);
}

void	error_global_close_fd(int fd, t_info *info)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	close(fd);
	free_info(info);
	exit(EXIT_FAILURE);
}
