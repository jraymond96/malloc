/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:31:34 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/04 15:43:33 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "malloc.h"
#include "./libft/libft.h"

void	*realloc(void *ptr, size_t size)
{
	void	*exist_ptr;
	void	*new;
	size_t	less_size;
	t_block	*t;

	t = NULL;
	ft_putstr("realloc\n");
	less_size = 0;
	if (! ptr)
	{
		if (!size)
			return (NULL);
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
		less_size = size < ((t_block *)exist_ptr)->free_size ? size : ((t_block *)exist_ptr)->free_size;
		if (size != 0)
			ft_memcpy(new, ((char *)exist_ptr + SIZEHEADERBLOCK), less_size);
		munmap(exist_ptr, ((t_block *)exist_ptr)->free_size);
	}
	else if ((exist_ptr = search_in_tiny_small_blocks(&t, ptr)))
	{
		if ((size_t)((t_chunk *)exist_ptr)->size >= size && size != 0)
		{
			ft_putstr("realloc ret\n");
			return (ptr);
		}
		else
		{
			if (size == 0)
				free(ptr);
			else
			{
				if ((new = malloc(size)))
				{
					less_size = size < ((t_chunk *)exist_ptr)->size ? size : ((t_chunk *)exist_ptr)->size;
					ft_memcpy(new, ((char *)exist_ptr + SIZEHEADERBLOCK), less_size);
					free(ptr);
					ft_putstr("realloc ret\n");
					return (new);
				}
			}
		}
	}

	ft_putstr("realloc ret\n");
	return (NULL);
}
