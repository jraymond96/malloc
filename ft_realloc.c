/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:31:34 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/04 14:46:02 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "malloc.h"
#include "./libft/libft.h"

void	*realloc(void *ptr, size_t size)
{
	void	*exist_ptr;
	void	*new;

	ft_putstr("realloc\n");
	if (! ptr)
	{
		ft_putstr("realloc ret\n");
		return (malloc(size));
	}
	if ((exist_ptr = ptr_is_large_block(ptr)))
	{
		if (size != 0 && !(new = malloc(size)))
		{
			ft_putstr("realloc ret\n");
			return (NULL);
		}
		if (size != 0)
			ft_memcpy(new, ((char *)exist_ptr + SIZEHEADERBLOCK), size);
		munmap(exist_ptr, ((t_block *)exist_ptr)->free_size);
	}
	else if ((exist_ptr = search_in_tiny_small_blocks(ptr)))
	{
		if ((size_t)((t_chunk *)exist_ptr)->size >= size && size != 0)
		{
			ft_putstr("realloc ret\n");
			return (ptr);
		}
		else
		{
			((t_chunk *)exist_ptr)->free |= FREE;
			handle_defragmentation(exist_ptr);
			if (size == 0)
			{
				ft_putstr("realloc ret\n");
				return (NULL);
			}
			ft_putstr("realloc ret\n");
			return (malloc(size));
		}
	}

	ft_putstr("realloc ret\n");
	return (NULL);
}
