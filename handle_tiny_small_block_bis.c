/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tiny_small_block_bis.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:15:31 by jraymond          #+#    #+#             */
/*   Updated: 2020/01/27 11:24:25 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft/libft.h"

void			init_newchunk_update_freechunk(t_chunk *new, int size, t_chunk *free_chunk)
{
	new->size = free_chunk->size - size - SIZEHEADERCHUNK;
	new->free = 1;
	new->prev = free_chunk;
	new->next = free_chunk->next;

	free_chunk->size = size;
	free_chunk->free ^= FREE;
	free_chunk->next = (void *)((char *)free_chunk + SIZEHEADERCHUNK + size);
}

t_chunk			*browse_chunk(t_block *block, int size)
{
	t_chunk		*chunk;

	chunk = (t_chunk *)((char *)block + SIZEHEADERBLOCK);
	while (chunk)
	{
		if ((chunk->free & FREE) && chunk->size >= size)
			return (chunk);
		chunk = chunk->next;
	}

	return (NULL);
}

t_chunk			*find_free_chunk(int type_block, int size, t_block **block_with_freechunk)
{
	t_chunk		*chunk;
	t_block		*block;
	t_block		*last_block;
	t_block		*new_block;

	block = g_start_header_block[type_block];
	new_block = NULL;
	while (block)
	{
		if (block->free_size > size && (chunk = browse_chunk(block, size)))
		{
			ft_putendl("----- FREE CHUNK -----");
			ft_putnbr(chunk->size);
			ft_putchar('\n');
			ft_putnbr(chunk->free);
			ft_putendl("\n----- FREE CHUNK END -----");
			*block_with_freechunk = block;
			return (chunk);
		}
		if (!block->next)
			last_block = block;
		block = block->next;
	}
	new_block = request_tiny_small_block(type_block);
	*block_with_freechunk = new_block;
	last_block->next = new_block;
	return ((t_chunk *)((char *)new_block + SIZEHEADERBLOCK));
}

t_chunk			*get_chunk(int type_block, int size)
{
	t_chunk		*free_chunk;
	t_chunk		new_chunk;
	t_block		*block_contains_freechunk;
	void		*new_addr;

//	ft_putstr("TOTO 1\n");
	block_contains_freechunk = NULL;
	free_chunk = find_free_chunk(type_block, size, &block_contains_freechunk);
//	ft_putstr("TOTO 2\n");
	if (free_chunk->size == size)
	{
		ft_putstr("TOTO if\n");
		block_contains_freechunk->free_size -= free_chunk->size;
		return (free_chunk + 1);
	}
	else
	{

		ft_putstr("TOTO 3\n");
		if (free_chunk->size >= size + SIZEHEADERCHUNK + ((type_block == 0) ? SMALLEST_T : SMALLEST_S))
		{
			ft_putstr("TOTO 4\n");
			init_newchunk_update_freechunk(&new_chunk, size, free_chunk);
//			ft_putstr("TOTO 5\n");
			new_addr = (void *)((char *)free_chunk + SIZEHEADERCHUNK + size);
			ft_memcpy(new_addr, &new_chunk, SIZEHEADERCHUNK);
//			ft_putstr("TOTO 6\n");
			if (free_chunk->next)
				((t_chunk *)free_chunk->next)->prev = new_addr;
		}
//		ft_putstr("TOTO 7\n");
		block_contains_freechunk->free_size -= free_chunk->size;
	}

	return (free_chunk + 1);
}

void			*handle_tiny_small_block(size_t size)
{
	int			type_block;
	int			cast_size;
	void		*free_chunk;

	cast_size = (int)size;
	type_block = (size <= TINY) ? TINY_BLOCK : SMALL_BLOCK;
	show_alloc_mem();
	if (!(g_start_header_block[type_block]))
	{
		if (!(g_start_header_block[type_block] = request_tiny_small_block(type_block)))
			return (NULL);
	}

	return ((void *)get_chunk(type_block, size));
}
