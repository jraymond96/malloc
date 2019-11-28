/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:06:14 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/28 09:40:34 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "malloc.h"
# include <stdio.h>
# include <unistd.h>

int	main()
{
	int	i;

	i = 0;
	while (i < 110)
	{
		ft_malloc(147456);
		i++;
	}

	show_alloc_mem();
	return (0);
}
