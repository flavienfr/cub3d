/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: froussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:41:24 by froussel          #+#    #+#             */
/*   Updated: 2019/10/16 14:58:35 by froussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*surf;

	if (!new || !*alst || !alst)
	{
		if (!*alst)
			*alst = new;
		return ;
	}
	surf = *alst;
	while (surf->next)
		surf = surf->next;
	surf->next = new;
}
