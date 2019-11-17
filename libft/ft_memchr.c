/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:30:05 by froussel          #+#    #+#             */
/*   Updated: 2019/10/13 11:47:33 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*psrc;
	size_t			i;

	psrc = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (psrc[i] == ((unsigned char)c))
			return (&psrc[i]);
		i++;
	}
	return (0);
}
