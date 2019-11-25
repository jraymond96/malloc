/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 07:24:16 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/21 16:07:02 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"
#include "libft.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void	*split_chunk(t_data_chunk *ptr, size_t size)
{
	t_data_chunk	new;

	if (ptr->next)
	{
		ptr->free = 0;
		return ((void *)((char *)ptr + SIZEMETADATA));
	}
	new.free = 1;
	new.size = ptr->size - size - SIZEMETADATA;
	new.next = NULL;
	ft_memcpy((void *)((char *)ptr + SIZEMETADATA + size), &new, SIZEMETADATA);
	ptr->free = 0;
	ptr->size = size;
	ptr->next = (void *)((char *)ptr + SIZEMETADATA + size);
	return ((void *)((char *)ptr + SIZEMETADATA));
}

void	*find_chunk(size_t size, int type_zone)
{
	t_data_chunk	*meta;
	
	if (type_zone == TINY_ZONE)
		meta = g_metas_datas[TINY_ZONE];
	else if (type_zone == TINY_ZONE)
	{
		ft_putstr("VERY_BAD\n");
		meta = g_metas_datas[SMALL_ZONE];
	}
	while (meta)
	{
		if (meta->free && meta->size >= (int)size)
			return (split_chunk(meta, size));
		meta = meta->next;
	}

	return (NULL);
}

t_data_chunk	*request_memory(int type_zone)
{
	t_data_chunk	*addr_map_created;
	t_data_chunk	new;
	long		total_size_request;
	int		page_size;

	page_size = getpagesize();
	if (type_zone > SMALL)
	{
		total_size_request = page_size * ((type_zone + page_size / 2) / page_size);
		if ((addr_map_created = (t_data_chunk *)mmap(NULL, total_size_request, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		{
			ft_putstr("ERROR FUNCITON MMAP\n");
			return (NULL);
		}
		return (addr_map_created);

	}
	total_size_request = page_size * (((type_zone * 101) + page_size / 2) / page_size);
	if ((addr_map_created = (t_data_chunk *)mmap(NULL, total_size_request, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		ft_putstr("ERROR FUNCITON MMAP\n");
		return (NULL);
	}
	new.free = 1;
	new.size = total_size_request - SIZEMETADATA;
	new.next = NULL;
	ft_memcpy(addr_map_created, &new, SIZEMETADATA);
	return (addr_map_created);
}

/*
** size_t size : memory size request by user;
** return : type of zone (tiny small large);
** if global content = null init them with request_memory
*/

int	request_first_memory_zone(size_t size)
{
	if (size <= TINY)
	{
		if (! g_metas_datas[TINY_ZONE])
		{
			if (!(g_metas_datas[TINY_ZONE] = request_memory(TINY)))
				return (-1);
		}
		return (TINY_ZONE);
	}
	if (size <= SMALL)
	{
		ft_putstr("VERY_BAD\n");
		if (! g_metas_datas[SMALL_ZONE])
		{
			if (!(g_metas_datas[SMALL_ZONE] = request_memory(SMALL)))
				return (-1);
		}
		return (SMALL_ZONE);
	}
	return (LARGE_ZONE);
}

void	*handle_large_zone(size_t size)
{
	t_data_chunk	*elem;

	if (! g_metas_datas[LARGE_ZONE])
	{
		if (!(g_metas_datas[SMALL_ZONE] = request_memory(size)))
			return (NULL);
		return ((void *)((char *)g_metas_datas[SMALL_ZONE] + SIZEMETADATA));
	}
	elem = g_metas_datas[LARGE_ZONE];
	while (elem->next)
		elem = elem->next;
	if (! (elem->next = request_memory(size)))
		return (NULL);
	return ((void *)((char *)elem->next + SIZEMETADATA));
}

void	*ft_malloc(size_t size)
{
	int		type_zone;
	void		*new_alloc;

	new_alloc = NULL;
	if ((type_zone = request_first_memory_zone(size)) == -1)
	{
		ft_putstr("call mmap failed");
		return (NULL);
	}
	if (type_zone == LARGE_ZONE)
	{
		if (!(new_alloc = handle_large_zone(size)))
			return (NULL);
		if (g_metas_datas[SMALL_ZONE])
			ft_putstr("2 WTF!!\n");
		else
			ft_putstr("2 DIDN T EXIST\n");
	}
	else if (!(new_alloc = find_chunk(size, type_zone)))
	{
		ft_putstr("no more space !\n");
		return (NULL);
	}
	return (new_alloc);
}
