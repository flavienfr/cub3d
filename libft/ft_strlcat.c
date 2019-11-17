/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:41:03 by froussel          #+#    #+#             */
/*   Updated: 2019/10/15 10:37:16 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	j = 0;
	x = 0;
	while (src[i])
		i++;
	while (dst[j] && j < dstsize)
		j++;
	if (dstsize <= j)
		i += dstsize;
	else
		i += j;
	while (src[x] && j + 1 < dstsize)
	{
		dst[j] = src[x];
		j++;
		x++;
	}
	if (j < dstsize)
		dst[j] = '\0';
	return (i);
}
