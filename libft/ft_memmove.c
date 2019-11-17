/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:28:18 by froussel          #+#    #+#             */
/*   Updated: 2019/10/16 14:51:30 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;
	size_t			i;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	i = 0;
	if (psrc < pdst)
		while (len-- > 0)
			pdst[len] = psrc[len];
	else
		while (i < len)
		{
			pdst[i] = psrc[i];
			i++;
		}
	return (dst);
}
