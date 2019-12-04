/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:20:47 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/04 15:00:14 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "malloc.h"
#include "./libft/libft.h"

void		handle_defragmentation(t_chunk *chunk_free)
{
	int		new_size;
	t_chunk	*chunk_h;

	new_size = 0;
	chunk_h = chunk_free;
	if ((chunk_h->prev && (((t_chunk *)chunk_h->prev)->free & FREE)) &&
			(chunk_h->next && (((t_chunk *)chunk_h->next)->free & FREE)))
	{
			new_size = (chunk_h->size + SIZEHEADERCHUNK) + (((t_chunk *)chunk_h->next)->size + SIZEHEADERCHUNK);
			((t_chunk *)chunk_h->prev)->size += new_size;
			((t_chunk *)chunk_h->prev)->next = chunk_h->next;
	}
	else if (chunk_h->prev && (((t_chunk *)chunk_h->prev)->free & FREE))
	{
		((t_chunk *)chunk_h->prev)->size += chunk_h->size + SIZEHEADERCHUNK;
		((t_chunk *)chunk_h->prev)->next = chunk_h->next;
	}
	else if (chunk_h->next && (((t_chunk *)chunk_h->next)->free & FREE))
	{
		chunk_h->size += ((t_chunk *)chunk_h->next)->size + SIZEHEADERCHUNK;
		chunk_h->next = ((t_chunk *)chunk_h->next)->next;
	}

	return;
}

t_chunk		*if_ptr_exist(t_block *block, void *ptr)
{
	t_chunk	*chunk;

	if (! block)
	{
		ft_putstr("ptr_exist NULL\n");
		return (NULL);
	}
	ft_putstr("ptr_exist\n");
	chunk = (t_chunk *)(block + 1);
	ft_putstr("ptr_exist 1\n");
	while (chunk)
	{
		ft_putstr("ptr_exist BEFORE\n");
		if ((chunk + 1) == ptr)
		{
			ft_putstr("ptr_exist IF\n");
			block->free_size += chunk->size;
			return (chunk);
		}
		ft_putstr("ptr_exist AFTER\n");
		chunk = chunk->next;
	}
	ft_putstr("ptr_exist END\n");
	return (NULL);
}

t_block		*get_block_content_address(void *ptr, int type_block)
{
	int		size_block;
	t_block	*block;

	ft_putstr("block_content\n");
	size_block = (type_block == TINY_BLOCK) ? REALSIZE_TBLOCK : REALSIZE_SBLOCK;
	block = g_start_header_block[type_block];
	ft_putstr("block_content 1\n");
	while (block)
	{
		if ((void *)block < ptr && (void *)((char *)block + size_block) > ptr)
			return (block);
		block = block->next;
	}

	ft_putstr("block_content 3\n");
	return (NULL);
}

t_chunk		*search_in_tiny_small_blocks(void *ptr)
{
	t_block	*block;

	if ((block = get_block_content_address(ptr, TINY_BLOCK)))
	{
		ft_putstr("search if\n");
		return (if_ptr_exist(block, ptr));
	}
	else
	{
		ft_putstr("search else\n");
		block = get_block_content_address(ptr, SMALL_BLOCK);
		ft_putstr("search else 1\n");
	}
	return (if_ptr_exist(block, ptr));
}

t_block		*ptr_is_large_block(void *ptr)
{
	t_block	*block;

	block = g_start_header_block[LARGE_BLOCK];
	while (block)
	{
		ft_putstr("before\n");
		if ((block + 1) == ptr)
		{
			ft_putstr("in if\n");
			return (block);
		}
		ft_putstr("after\n");
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
		ft_putstr("free large\n");
		if (large_block->prev)
			((t_block *)large_block->prev)->next = large_block->next;
		else
			g_start_header_block[LARGE_BLOCK] = large_block->next;
		if (large_block->next)
			((t_block *)large_block->next)->prev = large_block->prev;
		munmap(large_block, (large_block->free_size + SIZEHEADERBLOCK));
	}
	else
	{
		if ((chunk_to_free = search_in_tiny_small_blocks(ptr)))
		{
			ft_putstr("free_tiny_small exist\n");
			chunk_to_free->free |= FREE;
			ft_putstr("free_tiny_small exist 1\n");
			handle_defragmentation(chunk_to_free);
			ft_putstr("free_tiny_small exist 2\n");
		}
	}
	ft_putstr("free ret\n");
	return;
}
