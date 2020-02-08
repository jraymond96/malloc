/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_chunk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:12:37 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/08 17:12:35 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"
#include "../libft/libft.h"

void		init_and_update(t_chunk *new, int size, t_chunk *free_chunk)
{
	void	*next;

	next = NULL;
	new->size = free_chunk->size - size - SIZEHEADERCHUNK;
	new->free = 1;
	new->prev = free_chunk;
	new->next = free_chunk->next;
	if (new->next)
	{
		next = (void *)((char *)free_chunk + SIZEHEADERCHUNK + size);
		((t_chunk *)new->next)->prev = next;
	}
	free_chunk->size = size;
	free_chunk->free ^= FREE;
	free_chunk->next = (void *)((char *)free_chunk + SIZEHEADERCHUNK + size);
}

t_chunk		*browse_chunk(t_block *block, int size)
{
	t_chunk	*chunk;

	chunk = (t_chunk *)((char *)block + SIZEHEADERBLOCK);
	while (chunk)
	{
		if ((chunk->free & FREE) && chunk->size >= size)
			return (chunk);
		chunk = chunk->next;
	}
	return (NULL);
}

t_chunk		*find_free_chunk(int type_block, size_t size, t_block **blockfreechunk)
{
	t_chunk	*chunk;
	t_block	*block;
	t_block	*last_block;
	t_block	*new_block;

	block = g_header_block[type_block];
	new_block = NULL;
	while (block)
	{
		if (block->free_size > size && (chunk = browse_chunk(block, size)))
		{
			*blockfreechunk = block;
			return (chunk);
		}
		if (!block->next)
			last_block = block;
		block = block->next;
	}
	new_block = request_tiny_small_block(type_block);
	*blockfreechunk = new_block;
	last_block->next = new_block;
	return ((t_chunk *)((char *)new_block + SIZEHEADERBLOCK));
}

void		split_chunk(int t, t_chunk *free_chunk, t_block *block, int size)
{
	t_chunk	new_chunk;
	void	*new_addr;
	int		littlest_size;

	littlest_size = (t == 0) ? SMALLEST_T : SMALLEST_S;
	if (free_chunk->size >= size + SIZEHEADERCHUNK + littlest_size)
	{
		init_and_update(&new_chunk, size, free_chunk);
		new_addr = (void *)((char *)free_chunk + SIZEHEADERCHUNK + size);
		ft_memcpy(new_addr, &new_chunk, SIZEHEADERCHUNK);
		block->free_size -= SIZEHEADERCHUNK;
	}
	else
		free_chunk->free ^= FREE;
	block->free_size -= free_chunk->size;
}

t_chunk		*get_chunk(int type_block, int size)
{
	t_chunk	*free_chunk;
	t_block	*block_contains_freechunk;

	block_contains_freechunk = NULL;
	free_chunk = find_free_chunk(type_block, (size_t)size, &block_contains_freechunk);
	if (free_chunk->size == size)
	{
		block_contains_freechunk->free_size -= free_chunk->size;
		free_chunk->free ^= FREE;
		return (free_chunk + 1);
	}
	else
		split_chunk(type_block, free_chunk, block_contains_freechunk, size);
	return (free_chunk + 1);
}
