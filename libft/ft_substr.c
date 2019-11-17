/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:54:32 by froussel          #+#    #+#             */
/*   Updated: 2019/11/01 17:51:34 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ps;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else
		len -= start;
	if (!(ps = malloc(sizeof(*ps) * (len + 1))))
		return (0);
	i = 0;
	while (len-- > 0 && s[start + i])
	{
		ps[i] = s[start + i];
		i++;
	}
	ps[i] = '\0';
	return (ps);
}
