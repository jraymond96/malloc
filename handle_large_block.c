/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_large_chunk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:56:25 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/27 21:06:30 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*get_large_block(size_t size)
{
	t_block			*last;

	if (!(last = last_header_block(g_start_header_block[LARGE_BLOCK])))
	{
		g_start_header_block[LARGE_BLOCK] = request_large_block(size);
		return (g_start_header_block[LARGE_BLOCK]);
	}
	last->next = request_large_block(size);
	return (last->next);
}
