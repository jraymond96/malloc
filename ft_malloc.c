/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:36:54 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/02 16:14:08 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*free_chunk;

	free_chunk = NULL;
	if (size > SMALL)
		free_chunk = get_large_block(size);
	else
		free_chunk = handle_tiny_small_block(size);
	return (free_chunk);
}
