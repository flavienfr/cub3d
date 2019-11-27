#include "cub3d.h"

void		clear_buf_rgb(t_info *info, int color)
{
	int x;
	int y;

    y = -1;
	while (++y < info->res_y)
    {
        x = -1;
		while (++x < info->res_x)
            info->buf_rgb[info->res_x * y + x] = color;
    }
}

void		write_buf_rgb(t_info *info)
{
	int x;
	int y;

    y = -1;
	while (++y < info->res_y)
    {
        x = -1;
		while (++x < info->res_x)
            mlx_pixel_put (info->mlx_ptr, info->win_ptr, x , y, info->buf_rgb[info->res_x * y + x]);
    }
}