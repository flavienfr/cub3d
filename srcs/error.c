/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <froussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:13:18 by froussel          #+#    #+#             */
/*   Updated: 2019/12/11 16:17:34 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_preso(char *s, t_info *info)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	if (info)
		free_info(info);
	exit(EXIT_FAILURE);
}

void	error_global(t_info *info)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	free_info(info);
	exit(EXIT_FAILURE);
}

void	error_global_close_fd(int fd, t_info *info)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(strerror(errno), 2);
	close(fd);
	free_info(info);
	exit(EXIT_FAILURE);
}
