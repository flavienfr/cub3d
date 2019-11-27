#include "cub3d.h"
/*
void    render_wall(t_info *info, int x, int bot, int top)
{
    int y;

    y = top;
    while (y < bot)
    {
        info->buf_rgb[info->res_x * y + x] = GREEN;
        y++;
    }
}*/

void    render_wall(t_info *info, int x, int bot, int top)
{
    while (top < bot)
    {
        mlx_pixel_put (info->mlx_ptr, info->win_ptr, x, top, GREEN);
        top++;
    }
}

void    generete_wall(t_info *info, t_player *player)
{
    int i;
    int top_pix;
    int bot_pix;
    int stip_height;
    float per_dist;

    i = -1;
    while (++i < info->res_x)
    {
        per_dist = ray[i].dist * cos(ray[i].angle - player->rotate_angle);
        stip_height = (TILE_SIZE / per_dist) * ((info->res_x / 2) / (tan(FOV / 2)));
        top_pix = (info->res_y / 2) - (stip_height / 2);
        top_pix = (top_pix < 0) ? 0 : top_pix;

        bot_pix = (info->res_y / 2) + (stip_height / 2);
        bot_pix = (bot_pix > info->res_y) ? info->res_y : bot_pix;
        //printf("%d, %d");
        render_wall(info, i, bot_pix, top_pix);
    }
}