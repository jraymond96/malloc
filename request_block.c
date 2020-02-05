/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:03:12 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/05 21:18:49 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "malloc.h"
#include "./libft/libft.h"

void				creat_headers(void *start_block, int type_block)
{
	t_block			header_block;
	t_chunk			header_chunk;

	if (type_block == TINY_BLOCK)
		header_block.free_size = FIRSTSIZE_TBLOCK;
	else
		header_block.free_size = FIRSTSIZE_SBLOCK;
	header_block.prev = NULL;
	header_block.next = NULL;

	header_chunk.size = header_block.free_size;
	header_chunk.free = 1;
	header_chunk.prev = NULL;
	header_chunk.next = NULL;

	ft_memcpy(start_block, &header_block, SIZEHEADERBLOCK);
	ft_memcpy(((char *)start_block + SIZEHEADERBLOCK), &header_chunk, SIZEHEADERCHUNK);
}

void				*request_tiny_small_block(int type_block)
{
	void			*new_block;
	size_t			size_block;


	if (type_block == TINY_BLOCK)
		size_block = REALSIZE_TBLOCK;
	else
		size_block = REALSIZE_SBLOCK;
	if ((new_block = mmap(NULL, size_block, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		ft_putstr("ERROR FUNCITON MMAP\n");
		return (NULL);
	}
	creat_headers(new_block, type_block);
	return (new_block);

}

void				*request_large_block(size_t size)
{
	t_block			header_block;
	void			*new_block;
	size_t			total_size;
	int				modulo;

	if ((modulo = ((size + SIZEHEADERBLOCK) % PAGESIZE)))
		total_size = (size + SIZEHEADERBLOCK) + (PAGESIZE - modulo);
	else
		total_size = size + SIZEHEADERBLOCK;
	if ((new_block = mmap(NULL, total_size, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		ft_putstr("ERROR FUNCITON MMAP\n");
		return (NULL);
	}
	header_block.free_size = total_size - SIZEHEADERBLOCK;
	header_block.prev = NULL;
	header_block.next = NULL;
	ft_memcpy(new_block, &header_block, SIZEHEADERBLOCK);
	return (new_block);
}
