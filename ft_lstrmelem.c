/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrmelem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:54:36 by jraymond          #+#    #+#             */
/*   Updated: 2018/06/08 17:14:28 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstrmelem(t_list *begin_list, t_list *elem)
{
	t_list	*el;
	t_list	*next;

	el = begin_list;
	if (!begin_list || !elem)
		return (NULL);
	if (elem == begin_list)
	{
		elem = elem->next;
		free(begin_list);
		return (elem);
	}
	while (el->next != elem && el)
		el = el->next;
	if (!el)
		return (NULL);
	next = elem->next;
	free(elem);
	el->next = next;
	return (begin_list);
}
