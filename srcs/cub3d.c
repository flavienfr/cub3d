/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:41:17 by froussel          #+#    #+#             */
/*   Updated: 2019/12/04 16:34:50 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(t_map *map, float x, float y)
{
	int row;
	int col;

	row = floor(y / TILE_SIZE);
	col = floor(x / TILE_SIZE);
	if (map->map[row][col] == '1')/*|| map->./map[x / TILE_SIZE][y / TILE_SIZE] == '2'*/
		return (1);
	return (0);
}

void	print_rect42(t_info *info)
{
	int h;
	int w;

	h = 100;
	while (h < 200+ 100 )
	{
		w = 100;
		while (w < 500 + 100)
		{
			info->img.data[h * info->res_x + w] = BLUE;
			w++;
		}
		h++;
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img.img_ptr, 0, 0);
}

int 	loop_cub3d(t_info *info)
{	
	player_movement(info->map, &info->player);
    caste_all_ray(info, &info->player);
	generete_wall(info, &info->player);

	render_map(info, info->map);
	render_player(info, &info->player);
	render_ray(info);

	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img.img_ptr, 0, 0);
	return (0);
}

void	test()
{
	int y = -1;
	int x;
	while (++y < TEXTURE_HEIGHT)
	{
		x = -1;
		while (++x < TEXTURE_WIDTH)
			texture[x][y] = (x % 8 && y % 8) ? RED : BLACK; 
	}
}


void	test2(t_info *info, t_img *img)
{
	int h;
	int w;

	//img->img_ptr =mlx_new_image (info->mlx_ptr, info->res_x, info->res_y);
	//img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian);
	h = -1;
	while (++h < info->res_y)
	{
		w = -1;
		while (++w < info->res_x)
		{
			img->data[h * info->res_x + w] = YELLOW;
		}
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, img->img_ptr, 0, 0);

	//mlx_xpm_file_to_image (info->mlx_ptr, char *filename, int *width, int *height );
}

void	window_initialization(t_info *info, t_img *img)
{
	if (!(info->mlx_ptr = mlx_init()))
		error_strerror(info);
	if (!(info->win_ptr = mlx_new_window(info->mlx_ptr,
		info->res_x, info->res_y, "cub3d")))
		error_strerror(info);
	img->img_ptr = mlx_new_image (info->mlx_ptr, info->res_x, info->res_y);
	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_l, &img->endian);
}
int		main(int ac, char **av)
{
	t_info	*info;

	if (ac < 2 || ac > 3)
		return (-1);
	info = info_initialization();//why pas dans les params
	read_file_info(av[1], (ac == 3 ? av[2] : NULL), info);
	window_initialization(info, &info->img);
	init_player_on_map(info, info->map, &info->player);
	init_textute(info);

	test();
	//test2(info, &info->img);
	print_rect42(info);

	
	keys_set(info);
	mlx_loop_hook(info->mlx_ptr, loop_cub3d, info);
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
// other
/*void	update(t_info *info)
{
	float delta_time;
	time_t seconds;
    seconds = time (NULL);

	while (seconds < info->last_frame / FPS)
		seconds = time (NULL);
	delta_time = (seconds - info->last_frame);
	info->last_frame = seconds;

	//move_player(delta_time);
	//caste_all_ray()
}*/