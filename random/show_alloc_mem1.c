/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:54:56 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/06 18:48:00 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"
#include <stdio.h>

static long		countint(int n)
{
	long	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len++);
}

void			add_size_chunk(int n, char *str)
{
	long	n_lenght;
	long	len;
	char	buf[40];

	ft_bzero(&buf[0], 40);
	n_lenght = n;
	len = countint(n_lenght);
	len--;
	while (len >= 0)
	{
		buf[len] = (n_lenght % 10) + '0';
		len--;
		n_lenght /= 10;
	}
	ft_memcpy(str, &buf[0], len + 1);
}
void		*concat_and_print(char *start, char *end, int size)
{
	char	buff[100];
	int		index;
	int		start_size;
	int		end_size;

	start_size = ft_strlen(start);
	end_size = ft_strlen(end);
	index = start_size;
	ft_memcpy(&buff[0], start, ft_strlen(start));
	ft_memcpy(&buff[index], " - ", 3);
	index += 3;
	ft_memcpy(&buff[index], end, end_size);
	index+= end_size;
	ft_memcpy(&buff[index], " : ", 3);
	index += 3;
	add_size_chunk(size, &buff[index]);
	index = ft_strlen(&buff[0]);
	ft_memcpy(&buff[index], " octets\n", 8);
	ft_putstr(buff);
}

void		print_tiny_small_info(t_block *header_b)
{
	t_chunk	*chunk;
	char	*start_malloc;
	char	*end_malloc;

	if (!header_b || !(chunk = (t_chunk *)(header_b + 1)))
		ft_putstr("Nothing\n");
	else
	{
		while (chunk)
		{
			if (!(chunk->free & FREE))
			{
				start_malloc = ft_decimal_to_hexa((void *)(chunk + 1));
				end_malloc = ft_decimal_to_hexa((void *)((char *)chunk + (chunk->size + SIZEHEADERCHUNK)));
				concat_and_print(start_malloc, end_malloc, size);
				chunk = chunk->next;
			}
		}
	}
}


void	print_large_info()
{
	t_block			*block;
	char			*start_malloc;
	char			*end_malloc;

	if (!(block = g_header_block[LARGE_BLOCK]))
		ft_putstr("Nothing\n");
	else
	{
		while (block)
		{
			start_malloc = ft_decimal_to_hexa((void *)(block + 1));
			end_malloc = ft_decimal_to_hexa((void *)((char *)block + (block->free_size + SIZEHEADERBLOCK)));
//			end_malloc = block->next != NULL ? block->next : (void *)((char *)block + block->free_size + SIZEHEADERBLOCK);
			ft_printf("%s - %s : %zu octects\n", start_malloc, end_malloc, block->free_size);
			block = block->next;
		}
	}
}

void	show_alloc_mem()
{
	ft_putstr("TINY :\n");
	print_tiny_small_info(g_header_block[TINY_BLOCK]);
	ft_putstr("SMALL :\n");
	print_tiny_small_info(g_header_block[SMALL_BLOCK]);
	ft_putstr("LARGE :\n");
	print_large_info();
}
