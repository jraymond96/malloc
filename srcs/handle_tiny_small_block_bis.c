/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tiny_small_block_bis.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:15:31 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/08 17:09:43 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"

void			*handle_tiny_small_block(size_t size)
{
	int			typeblock;
	int			cast_size;

	cast_size = (int)size;
	typeblock = (size <= TINY) ? TINY_BLOCK : SMALL_BLOCK;
	if (!(g_header_block[typeblock]))
	{
		if (!(g_header_block[typeblock] = request_tiny_small_block(typeblock)))
			return (NULL);
	}
	return ((void *)get_chunk(typeblock, size));
}
