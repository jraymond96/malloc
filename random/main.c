/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:06:14 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/04 15:00:10 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./libft/libft.h"
# include "malloc.h"
# include <stdio.h>
# include <unistd.h>

int	main()
{
	void	*addr[100];
	int		i;

	i = 0;
	while (i < 5)
	{
		if (!(addr[i] = malloc(20)))
		{
			ft_putstr("MALLOC = NULL\n");
			return (0);
		}
		i++;
	}
	ft_putstr("MAIN 1\n");
	free(addr[1]);	
	ft_putstr("MAIN 2\n");
	free(addr[4]);
	free(addr[3]);
	if (((char *)addr[0])[1] == 'a' )
		ft_putstr("dewd");
	return (0);
}
