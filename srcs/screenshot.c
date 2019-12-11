/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 11:16:52 by froussel          #+#    #+#             */
/*   Updated: 2019/12/11 15:14:41 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	int_in_char(unsigned char *str, int value)
{
	int i;

	i = -1;
	while (++i < 4)
		str[i] = (unsigned char)(value >> (i * 8));
}

static int	write_header(t_info *info, int fd, unsigned int fd_size)
{
	unsigned char	header[54];
	int				i;

	i = -1;
	while (++i < 54)
		header[i] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_in_char(header + 2, fd_size);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	int_in_char(header + 18, info->res_x);
	int_in_char(header + 22, -info->res_y);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (write(fd, header, 54));
}

static int	write_data(t_info *info, int fd, unsigned int pad_byte_row)
{
	const unsigned char	zeroes[3] = {0, 0, 0};
	int					y;
	int					x;

	y = -1;
	while (++y < info->res_y)
	{
		x = -1;
		while (++x < info->res_x)
			if (write(fd, &info->img.data[y * info->res_x + x], 3) < 0)
				return (0);
		if (write(fd, &zeroes, pad_byte_row) < 0)
			return (0);
	}
	return (1);
}

void		screen_shot(t_info *info)
{
	int				fd;
	unsigned int	fd_size;
	unsigned int	pxl_byte_row;
	unsigned int	pad_byte_row;

	loop_cub3d(info);
	pxl_byte_row = info->res_x * 3;
	pad_byte_row = (4 - (pxl_byte_row % 4)) % 4;
	fd_size = 54 + (pxl_byte_row + pad_byte_row) * info->res_y;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
		S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
		error_global(info);
	if (write_header(info, fd, fd_size) < 0)
		error_global(info);
	if (!write_data(info, fd, pad_byte_row))
		error_global(info);
	close(fd);
	free_all(info);
}
