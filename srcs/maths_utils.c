#include "cub3d.h"

float	norm_angle(float angle)
{
	angle = remainder(angle, M_PI * 2);//angle % (2 * pi) ?
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