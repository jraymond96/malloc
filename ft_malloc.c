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
	// TODO: penser a ajouter une confition si on a un next sur ptr pour afficher la bonne taille
	t_data_chunk	new;

	new.free = 1;
	new.size = ptr->size - size - SIZEMETADATA;
	new.next = NULL;
	ft_memcpy((ptr + SIZEMETADATA + size), &new, SIZEMETADATA);
	ptr->free = 0;
	ptr->size = size;
	ptr->next = ptr + SIZEMETADATA + size;

	printf("split1: %p\n", ptr);
	printf("split2: %d\n", SIZEMETADATA);
	printf("split: %p\n", ptr + SIZEMETADATA);
	return (ptr + SIZEMETADATA);
}

void	*find_chunk_tiny(size_t size)
{
	t_data_chunk	*meta;
	
	meta = g_meta_datas->tiny;
	while (meta)
	{
		if (meta->free && meta->size >= (int)size)
		{
			if (meta->size - size > TINYSPLIT)
			{
//				printf("if\n");
				return (split_chunk(meta, size));
			}
			else
			{
//				printf("else\n");
				meta->free = 0;
				return (meta + SIZEMETADATA);
			}
		}
		meta = meta->next;
	}

	return (NULL);
}

t_data_chunk	*request_memory(int type_zone)
{
	t_data_chunk	*addr_map_created;
	t_data_chunk	new;

	if ((addr_map_created = mmap(NULL, type_zone * 101, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		printf("ERROR FUNCITON MMAP\n");
		return (NULL);
	}
	new.free = 1;
	new.size = TINY * 101 - SIZEMETADATA;
	new.next = NULL;
	ft_memcpy(addr_map_created, &new, SIZEMETADATA);

	printf("ret mmap:  %p\n", addr_map_created);
	return (addr_map_created);
}

void	*ft_malloc(size_t size)
{
	t_blocks_start	blocks;
	void			*new_alloc;

	new_alloc = NULL;
	if (! g_meta_datas)
	{
		ft_bzero(&blocks, sizeof(t_blocks_start));
		g_meta_datas = &blocks;
	}
	if (size <= TINY)
	{
		if (! g_meta_datas->tiny)
		{
			if (!(g_meta_datas->tiny = request_memory(TINY)))
				return (NULL);
		}
		if (!(new_alloc = find_chunk_tiny(size)))
			printf("no more space !\n");
		return (new_alloc);
	}

	return (NULL);
}
