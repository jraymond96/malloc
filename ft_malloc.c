/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:36:54 by jraymond          #+#    #+#             */
/*   Updated: 2020/01/27 19:16:10 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "./libft/libft.h"
#include <unistd.h>

size_t		my_malloc_good_size(size_t size)
{
	size_t	rest;
	size_t	align;

	if (size == 0)
		return (SMALLEST_T);
	if (size <= TINY)
		align = TINY_ALIGN;
	else
		align = SMALL_ALIGN;
	if ((rest = size % align))
		return (size + (align - rest));
	else
		return (size);
}

void		*malloc(size_t size)
{
	void	*free_chunk;

	ft_putstr("malloc\n");
	ft_putnbr(size);
	ft_putendl(" size malloc");
	free_chunk = NULL;
	if (g_start_header_block[TINY_BLOCK])
	{
		ft_decimal_to_hexa(g_start_header_block[TINY_BLOCK]);
		ft_putchar('\n');
	}
	if (size > SMALL)
		free_chunk = get_large_block(size);
	else
		free_chunk = handle_tiny_small_block(my_malloc_good_size(size));
	ft_putstr("malloc ret\n");
	show_alloc_mem();
	ft_putendl("\nret_addrr_malloc");
	ft_decimal_to_hexa(free_chunk);
	ft_putchar('\n');
	return (free_chunk);
}
