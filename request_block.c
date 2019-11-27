/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:03:12 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/27 21:13:05 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "malloc.h"
#include "libft.h"

#include <stdio.h>

void	*request_large_block(size_t size)
{
	void			*new_block;
	t_block			header_block;
	size_t			total_size;
	size_t			page_size;

	page_size = (size_t)getpagesize();
	total_size = page_size * (((size + SIZEHEADERBLOCK) + page_size / 2) / page_size);
	printf("total: %zu\n", total_size);
	if ((new_block = (t_block *)mmap(NULL, total_size, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		ft_putstr("ERROR FUNCITON MMAP\n");
		return (NULL);
	}
	header_block.size_free = total_size - SIZEHEADERBLOCK;
	header_block.prev = NULL;
	header_block.next = NULL;
	ft_memcpy(new_block, &header_block, SIZEHEADERBLOCK);
	return (new_block);
}
