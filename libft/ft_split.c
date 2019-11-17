/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:23:10 by froussel          #+#    #+#             */
/*   Updated: 2019/10/11 18:08:27 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_len_word(char const *str, char c, int pos)
{
	int i;
	int glight;
	int word;
	int len_word;

	i = 0;
	word = 0;
	len_word = 0;
	glight = 1;
	while (str[i])
	{
		if (str[i] != c && str[i] && glight == 1)
		{
			glight = 0;
			word++;
		}
		else if (str[i] == c)
			glight = 1;
		if (word == pos && str[i] != c && str[i])
			len_word++;
		i++;
	}
	if (pos == -1)
		return (word);
	return (len_word);
}

static int	ft_pos(char const *str, char c, int idx_word)
{
	int i;
	int glight;
	int word;

	i = 0;
	word = 0;
	glight = 1;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i] && glight == 1)
		{
			glight = 0;
			word++;
		}
		else if (str[i] == c)
			glight = 1;
		if (word == idx_word)
			break ;
		i++;
	}
	return (i);
}

static char	*ft_write(char const *str, char c, int idx_word)
{
	char	*tab;
	int		i;
	int		j;
	int		len;

	idx_word++;
	len = ft_count_len_word(str, c, idx_word);
	tab = (char*)malloc(sizeof(char) * (len + 1));
	i = 0;
	j = ft_pos(str, c, idx_word);
	while (i < len)
	{
		tab[i] = str[j];
		i++;
		j++;
	}
	tab[i] = '\0';
	return (tab);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	char	**tab;
	int		nb_word;

	if (!s)
		return (0);
	nb_word = ft_count_len_word(s, c, -1);
	if (!(tab = (char **)malloc(sizeof(char*) * (nb_word + 1))))
		return (0);
	i = -1;
	while (++i < nb_word)
		tab[i] = ft_write(s, c, i);
	tab[i] = 0;
	return (tab);
}
