/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:54:56 by jraymond          #+#    #+#             */
/*   Updated: 2020/01/27 19:19:34 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"
#include <stdio.h>

void	print_tiny_small_info(t_block *header_b)
{
	t_chunk			*chunk;
	void			*end_malloc;

	(void)end_malloc;
	if (!header_b || !(chunk = (t_chunk *)(header_b + 1)))
		ft_putstr("Nothing\n");
	else
	{
		while (chunk)
		{
/*			if (!(chunk->free & FREE))
			{*/
				ft_putstr("BLABLABLA\n");
//				end_malloc = (void *)((char *)chunk + (chunk->size + SIZEHEADERCHUNK));
//				printf("%p - %p : %d octects\n", (void *)((char *)chunk + SIZEHEADERCHUNK), end_malloc, chunk->size);
				ft_putstr("addr_chunk: ");
				ft_decimal_to_hexa(chunk);
				ft_putchar('\n');
				ft_putnbr(chunk->size);
				ft_putstr(" octects\n");
				ft_putstr("free : ");
				if (!(chunk->free & FREE))
					ft_putstr("non\n");
				else
					ft_putstr("oui\n");
				ft_putstr("free: [");
				ft_putnbr(chunk->free);
				ft_putstr("]\n");
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
			end_malloc = block->next != NULL ? block->next : (void *)((char *)block + block->free_size + SIZEHEADERBLOCK);
//			printf("%p - %p : %zu octects\n", (void *)((char *)block + SIZEHEADERBLOCK), end_malloc, block->free_size);

			ft_printf("%zu octects\n", block->free_size);
			block = block->next;
		}
	}
}

void	show_alloc_mem()
{
	ft_putstr("---------------TINY :\n");
	print_tiny_small_info(g_start_header_block[TINY_BLOCK]);
	ft_putstr("---------------SMALL :\n");
	print_tiny_small_info(g_start_header_block[SMALL_BLOCK]);
	ft_putstr("---------------LARGE :\n");
	print_large_info();
}
