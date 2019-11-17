/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:09:39 by froussel          #+#    #+#             */
/*   Updated: 2019/10/16 14:33:59 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ps;

	i = 0;
	while (s1[i])
		i++;
	if (!(ps = malloc(sizeof(*ps) * (i + 1))))
		return (0);
	i = 0;
	while (s1[i])
	{
		ps[i] = s1[i];
		i++;
	}
	ps[i] = '\0';
	return (ps);
}
