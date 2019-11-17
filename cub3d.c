/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:41:17 by froussel          #+#    #+#             */
/*   Updated: 2019/11/17 17:45:36 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>//-> strerror
#include <stdio.h>// -> <errno.h>
#include <errno.h>

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

#define WINDOW_X 500
#define WINDOW_Y 500

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}					t_mlx;

typedef struct		s_info
{
	int		resolution_x;
	int		resolution_y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int 	f[3];
	int 	c[3];
}					t_info;

void		error_strerror()
{
	ft_putstr_fd(strerror(errno), 2);
	//printf("strerror et perror \n");
	exit(0);
}

void		error_perror(char *s)
{
	perror(s);
	//printf("strerror et perror \n");
	exit(0);
}

int		key_hook(int key, void *mx)
{
	t_mlx *ptr_mx = (t_mlx *)mx;

	//printf("la touche =%d\n", key);
	if (key == 53)
	{
		mlx_destroy_window(ptr_mx->mlx_ptr, ptr_mx->win_ptr);
		exit(0);
	}
	return (0);
}

t_info	*info_initialization(t_info	*info)
{
	int i;

	i = -1;
	if (!(info = malloc(sizeof(*info))))
		exit(0);
	info->resolution_x = 0;
	info->resolution_y = 0;
	info->no = NULL;
	info->so = NULL;
	info->we = NULL;
	info->ea = NULL;
	info->s = NULL;
	while (++i < 3)
	{
		info->f[i] = -1;
		info->c[i] = -1;
	}
	return (info);
}

char	*read_path(char *line)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (line[i] == ' ')
		i++;
	len = i;
	while (line[len] && line[len] != ' ')
		len++;
	if (!(str = malloc(sizeof(*str))))
		return (NULL);
	str = ft_substr(str, i, len);
	return (str);
}

void	read_resolution(char *line, t_info *info)
{
	int	i;

	i = 0;
	info->resolution_x = ft_atoi(&line[1]);
	while (line[i] == ' ' || line[i] == '\f' || line[i] == '\n'
		|| line[i] == '\r' || line[i] == '\t' || line[i] == '\v')
		i++;
	while (ft_isdigit(line[i]))
		i++;
	info->resolution_y = ft_atoi(&line[i]);
}

void	read_floor_ceiling(char *line, int *tab)
{
	int i;
	int pos;

	i = 0;
	pos = 0;
	tab[pos++] = ft_atoi(line);
	while (line[i] && pos != 3)
	{
		if (line[i] == ',' && line[i + 1])
			tab[pos++] = ft_atoi(&line[i + 1]);
		i++;
	}
}

int		parse_file_info(int fd, t_info *info)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (*line == 'R')
			read_resolution(line, info);
		else if (line[0] == 'N' && line[1] == 'O')
			info->no = read_path(line);
		else if (line[0] == 'S' && line[1] == 'O')
			info->so = read_path(line);
		else if (line[0] == 'W' && line[1] == 'E')
			info->we = read_path(line);
		else if (line[0] == 'E' && line[1] == 'A')
			info->ea = read_path(line);
		else if (line[0] == 'S')
			info->s = read_path(line);
		else if (*line == 'F')
			read_floor_ceiling(line, info->f);
		else if (*line == 'C')
			read_floor_ceiling(line, info->c);
		free(line);
	}
	return (ret);
}

int		parse_file_map(t_info *info)
{
	return (0);
}
int		read_file_info(char *file)
{
	int		fd;
	int		i;
	t_info	*info;

	i = 0;
	info_initialization(info);
	if (!(fd = open(file, O_RDONLY)))
		error_strerror();
	if (parse_file_info(fd, info) == -1)
		error_strerror();
	parse_file_map(info);
	//fonction check error info
	close(fd);
}

int		main(int ac, char **av)
{
	t_mlx mx;

	if (!(mx.mlx_ptr = mlx_init()))
		error_strerror();
	if (!(mx.win_ptr = mlx_new_window(mx.mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d")))
		error_strerror();
	mlx_key_hook(mx.win_ptr, key_hook, (void *)&mx);
	mlx_loop(mx.mlx_ptr);
	return (0);
}
