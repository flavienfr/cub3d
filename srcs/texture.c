#include "cub3d.h"

static int  texture_info(t_info *info, t_tex *tex)
{
	t_tex tex;

	printf("path=%s\n", tex->path);
	if (!(tex->ptr = mlx_xpm_file_to_image (info->win_ptr, tex->path, &tex->width, &tex->height)))
		return (-1);
	//if (!(tex->data = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->size_l, &tex->endian)))
	//	return (-1);
	return (1);
}

void        check_textute(t_info *info)
{

	if (check_info_path_file(info, &info->tex[TEX_NO]) < 0)
		error_global("NO", info);
	if (check_info_path_file(info, &info->tex[TEX_SO]) < 0)
		error_global("SO", info);
	if (check_info_path_file(info, &info->tex[TEX_WE]) < 0)
		error_global("WE", info);
	if (check_info_path_file(info, &info->tex[TEX_EA]) < 0)
		error_global("EA", info);
	if (check_info_path_file(info, &info->tex[TEX_S]) < 0)
		error_global("S", info);
}