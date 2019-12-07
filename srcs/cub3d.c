/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:41:17 by froussel          #+#    #+#             */
/*   Updated: 2019/12/07 19:06:53 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(t_map *map, float x, float y)
{
	int row;
	int col;

	row = floor(y / TILE_SIZE);
	col = floor(x / TILE_SIZE);
	if (map->map[row][col] == '1')/*|| map->map[row][col] == '2')*/
		return (1);
	return (0);
}

void	set_mini_map(t_info *info, t_mini_map *m_map)
{
	int	ratio_x;
	int ratio_y;
	int diff;

	ratio_x = info->res_x / info->map->map_col;
	ratio_y = info->res_y / info->map->map_row;
	diff = ratio_x - ratio_y;
	m_map->map = ratio_y + (diff / 2);
	m_map->map += (m_map->map % 2) ? 1 : 0;
	m_map->player = m_map->map * 0.3;
	m_map->player = m_map->player < 10 ? 10 : m_map->player;
}

int		loop_cub3d(t_info *info)
{
	player_movement(info->map, &info->player);
	caste_all_ray(info, &info->player);
	generete_wall(info, &info->player);
	/*
	** Minimap render
	*/
	render_map(info, info->map);
	render_player(info, &info->player);
	render_ray(info);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img.img_ptr,
	0, 0);
	return (0);
}

void	window_initialization(t_info *info, t_img *img)
{
	if (!(info->mlx_ptr = mlx_init()))
		error_global(info);
	if (!(info->win_ptr = mlx_new_window(info->mlx_ptr,
		info->res_x, info->res_y, "cub3d")))
		error_global(info);
	img->img_ptr = mlx_new_image(info->mlx_ptr, info->res_x, info->res_y);
	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp,
	&img->size_l, &img->endian);
}

int		main(int ac, char **av)
{
	t_info	*info;

	if (ac < 2 || ac > 3)
		return (-1);
	info = info_initialization();//why pas dans les params
	read_file_info(av[1], (ac == 3 ? av[2] : NULL), info);
	set_mini_map(info, &info->m_map);
	window_initialization(info, &info->img);
	init_player_on_map(info, info->map, &info->player);
	init_textute(info);
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

/*
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
void	test(t_tex *tex)
{
	int y = -1;
	int x;
	while (++y < TEXTURE_HEIGHT)
	{
		x = -1;
		while (++x < TEXTURE_WIDTH)
			texture[x][y] = (int)tex->data[y * TEXTURE_HEIGHT + x];
		//texture[x][y] = (x % 8 && y % 8) ? RED : BLACK; 
		//printf("%d\n", (int)tex->data[5]);
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
}*/
