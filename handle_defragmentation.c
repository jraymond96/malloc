/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_defragmentation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:22:54 by jraymond          #+#    #+#             */
/*   Updated: 2020/01/27 17:05:21 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "./libft/libft.h"

void		next_or_prev_free(t_chunk *ptr, t_chunk *prev, t_chunk *next)
{
	if (prev && prev->free & FREE)
	{
		prev->size += ptr->size + SIZEHEADERCHUNK;
		prev->next = next;
		next->prev = prev;
	}
	else
	{
		ptr->size += next->size + SIZEHEADERCHUNK;
		ptr->next = next->next;
		((t_chunk *)next->next)->prev = ptr;
	}
}

void		handle_defragmentation(t_chunk *ptr, t_block *block)
{
	t_chunk	*prev;
	t_chunk	*next;

	prev = ((t_chunk *)ptr)->prev;
	next = ((t_chunk *)ptr)->next;
	if ((prev && prev->free & FREE) && (next && next->free & FREE))
	{
		ft_putstr("DEFRAGMENTATION IF\n");
		prev->size += (ptr->size + next->size) + (SIZEHEADERCHUNK * 2);
		prev->next = next->next;
		if (next->next)
			((t_chunk *)next->next)->prev = prev;
		block->free_size += SIZEHEADERCHUNK * 2;
	}
	else if ((prev && prev->free & FREE) || (next && next->free & FREE))
	{
		ft_putstr("DEFRAGMENTATION ELSE IF\n");
		next_or_prev_free(ptr, prev, next);
		block->free_size += SIZEHEADERCHUNK;
	}
}
