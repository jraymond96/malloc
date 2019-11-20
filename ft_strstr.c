/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <jraymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:55:27 by jraymond          #+#    #+#             */
/*   Updated: 2018/06/20 09:17:36 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	if (!to_find || !str)
		return (NULL);
	if (to_find[0] == '\0')
		return ((char*)&str[i]);
	while (str[i] != '\0')
	{
		j = i;
		k = 0;
		while (to_find[k] == str[j])
		{
			k++;
			j++;
			if (to_find[k] == '\0')
				return ((char*)&str[i]);
		}
		i++;
	}
	return (NULL);
}
