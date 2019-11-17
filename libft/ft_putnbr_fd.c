/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:19:53 by froussel          #+#    #+#             */
/*   Updated: 2019/10/16 14:47:56 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;

	if (fd <= 0)
		return ;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		un = -n;
	}
	else
		un = n;
	if (un < 10)
		ft_putchar_fd('0' + un, fd);
	else
	{
		ft_putnbr_fd(un / 10, fd);
		ft_putchar_fd('0' + un % 10, fd);
	}
}
