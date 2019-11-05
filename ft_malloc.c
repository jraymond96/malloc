/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:59:33 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/05 16:09:42 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

#include <stdio.h>

void	*malloc(size_t size)
{
	int addr_map_created

	if ((addr_map_created = mmap(null, SMALL * 100, PROT_WRITE | PROT_READ, MAP_SHARED)) == MAP_FAILED)
	{
		printf("ERROR FUNCITON MMAP");
		return (-1);
	}
	
	if (munmap(addr_map_created, SMALL * 100) == -1)
	{
		printf("ERROR FUNCITON MUNMAP");
		return (-1);
	}

	return (addr_map_created);
}

int		main()
{
	malloc
	return (0);
}
