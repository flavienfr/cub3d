/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 12:44:54 by froussel          #+#    #+#             */
/*   Updated: 2019/12/10 19:26:35 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_sprite(t_sprite **begin)
{
	t_sprite	*sp;
	t_sprite	*nxt;

	sp = *begin;
	while (sp)
	{
		nxt = sp->next;
		free(sp);
		sp = nxt;
	}
	*begin = NULL;
}

void	init_sprite(t_info *info, int x, int y)
{
	int			i;
	t_sprite	*sprite;

	i = -1;
	info->num_sprite++;
	if (!(sprite = malloc(sizeof(*sprite))))
		error_global(info);
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
	sprite->texture = TEX_S;
	if (info->sprite)
		sprite->next = info->sprite;
	else
		sprite->next = NULL;
	info->sprite = sprite;
}

static void		sort_sprite(t_sprite **begin)
{
	t_sprite	*sp;
	t_sprite	*bef;
	t_sprite	*nxt;

	if (*begin)
	{
		sp = *begin;
		bef = 0;
		while (sp->next)
		{
			nxt = sp->next;
			if (sp->dist < nxt->dist)
			{
				sp->next = nxt->next;
				nxt->next = sp;
				if (bef)
					bef->next = nxt;
				else
					*begin = nxt;
				sp = *begin;
			}
			bef = sp;
			sp = sp->next;
		}
	}
}

void	render_sprite_2(t_info *info, t_sprite *sprite, int spt_size, int x_ofst, int y_ofst)
{
	int color;
	int i;
	int j;

	i = -1;
	while (++i < spt_size /*&& i < info->res_x*/)
	{
        if (x_ofst + i < 0 || x_ofst + i > info->res_x)
			continue ;
        if (info->ray[x_ofst + i].dist <= sprite->dist)
			continue ;
		j = -1;
		while (++j < spt_size /*&& j < info->res_y*/)
		{
            if (y_ofst + j < 0 || y_ofst + j >= info->res_y)
				continue ;
			color = info->tex[TEX_S].tex[i * TEXTURE_SIZE / spt_size]
			[j * TEXTURE_SIZE / spt_size];
			if (color != 0)
				info->img.data[(y_ofst + j) * info->res_x +
				(info->res_x + x_ofst + i)] = color;
        }
    }
}

void	render_sprite(t_info *info, t_sprite *sprite, t_player * player)
{
	int spt_size;
	int x_ofst;
	int y_ofst;
	
    float sprite_dir = atan2(sprite->y - player->y, sprite->x - player->x);
    while (sprite_dir - player->rotate_angle >  M_PI)
		sprite_dir -= 2 * M_PI;
    while (sprite_dir - player->rotate_angle < -M_PI)
		sprite_dir += 2 * M_PI;
	if (info->res_y > info->res_x)
    	spt_size = info->res_y / sprite->dist;
	else
		spt_size = info->res_x / sprite->dist;
	//if (spt_size > 1000 ) 
	//	spt_size = 1000;
    x_ofst = (sprite_dir - player->rotate_angle) * info->res_x / info->fov +
	(info->res_x / 2 - spt_size / 2);
    y_ofst = info->res_y / 2 - spt_size / 2;
	render_sprite_2(info, sprite, spt_size, x_ofst, y_ofst);
}

void	generete_sprite(t_info *info, t_player * player)
{
	t_sprite *cur;

	cur = info->sprite;
	while (cur)
	{
		cur->dist = dist_point(player->x, player->y, cur->x, cur->y);
		cur = cur->next;
	}
	sort_sprite(&info->sprite);
	cur = info->sprite;
	while (cur)
	{
		render_sprite(info, cur, player);
		cur = cur->next;
	}
}


/*void	generete_sprite(t_info *info, t_sprite *sprite, t_player * player)
{
	int i;

	i = -1;
	while (++i < NUM_SPRITE)
		sprite[i].dist = dist_point(player->x, player->y,
		sprite->x, sprite->y);
	//lst_sort(sprite);
	i = -1;
	while (++i < NUM_SPRITE)
	{
		//translate sprite position to relative to camera
		//sprite[i].x -= player->x;
		//sprite[i].y -= player->y;
		//transformX = sprite[i].x;
		//transformY = sprite[i].y;
		int spriteScreenX = (info->res_x / 2) * (1 + sprite[i].x / sprite[i].y);

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(info->res_y / sprite[i].y));
		int drawStartY = -spriteHeight / 2 + info->res_y / 2;
      	if(drawStartY < 0)
			drawStartY = 0;
      	int drawEndY = spriteHeight / 2 + info->res_y / 2;
      	if(drawEndY >= info->res_y)
			drawEndY = info->res_y - 1;

		//calculate width of the sprite
      	int spriteWidth = abs((int)(info->res_y / sprite[i].y));
      	int drawStartX = -spriteWidth / 2 + spriteScreenX;
      	if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= info->res_x)
			drawEndX = info->res_x - 1;
		//render sprite
		int stripe = drawStartX;
		printf("stripe=%d drawEndX=%d\n", stripe, drawEndX);
		while (stripe < drawEndX)
		{		
			int texX = (256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXTURE_SIZE / spriteWidth) / 256;
			
			if(sprite[i].y > 0 && stripe > 0 && stripe < info->res_x && sprite[i].y < sprite[stripe].dist)
        	for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        	{
         		int d = (y) * 256 - info->res_y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
        		int texY = ((d * TEXTURE_SIZE) / spriteHeight) / 256;
				int color = info->tex[TEX_S].tex[texX][texY];
				printf("color=%d\n", color);
        		if(color != 0)
					info->img.data[y * info->res_x + stripe] = color;
        	}
			stripe++;
		}
	}
}*/
