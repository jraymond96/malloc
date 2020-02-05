/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:36:18 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/05 19:05:04 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "malloc.h"
#include "./libft/libft.h"

void		*handle_large_block(t_block	*block, size_t size)
{
	t_block	*prev;
	t_block	*next;
	void	*res;

	prev = (t_block *)block->prev;
	next = (t_block *)block->next;
	if (size <= block->free_size)
		return ((void *)block);
	else
	{
		if (prev)
			prev->next = next;
		else
			g_start_header_block[LARGE_BLOCK] = next;
		if (next)
			next->prev = prev;
	}
	if (!(res = malloc(size)))
		return (NULL);
	ft_memcpy(res, (block + 1), block->free_size);
	munmap(block, (block->free_size + SIZEHEADERBLOCK));
	return (res);
}

void		*handle_tiny_small(void *ptr, size_t size)
{
	t_block	*block;
	void	*res;
	t_chunk	*info_ptr;

	if ((block = is_tiny_small_block(ptr, TINY_BLOCK)) || 
		((block = is_tiny_small_block(ptr, SMALL_BLOCK))))
	{
		if (ptr_is_exist_chunk(ptr, block))
		{
			info_ptr = (t_chunk *)((char *)ptr - SIZEHEADERCHUNK);
			if ((size_t)info_ptr->size >= size)
				return (ptr);
			else
			{
				if (!(res = malloc(size)))
					return (NULL);
				ft_memcpy(res, ptr, (size_t)info_ptr->size);
				free(ptr);
				return (res);
			}
		}
	}
	return (NULL);
}

void		*realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*res;

//	ft_putstr("START REALLOC: ");
//	ft_decimal_to_hexa(ptr);
//	ft_putchar('\n');
//	ft_putnbr(size);
//	ft_putchar('\n');
	if (ptr && !size)
	{
//		ft_putstr("END REALLOC\n");
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
	{
//		ft_putstr("END REALLOC !ptr\n");
		return (malloc(size));
	}
	if ((block = is_large_block(ptr)))
	{
		res = handle_large_block(block, size);
//		ft_putstr("END REALLOC\n");
		return (res);
	}
	res = handle_tiny_small(ptr, size);
//	ft_putstr("END REALLOC\n");
//	show_alloc_mem();
	return (res);
}
