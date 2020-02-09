/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_08.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:24:49 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/09 17:18:54 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"

int		main(void)
{
	char	*ptr[190];
	int		index;

	index = 0;
	while (index < 190)
	{
		ptr[index] = (char *)malloc(992);
		index++;
	}
	index = 0;
	while (index < 190)
	{
		free(ptr[index]);
		index++;
	}
	show_alloc_mem();
	return (0);
}
