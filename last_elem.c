/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:37:17 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/27 20:57:32 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*last_header_block(t_block *begin)
{
	if (!begin)
		return (NULL);
	while (begin->next)
		begin = begin->next;
	return (begin);
}

t_chunk	*last_header_chunk(t_chunk *begin)
{
	if (!begin)
		return (NULL);
	while (begin->next)
		begin = begin->next;
	return (begin);
}
