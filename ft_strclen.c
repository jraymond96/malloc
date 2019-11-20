/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 10:30:39 by jraymond          #+#    #+#             */
/*   Updated: 2018/06/18 17:40:29 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strclen(char *str, char c)
{
	size_t	len;

	len = 0;
	if (!c || !str)
		return (ft_strlen(str));
	else
	{
		while (str[len] && str[len] != c)
			len++;
		return (len);
	}
}
