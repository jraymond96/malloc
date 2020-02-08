/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_large_block.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 15:53:45 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/08 15:53:48 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"

void	*get_large_block(size_t size)
{
	t_block			*last;
	void			*new;

	if (!(new = request_large_block(size)))
		return (NULL);
	if (!(last = last_header_block(g_header_block[LARGE_BLOCK])))
		g_header_block[LARGE_BLOCK] = (t_block *)new;
	else
		last->next = (t_block *)new;
	return ((void *)((char *)new + SIZEHEADERBLOCK));
}
