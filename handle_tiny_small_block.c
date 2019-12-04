/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tiny_small_block.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:47:28 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/04 15:00:16 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft/libft.h"

void			*add_new_chunk(t_chunk *chunk, int size)
{
	t_chunk		new;
	void		*addr_new;

	new.size = chunk->size - (size + SIZEHEADERCHUNK);
	new.free |= FREE;
	new.next = chunk->next;
	new.prev = chunk;

//	ft_putstr("add 1\n");
	addr_new = ((char *)chunk + (size + SIZEHEADERCHUNK));
	ft_memcpy(addr_new, &new, SIZEHEADERCHUNK);
//	ft_putstr("add 2\n");
	if (chunk->next)
		((t_chunk *)chunk->next)->prev = addr_new;
//	ft_putstr("add 3\n");
	chunk->size = size;
	chunk->next = addr_new;

	return (addr_new);
}

t_chunk			*split_chunk(t_chunk *chunk, t_block *block, int size)
{
	int			min_size;
	t_chunk		*ret;

	min_size = (size <= TINY) ? SMALLEST_T : SMALLEST_S;
	if (size == chunk->size || chunk->size < (size + SIZEHEADERCHUNK + min_size))
	{
		block->free_size -= chunk->size;
		chunk->free ^= FREE;
		ret = chunk;
	}
	else
	{
		block->free_size -= (size + SIZEHEADERCHUNK);
		chunk->free ^= FREE;
		ret = add_new_chunk(chunk, size);
	}
	
	return (ret);
}

t_block			*get_block_with_free_space(t_block *last_ret, int type_block, size_t size)
{
	t_block		*new_block;
	t_block		*block;
	t_block		*tmp;;

	new_block = NULL;
	if (!last_ret)
	{
		block = g_start_header_block[type_block];
		tmp = block;
	}
	else
	{
		block = last_ret->next;
		tmp = block;
	}
	while (block)
	{
		if (block->free_size >= size)
			return (block);
		tmp = block;
		block = block->next;
	}
	if (!(new_block = request_tiny_small_block(type_block)))
		return (NULL);
	tmp->next = new_block;
	return (new_block);
}

void			*find_free_chunk(int type_block, size_t size)
{
	t_block		*block_free_space;
	t_chunk		*chunk;
	t_chunk		*free_chunk;
	int			cast_size;

	cast_size = (int)size;
	block_free_space = NULL;
	while (1)
	{
//		ft_putstr("toto 1\n");
		if (!(block_free_space = get_block_with_free_space(block_free_space, type_block, size)))
			return (NULL);
		chunk = (t_chunk *)((char *)block_free_space + SIZEHEADERBLOCK);
		while (chunk)
		{
//			ft_putstr("TATA 1\n");
			if ((chunk->free & FREE) && chunk->size >= cast_size)
			{
//				ft_putstr("TATA IF\n");
				free_chunk = split_chunk(chunk, block_free_space, cast_size);
//				ft_putstr("TATA IF\n");
				return (((char *)free_chunk + SIZEHEADERCHUNK));
			}
			chunk = chunk->next;
//			ft_putstr("TATA 2\n");
		}
//		ft_putstr("toto 2\n");
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
