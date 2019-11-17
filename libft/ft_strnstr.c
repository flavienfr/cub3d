/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:51:09 by froussel          #+#    #+#             */
/*   Updated: 2019/10/17 10:43:15 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	if (!*to_find)
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = i;
		x = 0;
		while (str[j] == to_find[x] && j < len)
		{
			if (to_find[x + 1] == '\0')
				return ((char *)&str[i]);
			j++;
			x++;
		}
		i++;
	}
	return (0);
}
