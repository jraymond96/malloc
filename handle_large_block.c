/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_large_chunk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:56:25 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/05 21:04:20 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*get_large_block(size_t size)
{
	t_block			*last;
	void			*new;

	new = request_large_block(size);
	if (!(last = last_header_block(g_start_header_block[LARGE_BLOCK])))
		g_start_header_block[LARGE_BLOCK] = (t_block *)new;
	else
		last->next = (t_block *)new;
	return ((void *)((char *)new + SIZEHEADERBLOCK));
}
