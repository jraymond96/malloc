/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:20:47 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/03 18:40:45 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "malloc.h"
#include "./libft/libft.h"

void		handle_defragmentation(t_chunk *chunk_free)
{
	int		new_size;

	new_size = 0;
	if ((chunk_free->prev && (((t_chunk *)chunk_free->prev)->free & FREE)) ||
			(chunk_free->next && (((t_chunk *)chunk_free->next)->free & FREE)))
	{
		if ((((t_chunk *)chunk_free->prev)->free & FREE)
				&& (((t_chunk *)chunk_free->next)->free & FREE))
		{
			new_size = (chunk_free->size + SIZEHEADERCHUNK) + (chunk_free->size + SIZEHEADERCHUNK);
			((t_chunk *)chunk_free->prev)->size += new_size;
			((t_chunk *)chunk_free->prev)->next = ((t_chunk *)chunk_free->next)->next;
		}
	}
	else if (chunk_free->prev && (((t_chunk *)chunk_free->prev)->free & FREE))
	{
		((t_chunk *)chunk_free->prev)->size += chunk_free->size + SIZEHEADERCHUNK;
		((t_chunk *)chunk_free->prev)->next = chunk_free->next;
	}
	else if (chunk_free->next && (((t_chunk *)chunk_free->next)->free & FREE))
	{
		chunk_free->size += ((t_chunk *)chunk_free->next)->size + SIZEHEADERCHUNK;
		chunk_free->next = ((t_chunk *)chunk_free->next)->next;
	}

	return;
}

t_chunk		*if_ptr_exist(t_block *block, void *ptr)
{
	t_chunk	*chunk;

	if (! block)
		return (NULL);
	chunk = (t_chunk *)(block + 1);
	while (chunk)
	{
		if ((chunk + 1) == ptr)
			return ((chunk + 1));
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
		if ((void *)block < ptr && (void *)((char *)block + size_block) > ptr)
			return (block);
		block = block->next;
	}

	return (NULL);
}

t_chunk		*search_in_tiny_small_blocks(void *ptr)
{
	t_block	*block;

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
			return (block);
		block = block->next;
	}

	return (NULL);
}

void		free(void *ptr)
{
	t_chunk	*chunk_to_free;
	t_block	*large_block;

	ft_putstr("free\n");
	if (! ptr)
	{
		ft_putstr("free ret\n");
		return;
	}
	if ((large_block = ptr_is_large_block(ptr)))
	{
		if (large_block->prev)
			((t_block *)large_block->prev)->next = large_block->next;
		if (large_block->next)
			((t_block *)large_block->next)->prev = large_block->prev;
		munmap(large_block, (large_block->free_size + SIZEHEADERBLOCK));
	}
	else
	{
		if ((chunk_to_free = search_in_tiny_small_blocks(ptr)))
		{
			chunk_to_free->free |= FREE;
			handle_defragmentation(chunk_to_free);
		}
	}

	ft_putstr("free ret\n");
	return;
}
