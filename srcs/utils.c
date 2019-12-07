/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:22:14 by froussel          #+#    #+#             */
/*   Updated: 2019/12/07 19:30:57 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		first_in_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

/*
** Maths
*/

float	norm_angle(float angle)
{
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle += M_PI * 2;
	return (angle);
}

float	dist_point(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	deg_to_rad(float deg)
{
	return (deg * (M_PI / 180));
}

float	rad_to_deg(float rad)
{
	return (rad * (M_PI / 180));
}
