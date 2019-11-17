/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:39:53 by froussel          #+#    #+#             */
/*   Updated: 2019/10/13 10:54:50 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	char		*fs;
	size_t		i;
	size_t		len;

	if (!s || !f)
		return (0);
	i = 0;
	len = ft_strlen(s);
	if (!(fs = ft_calloc(len + 1, sizeof(*fs))))
		return (0);
	while (i < len)
	{
		fs[i] = (*f)(i, s[i]);
		i++;
	}
	return (fs);
}
