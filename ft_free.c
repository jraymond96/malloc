/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:20:47 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/02 19:41:19 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk		*if_ptr_exist(t_block *block, void *ptr)
{
	t_chunk	*chunk;

	t_chunk = (t_chunk *)(t_block + 1);
	while (chunk)
	{
		if ((chunk + 1) == ptr)
			return ((chunk + 1))
		chunk = chunk->next;
	}

	return (NULL);
}

t_block		*get_block_content_address(void *ptr, int type_block)
{
	int		size_block;
	t_block	*block;

	size_block = (type_block == TINY_BLOCK) ? SIZE_TBLOCK : SIZE_SBLOCK;
	block = g_start_header_block[type_block];
	while (block)
	{
		if (block < ptr && ((char *)block + size_block) > ptr)
			return (block);
		block = block->next;
	}

	return (NULL);
}

t_block		*search_in_tiny_small_blocks(void *ptr)
{
	t_block	*block;

	chunk_to_free = NULL;
	if ((block = get_block_content_address(ptr, TINY_BLOCK)))
		return (if_ptr_exist(block, ptr));
	else
		block = get_block_content_address(ptr, TINY_BLOCK);
	return (if_ptr_exist(block, ptr));
}

t_block		*ptr_is_large_block(void *ptr)
{
	t_block	*block;

	block = g_start_header_block[LARGE_BLOCK];
	while (block)
	{
		if ((block + 1) == ptr)
			return (block)
		block = block->next;
	}

	return (NULL);
}

void		free(void *ptr)
{
	t_chunk	*chunk_to_free;
	t_block	*large_block;

	if (! ptr)
		return;
	if ((large_block = ptr_is_large_block(ptr)))
	{
		if (large_block->prev)
			large_block->prev->next = large_block->next;
		if (large_block->next)
			large_block->next->prev = large_block->prev;
		munmap(large_block, (large_block->free_size + SIZEHEADERBLOCK));
	}
	else
	{
		if ((chunk_to_free = get_block_tiny_small_content_address(ptr)))
		{
			chunk_to_free->free ^= FREE;
		}
	}

	return;
}
