/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:45:08 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/05 21:18:44 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "malloc.h"
#include "./libft/libft.h"

t_block		*is_large_block(void *ptr)
{
	t_block	*block;

	block = g_start_header_block[LARGE_BLOCK];
	while (block)
	{
		if (block + 1 == ptr)
			break;
		block = block->next;
	}

	return (block);
}

int			ptr_is_exist_chunk(void *ptr, t_block *block)
{
	t_chunk	*chunk;

	chunk = (t_chunk *)((char *)block + SIZEHEADERBLOCK);
	while (chunk)
	{
//		ft_putstr("addr_chunk\n");
//		ft_decimal_to_hexa(chunk + 1);
//		ft_putchar('\n');
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
		return;
//	show_alloc_mem();
//	ft_putstr("content free : ");
//	ft_putnbr(data_ptr->free);
//	ft_putchar('\n');
	data_ptr->free |= FREE;
	block->free_size += data_ptr->size;
//	show_alloc_mem();
	handle_defragmentation(data_ptr, block);
}

t_block		*is_tiny_small_block(void *ptr, int type_block)
{
	t_block	*block;
	void	*start_block;
	int		size_block;

	block = g_start_header_block[type_block];
	size_block = (type_block == TINY_BLOCK) ? REALSIZE_TBLOCK : REALSIZE_SBLOCK;
	while (block)
	{
		start_block = block + 1;
		if (start_block <= ptr && ptr < (void *)((char *)block + size_block))
			break;
		block = block->next;
	}

	return (block);
}

void		munmap_block(int type_block, t_block *block)
{
	int		biggest_chunk_size;
	int		size_munmap;

	if (type_block == TINY_BLOCK)
	{
		biggest_chunk_size = FIRSTSIZE_TBLOCK;
		size_munmap = REALSIZE_TBLOCK;
	}
	else
	{
		biggest_chunk_size = FIRSTSIZE_SBLOCK;
		size_munmap = REALSIZE_SBLOCK;
	}
	if (((t_chunk *)((char *)block + SIZEHEADERBLOCK))->size == biggest_chunk_size)
	{
		if (block->prev)
			((t_block *)block->prev)->next = block->next;
		else
			g_start_header_block[type_block] = block->next;
		if (block->next)
			((t_block *)block->next)->prev = block->prev;
		munmap(block, size_munmap);
	}
}

void		free(void *ptr)
{
//	ft_putstr("START FREE\n");
//	ft_putendl("addr_free_ptr");
//	ft_decimal_to_hexa(ptr);
//	ft_putchar('\n');
	t_block	*block_content_chunk;
	t_block	*large_block;
	int		type_block;

//	show_alloc_mem();
	if (!ptr)
	{
//		ft_putstr("END FREE 1\n");
		return;
	}
	if ((large_block = is_large_block(ptr)))
	{
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
		if ((block_content_chunk = is_tiny_small_block(ptr, TINY_BLOCK)))
		{
//			ft_putstr("TINY_BLOCK\n");
			type_block = TINY_BLOCK;
		}
		else if ((block_content_chunk = is_tiny_small_block(ptr, SMALL_BLOCK)))
		{
//			ft_putstr("SMALL_BLOCK\n");
			type_block = SMALL_BLOCK;
		}
		else
		{
//			ft_putstr("END FREE no exist ptr\n");
			return;
		}
		handle_free_chunk(ptr, block_content_chunk);
		munmap_block(type_block, block_content_chunk);
	}
//	show_alloc_mem();
//	ft_putstr("END FREE 2\n");
}
