/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:54:56 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/08 17:10:11 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"
#include "../libft/libft.h"

void	print_tiny_small_info(t_block *header_b)
{
	t_chunk			*chunk;
	char			buf[16];
	int				len;

	if (!header_b || !(chunk = (t_chunk *)(header_b + 1)))
		ft_putstr("Nothing\n");
	else
	{
		ft_decimal_to_hexa((long)header_b, buf);
		len = ft_strlen(buf);
		buf[len] = '\n';
		buf[len + 1] = '\0';
		ft_putstr(buf);
		while (chunk)
		{
			if (!(chunk->free & FREE))
				print_showalloc((void *)chunk, chunk->next, chunk->size);
			chunk = chunk->next;
		}
	}
}


void	print_large_info()
{
	t_block			*block;
	char			buf[16];
	int				len;

	if (!(block = g_header_block[LARGE_BLOCK]))
		ft_putstr("Nothing\n");
	else
	{
		ft_decimal_to_hexa((long)block, buf);
		len = ft_strlen(buf);
		buf[len] = '\n';
		buf[len + 1] = '\0';
		ft_putstr(buf);
		while (block)
		{
			print_showalloc((void *)block, block->next, block->free_size);
			block = block->next;
		}
	}
}

void	show_alloc_mem()
{
	ft_putstr("TINY : ");
	print_tiny_small_info(g_header_block[TINY_BLOCK]);
	ft_putstr("SMALL : ");
	print_tiny_small_info(g_header_block[SMALL_BLOCK]);
	ft_putstr("LARGE : ");
	print_large_info();
}
