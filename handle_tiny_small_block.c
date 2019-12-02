/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tiny_small_block.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:47:28 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/02 16:36:18 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

void			*add_new_chunk(t_chunk *chunk, int size)
{
	t_chunk		new;
	void		*addr_new;

	new.size = chunk->size - (size + SIZEHEADERCHUNK);
	new.free |= FREE;
	new.next = chunk->next;
	new.prev = chunk;

	addr_new = ((char *)chunk + size);
	ft_memcpy(addr_new, &new, SIZEHEADERCHUNK);
	if (chunk->next)
		((t_chunk *)chunk->next)->prev = addr_new;
	chunk->size = size;
	chunk->next = addr_new;

	return (addr_new);
}

t_chunk			*split_chunk(t_chunk *chunk, t_block *block, int size)
{
	int			min_size;

	min_size = (size <= TINY) ? SMALLEST_T : SMALLEST_S;
	if (size == chunk->size)
		return (chunk);
	if (chunk->size >= (size + SIZEHEADERCHUNK + min_size))
	{
		block->free_size -= (size + SIZEHEADERCHUNK);
		chunk->free ^= FREE;
		return (add_new_chunk(chunk, size));
	}
	else
		return (chunk);
}

t_block			*get_block_with_free_space(int type_block, size_t size)
{
	t_block		*new_block;
	t_block		*block;

	new_block = NULL;
	block = g_start_header_block[type_block];
	while (block->next)
	{
		if (block->free_size >= size)
			return (block);
		block = block->next;
	}
	if (block->free_size >= size)
		return (block);
	else
	{
		if (!(new_block = request_tiny_small_block(type_block)))
			return (NULL);
		block->next = new_block;
		return (new_block);
	}
}

void			*find_free_chunk(int type_block, size_t size)
{
	t_block		*block_with_free_space;
	t_chunk		*chunk;
	t_chunk		*free_chunk;
	int			cast_size;

	cast_size = (int)size;
	while (1)
	{
		if (!(block_with_free_space = get_block_with_free_space(type_block, size)))
			return (NULL);
		chunk = (t_chunk *)((char *)block_with_free_space + SIZEHEADERBLOCK);
		while (chunk)
		{
			if (chunk->free & FREE && chunk->size >= cast_size)
			{
				free_chunk = split_chunk(chunk, block_with_free_space, cast_size);
				return (((char *)free_chunk + SIZEHEADERCHUNK));
			}
			chunk = chunk->next;
		}
	}
}

void			*handle_tiny_small_block(size_t size)
{
	int			type_block;

	type_block = (size <= TINY_BLOCK) ? TINY_BLOCK : SMALL_BLOCK;
	if (!(g_start_header_block[type_block]))
	{
		if (!(g_start_header_block[type_block] = request_tiny_small_block(type_block)))
			return (NULL);
	}
	return (find_free_chunk(type_block, size));
}
