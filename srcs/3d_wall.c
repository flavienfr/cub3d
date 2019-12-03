#include "cub3d.h"

void    render_wall(t_info *info, int x, int bot, int top)
{
    int texture_x;
    int texture_y;
    int y;

    y = top;
    if (ray[x].is_vert)
        texture_x = (int)ray[x].wall_y % TEXTURE_HEIGHT;
    else
        texture_x = (int)ray[x].wall_x % TEXTURE_WIDTH;
    while (y < bot)
    {
        texture_y = (y + (ray[x].stip_height / 2) - (info->res_y / 2)) * ((float)TEXTURE_HEIGHT / ray[x].stip_height);
        info->img.data[y * info->res_x + x] = texture[texture_x][texture_y];
        y++;
    }
}

void    render_ceiling(t_info *info, int x, int top)
{
    while (top > 0)
    {
        info->img.data[top * info->res_x + x] = info->c;
        //info->buf_rgb[x][top] = info->c;
        top--;
    }
}

void    render_floor(t_info *info, int x, int bot)
{
    while (bot < info->res_y)
    {
        info->img.data[bot * info->res_x + x] = info->f;
        //info->buf_rgb[x][bot] = info->f;
        bot++;
    }
}

void    generete_wall(t_info *info, t_player *player)
{
    int i;
    int top_pix;
    int bot_pix;
    float per_dist;

    i = -1;
    while (++i < info->res_x)
    {
        per_dist = ray[i].dist * cos(ray[i].angle - player->rotate_angle);
        ray[i].stip_height = (TILE_SIZE / per_dist) * ((info->res_x / 2) / (tan(FOV / 2)));
        top_pix = (info->res_y / 2) - (ray[i].stip_height / 2);
        top_pix = (top_pix < 0) ? 0 : top_pix;

        bot_pix = (info->res_y / 2) + (ray[i].stip_height / 2);
        bot_pix = (bot_pix > info->res_y) ? info->res_y : bot_pix;

        render_ceiling(info, i, top_pix);
        render_floor(info, i, bot_pix);
        render_wall(info, i, bot_pix, top_pix);
    }
}