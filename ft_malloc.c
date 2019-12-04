/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:36:54 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/04 13:53:14 by jraymond         ###   ########.fr       */
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
	free_chunk = NULL;
	if (size > SMALL)
		free_chunk = get_large_block(size);
	else
		free_chunk = handle_tiny_small_block(my_malloc_good_size(size));
	ft_putstr("malloc ret\n");
	return (free_chunk);
}
