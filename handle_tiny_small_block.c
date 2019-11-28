/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tiny_small_block.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:47:28 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/28 16:20:50 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk			*split_chunk(t_chunk *chunk, size_t size)
{
	t_chunk		new;
	int			min_size;

	min_size = (size <= TINY) ? SMALLEST_T : SMALLEST_S;
	if (size == (size_t)chunk->size)
		return (chunk);
	new.size
}

t_block			*get_block_with_free_space(t_block *block, size_t size)
{
	t_block		*new_block;

	new_block = NULL;
	while (block->next)
	{
		if (block->free_size >= size)
			return (block);
		block = block->next;
	}
	if (block->free_size >= size)
		return (block)
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
	int			chunk_size;

	if (!(block_with_free_space = get_block_with_free_space(type_block, size)))
		return (NULL);
	while (1)
	{
		chunk = (t_chunk *)((char *)block_with_free_space + SIZEHEADERBLOCK);
		while (chunk)
		{
			if (chunk->free & FREE && (chunk->size + ))
			{
				free_chunk = split_chunk(chunk);
				return (((char *)free_chunk + SIZEHEADERCHUNK))
			}
			chunk = chunk->next;
		}
	}
}

void			*handle_tiny_small_block(size_t size)
{
	void		*free_chunk;

	if (size <= TINY_BLOCK)
	{
		if (!(g_start_header_block[TINY_BLOCK]))
		{
			if (!(g_start_header_block[TINY_BLOCK] = request_tiny_small_block(TINY_BLOCK)))
				return (NULL);
		}
		free_chunk = find_free_chunk(TINY_BLOCK, size);
	}
	else
	{

	}
}
