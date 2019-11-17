/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:28:37 by froussel          #+#    #+#             */
/*   Updated: 2019/10/12 12:48:43 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(long int n)
{
	int len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	else if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	long int	i;
	long int	nn;
	char		*s;

	nn = n;
	i = len(nn);
	if (!(s = ft_calloc(i + 1, sizeof(*s))))
		return (0);
	i--;
	if (nn == 0)
		s[0] = '0';
	if (nn < 0)
	{
		s[0] = '-';
		nn *= -1;
	}
	while (nn > 0)
	{
		s[i] = (nn % 10) + 48;
		nn = nn / 10;
		i--;
	}
	return (s);
}
