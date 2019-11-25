/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:06:14 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/21 12:46:43 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "malloc.h"
# include <stdio.h>
# include <unistd.h>

int	main()
{
	int		*toto;
	int		*titi;
//	t_data_chunk	*start;

	toto = ft_malloc(10);
	titi = ft_malloc(10);
	(void)toto;
	(void)titi;

	show_alloc_mem();
	return (0);
}
