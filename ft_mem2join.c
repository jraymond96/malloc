/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem2join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 18:46:40 by jraymond          #+#    #+#             */
/*   Updated: 2018/06/26 18:46:16 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_mem2join(char *dest, char *s1, char *s2, size_t size)
{
	if (s1)
		ft_strcpy(dest, s1);
	dest += ft_strlen(dest);
	if (s2)
	{
		while (size-- && *s2)
		{
			*dest = *s2;
			dest++;
			s2++;
		}
	}
	*dest = '\0';
}
