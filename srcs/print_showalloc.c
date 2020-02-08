/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_showalloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:59:02 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/08 15:54:27 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"
#include "../libft/libft.h"

void		concat_addr_sizeoctets(char *size, char *result)
{
	int		index;
	int		len_size;

	index = ft_strlen(result);
	len_size = ft_strlen(size);
	ft_memcpy(&result[index], " : ", 3);
	index += 3;
	ft_memcpy(&result[index], size, len_size);
	index += len_size;
	ft_memcpy(&result[index], " octets\n\0", 9);
}

void		concat_addresses(char *start, char *end, char *result)
{
	int		len_start;
	int		len_end;

	len_start = ft_strlen(start);
	len_end = ft_strlen(end);
	ft_memcpy(result, start, len_start);
	ft_memcpy(&result[len_start], " - ", 3);
	len_start += 3;
	ft_memcpy(&result[len_start], end, len_end);
	len_start += len_end;
	result[len_start] = '\0';
}

void		print_showalloc(void *start_addr, void *end_addr, long size)
{
	char	addr1[16];
	char	addr2[16];
	char	str_size[16];
	char	result[64];

	ft_decimal_to_hexa((long)start_addr, addr1);
	if (end_addr)
		ft_decimal_to_hexa((long)end_addr, addr2);
	else
		ft_decimal_to_hexa((long)(char *)start_addr + size, addr2);
	ft_itoa_nomalloc(size, str_size);
	concat_addresses(addr1, addr2, result);
	concat_addr_sizeoctets(str_size, result);
	ft_putstr(result);
}
