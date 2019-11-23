/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:13:18 by froussel          #+#    #+#             */
/*   Updated: 2019/11/21 11:37:39 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_read_file_info(int fd, t_info *info)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	info_free(info);
	close(fd);
	exit(0);
}
void	error_global(char *s, t_info *info)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	info_free(info);
	exit(0);
}
void	error_strerror(t_info *info)
{
	ft_putstr_fd(strerror(errno), 2);
	info_free(info);
	exit(0);
}
