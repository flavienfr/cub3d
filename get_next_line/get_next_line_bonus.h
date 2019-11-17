/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:25:13 by froussel          #+#    #+#             */
/*   Updated: 2019/10/30 11:26:38 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "stdlib.h"
# include "unistd.h"

int			get_next_line(int fd, char **line);
size_t		ft_strclen(const char *s, char c);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *str1, char const *str2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);

#endif
