/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:45:08 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/06 15:43:38 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "malloc.h"
#include "./libft/libft.h"

t_block		*is_large_block(void *ptr)
{
	t_block	*block;

	block = g_header_block[LARGE_BLOCK];
	while (block)
	{
		if (block + 1 == ptr)
			break ;
		block = block->next;
	}
	return (block);
}

void		munmap_block(int type_block, t_block *block)
{
	int		biggest_size;
	int		size_munmap;

	if (type_block == TINY_BLOCK)
	{
		biggest_size = FIRSTSIZE_TBLOCK;
		size_munmap = REALSIZE_TBLOCK;
	}
	else
	{
		biggest_size = FIRSTSIZE_SBLOCK;
		size_munmap = REALSIZE_SBLOCK;
	}
	if (((t_chunk *)((char *)block + SIZEHEADERBLOCK))->size == biggest_size)
	{
		if (block->prev)
			((t_block *)block->prev)->next = block->next;
		else
			g_header_block[type_block] = block->next;
		if (block->next)
			((t_block *)block->next)->prev = block->prev;
		munmap(block, size_munmap);
	}
}

t_block		*is_tiny_small_block(void *ptr, int type_block)
{
	t_block	*block;
	void	*start_block;
	int		size_block;

	block = g_header_block[type_block];
	size_block = (type_block == TINY_BLOCK) ? REALSIZE_TBLOCK : REALSIZE_SBLOCK;
	while (block)
	{
		start_block = block + 1;
		if (start_block <= ptr && ptr < (void *)((char *)block + size_block))
			break ;
		block = block->next;
	}
	return (block);
}

int			get_type_block(void *ptr, t_block **block_content_chunk)
{
	int		type_block;

	type_block = -1;
	if ((*block_content_chunk = is_tiny_small_block(ptr, TINY_BLOCK)))
		type_block = TINY_BLOCK;
	else if ((*block_content_chunk = is_tiny_small_block(ptr, SMALL_BLOCK)))
		type_block = SMALL_BLOCK;
	return (type_block);
}

void		free(void *ptr)
{
	t_block	*block_content_chunk;
	t_block	*large_block;
	int		type_block;

	if (!ptr)
		return ;
	if ((large_block = is_large_block(ptr)))
	{
		if (large_block->prev)
			((t_block *)large_block->prev)->next = large_block->next;
		else
			g_header_block[LARGE_BLOCK] = large_block->next;
		if (large_block->next)
			((t_block *)large_block->next)->prev = large_block->prev;
		munmap(large_block, (large_block->free_size + SIZEHEADERBLOCK));
	}
	else
	{
		if ((type_block = (get_type_block(ptr, &block_content_chunk)) == -1))
			return ;
		handle_free_chunk(ptr, block_content_chunk);
		munmap_block(type_block, block_content_chunk);
	}
}
