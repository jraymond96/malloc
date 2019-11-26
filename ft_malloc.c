/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 07:24:16 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/26 19:09:12 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"
#include "libft.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

t_data_chunk	*request_memory(int type_block)
{
	t_data_chunk	*addr_map_created;
	t_data_chunk	new;
	long		total_size_request;
	int		page_size;

	page_size = getpagesize();
	if (type_block > SMALL)
	{
		total_size_request = page_size * ((type_block + page_size / 2) / page_size);
		if ((addr_map_created = (t_data_chunk *)mmap(NULL, total_size_request, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		{
			ft_putstr("ERROR FUNCITON MMAP\n");
			return (NULL);
		}
		return (addr_map_created);

	}
	total_size_request = page_size * (((type_block * 101) + page_size / 2) / page_size);
	if ((addr_map_created = (t_data_chunk *)mmap(NULL, total_size_request, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		ft_putstr("ERROR FUNCITON MMAP\n");
		return (NULL);
	}
	new.flags = 0 | FREE_CHUNK;
	new.flags |= F_META_BLOCK;
	new.size = total_size_request - SIZEMETADATA;
	new.next = NULL;
	ft_memcpy(addr_map_created, &new, SIZEMETADATA);
	return (addr_map_created);
}

void	*split_chunk(t_data_chunk *ptr, size_t size)
{
	t_data_chunk	new;

	if (ptr->next)
	{
		ptr->flags ^= FREE_CHUNK;
		return ((void *)((char *)ptr + SIZEMETADATA));
	}
	new.flags = 0 | FREE_CHUNK;
	new.size = ptr->size - size - SIZEMETADATA;
	new.next = NULL;
	ft_memcpy((void *)((char *)ptr + SIZEMETADATA + size), &new, SIZEMETADATA);
	ptr->flags ^= FREE_CHUNK;
	ptr->size = size;
	ptr->next = (void *)((char *)ptr + SIZEMETADATA + size);
	return ((void *)((char *)ptr + SIZEMETADATA));
}

void	*find_chunk(size_t size, int type_block)
{
	t_data_chunk	*meta;

	meta = NULL;
	if (type_block == TINY_BLOCK)
		meta = g_metas_datas[TINY_BLOCK];
	else if (type_block == SMALL_BLOCK)
		meta = g_metas_datas[SMALL_BLOCK];
	while (meta)
	{
		if ((meta->flags & FREE_CHUNK) && meta->size >= (int)size)
			return (split_chunk(meta, size));
		meta = meta->next;
	}
	return (NULL);
}

/*
** size_t size : memory size request by user;
** return : type of block (tiny small large);
** if global content = null init them with request_memory
*/

int	request_first_memory_block(size_t size)
{
	if (size <= TINY)
	{
		if (! g_metas_datas[TINY_BLOCK])
		{
			if (!(g_metas_datas[TINY_BLOCK] = request_memory(TINY)))
				return (-1);
		}
		return (TINY_BLOCK);
	}
	else if (size <= SMALL)
	{
		if (! g_metas_datas[SMALL_BLOCK])
		{
			if (!(g_metas_datas[SMALL_BLOCK] = request_memory(SMALL)))
				return (-1);
		}
		return (SMALL_BLOCK);
	}
	return (LARGE_BLOCK);
}

void	*handle_large_block(size_t size)
{
	t_data_chunk	*elem;

	if (! g_metas_datas[LARGE_BLOCK])
	{
		if (!(g_metas_datas[SMALL_BLOCK] = request_memory(size)))
			return (NULL);
		return ((void *)((char *)g_metas_datas[SMALL_BLOCK] + SIZEMETADATA));
	}
	elem = g_metas_datas[LARGE_BLOCK];
	while (elem->next)
		elem = elem->next;
	if (! (elem->next = request_memory(size)))
		return (NULL);
	return ((void *)((char *)elem->next + SIZEMETADATA));
}

void	*handle_tiny_small_block(size_t size, int type_block)
{
	void			*free_address;
	t_data_chunk	*last_metadata;

	while (1)
	{
		free_address = find_chunk(size, type_block)
		if (free_address)
			return (free_address);
		last_metadata = last_elem(g_meta_datas[type_block]);
		// call function 
	}
}

void	*ft_malloc(size_t size)
{
	int		type_block;
	void		*new_alloc;

	new_alloc = NULL;
	if ((type_block = request_first_memory_block(size)) == -1)
	{
		ft_putstr("call mmap failed");
		return (NULL);
	}
	if (type_block == LARGE_BLOCK)
	{
		if (!(new_alloc = handle_large_block(size)))
			return (NULL);
	}
	else if (!(new_alloc = find_chunk(size, type_block)))
	{
		ft_putstr("no more space !\n");
		return (NULL);
	}
	return (new_alloc);
}

/*
** TODO:TOTALY SEPARATE LARGE OF TINY AND SMALL
*/
