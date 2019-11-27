/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:54:56 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/27 21:13:07 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include <stdio.h>

void	print_tiny_small_info(t_block *header_b)
{
	void			*end_malloc;
	t_chunk			*chunk;

	if (!header_b || !(chunk = (t_chunk *)(header_b + 1)))
		ft_putstr("Nothing\n");
	else
	{
		while (chunk)
		{
			if (!(chunk->size & NEG_BYTE))
			{
				end_malloc = chunk->next != NULL ? chunk->next : (void *)((char *)chunk + chunk->size + SIZEHEADERCHUNK);
				printf("%p - %p : %d octects\n", (void *)((char *)chunk + SIZEHEADERCHUNK), end_malloc, chunk->size);
			}
			chunk = chunk->next;
		}
	}
}


void	print_large_info()
{
	t_block			*block;
	void			*end_malloc;

	if (!(block = g_start_header_block[LARGE_BLOCK]))
		ft_putstr("Nothing\n");
	else
	{
		while (block)
		{
			end_malloc = block->next != NULL ? block->next : (void *)((char *)block + block->size_free + SIZEHEADERBLOCK);
			printf("%p - %p : %zu octects\n", (void *)((char *)block + SIZEHEADERBLOCK), end_malloc, block->size_free);
			block = block->next;
		}
	}
}

void	show_alloc_mem()
{
	ft_putstr("TINY :\n");
	print_tiny_small_info(g_start_header_block[TINY_BLOCK]);
	ft_putstr("SMALL :\n");
	print_tiny_small_info(g_start_header_block[SMALL_BLOCK]);
	ft_putstr("LARGE :\n");
	print_large_info();
}
