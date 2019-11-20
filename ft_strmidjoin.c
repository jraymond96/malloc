/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 13:48:34 by jraymond          #+#    #+#             */
/*   Updated: 2018/06/18 16:12:52 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*cpy(char *dest, char const *src)
{
	int	x;

	x = 0;
	if (!src)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	return (&dest[x]);
}

char	*ft_strmidjoin(char const *s1, char const *s2, char *middle)
{
	char	*new;
	char	*tmp;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(middle) + ft_strlen(s1) + ft_strlen(s2);
	if (!(new = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	tmp = new;
	new = cpy(new, s1);
	new = cpy(new, middle);
	new = cpy(new, s2);
	*new = '\0';
	return (tmp);
}
