/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:08:52 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/03 05:07:03 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memdup(char *str, size_t len)
{
	char	*new;
	int		x;

	if (!(new = malloc(len + 1)))
		return (NULL);
	x = -1;
	while (len)
	{
		new[++x] = *str;
		str++;
		len--;
	}
	new[++x] = '\0';
	return (new);
}
