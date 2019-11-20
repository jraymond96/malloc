/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 07:24:16 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/20 19:09:19 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"
#include <sys/mman.h>

#include <stdio.h>


void	*find_chunck(size_t size)
{
	long long	*first_meta_data = (long long)(g_meta_datas->tiny + 8)
	if (first_meta_data)
}

void	init()
{
	t_blocks_start	*blocks;

	ft_bzero(blocks, sizeof(t_blocks_start));
	g_meta_datas = blocks;
}

void	*ft_malloc(size_t size)
{
	void *addr_map_created;

	addr_map_created = NULL;
	init();
	if (size <= TINY)
	{
		if (g_meta_datas->tiny)
		{
			if (find_chunck(size))
		}
		else
		{
			if ((addr_map_created = mmap(null, TINY * 101, PROT_WRITE | PROT_READ, MAP_SHARED)) == MAP_FAILED)
			{
				printf("ERROR FUNCITON MMAP");
				return (-1);
			}
			ft_bzero(addr_map_created, 9);
			g_meta_datas->tiny = addr_map_created;
		}
	}
	if (munmap(addr_map_created, SMALL * 101) == -1)
	{
		printf("ERROR FUNCITON MUNMAP");
		return (-1);
	}

	return (addr_map_created);
}
