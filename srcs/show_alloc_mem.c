/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:54:56 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/09 17:17:24 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"
#include "../libft/libft.h"

void				print_total(long total_malloced)
{
	char			buf[16];
	char			res[32];
	int				buf_len;

	ft_itoa_nomalloc(total_malloced, buf);
	buf_len = ft_strlen(buf);
	ft_memcpy(res, "Total : ", 8);
	ft_memcpy(&res[8], buf, buf_len);
	ft_memcpy(&res[8 + buf_len], " octects\n\0", 10);
	ft_putstr(res);
}

void				print_addr_start_block(t_block *header_b)
{
	char			buf[16];
	int				len;

	ft_memcpy(buf, "0x", 2);
	ft_decimal_to_hexa((long)header_b, &buf[2]);
	len = ft_strlen(buf);
	buf[len] = '\n';
	buf[len + 1] = '\0';
	ft_putstr(buf);
}

long				print_tiny_small_info(t_block *header_b)
{
	t_chunk			*chunk;
	long			size_malloced;

	size_malloced = 0;
	while (header_b)
	{
		chunk = (t_chunk *)(header_b + 1);
		print_addr_start_block(header_b);
		while (chunk)
		{
			if (!(chunk->free & FREE) && (size_malloced += chunk->size))
				print_showalloc((void *)chunk, chunk->next, chunk->size);
			chunk = chunk->next;
		}
		header_b = header_b->next;
	}
	return (size_malloced);
}

long				print_large_info(t_block *block)
{
	char			buf[16];
	int				len;
	long			size_malloced;

	size_malloced = 0;
	ft_decimal_to_hexa((long)block, buf);
	len = ft_strlen(buf);
	buf[len] = '\n';
	buf[len + 1] = '\0';
	ft_putstr(buf);
	while (block)
	{
		print_showalloc((void *)block, block->next, block->free_size);
		size_malloced += block->free_size;
		block = block->next;
	}
	return (size_malloced);
}

void				show_alloc_mem(void)
{
	long			total_malloced;

	total_malloced = 0;
	if (!g_header_block[TINY_BLOCK])
		ft_putstr("TINY :\nNothing\n");
	else
	{
		ft_putstr("TINY : ");
		total_malloced += print_tiny_small_info(g_header_block[TINY_BLOCK]);
	}
	if (!g_header_block[SMALL_BLOCK])
		ft_putstr("SMALL :\nNothing\n");
	else
	{
		ft_putstr("SMALL : ");
		total_malloced += print_tiny_small_info(g_header_block[SMALL_BLOCK]);
	}
	if (!g_header_block[LARGE_BLOCK])
		ft_putstr("LARGE :\nNothing\n");
	else
	{
		ft_putstr("LARGE : ");
		total_malloced += print_large_info(g_header_block[LARGE_BLOCK]);
	}
	print_total(total_malloced);
}
