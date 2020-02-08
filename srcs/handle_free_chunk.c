/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_free_chunk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:56:21 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/08 15:53:14 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"

int			ptr_is_exist_chunk(void *ptr, t_block *block)
{
	t_chunk	*chunk;

	chunk = (t_chunk *)((char *)block + SIZEHEADERBLOCK);
	while (chunk)
	{
		if ((chunk + 1) == ptr)
			return (1);
		chunk = chunk->next;
	}
	return (0);
}

void		handle_free_chunk(void *ptr, t_block *block)
{
	t_chunk	*data_ptr;

	data_ptr = (t_chunk *)((char *)ptr - SIZEHEADERCHUNK);
	if (!ptr_is_exist_chunk(ptr, block))
		return ;
	data_ptr->free |= FREE;
	block->free_size += data_ptr->size;
	handle_defragmentation(data_ptr, block);
}
