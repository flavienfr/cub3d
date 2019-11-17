/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:04:25 by froussel          #+#    #+#             */
/*   Updated: 2019/10/16 15:17:16 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_separator(char c, char const *charset)
{
	size_t	i;

	if (!charset)
		return (0);
	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*full_set(void)
{
	char	*new;

	if (!(new = ft_calloc(1, sizeof(*new))))
		return (NULL);
	return (new);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*new;
	size_t	len;
	size_t	i;

	if (!s1)
		return (0);
	i = 0;
	len = ft_strlen(s1);
	start = (char *)s1;
	end = (char *)&s1[len - 1];
	while (ft_check_separator(*start, set))
		start++;
	if (*start == '\0')
		return (full_set());
	while (ft_check_separator(*end, set))
		end--;
	len = end - start + 1;
	if (!(new = ft_calloc(len + 1, sizeof(*new))))
		return (NULL);
	while (len--)
		new[i++] = *start++;
	return (new);
}
