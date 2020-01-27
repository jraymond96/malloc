/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:34:15 by jraymond          #+#    #+#             */
/*   Updated: 2020/01/23 18:38:09 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"

int		main()
{
	char	*toto;
	char	*res[4];
	int		x;

	toto = malloc(10);
	toto[0] = 'c';
	toto[1] = 'h';
	toto[2] = 'a';
	toto[3] = 'r';
	toto[4] = 'l';
	toto[5] = 'i';
	toto[6] = 'e';
	toto[7] = '\0';

	ft_putstr(toto);
	ft_putchar('\n');
	ft_putstr("start\n");
	ft_putstr((res[0] = ft_decimal_to_hexa(921)));
	ft_putstr("\nend");
	ft_putchar('\n');
	ft_putstr("start\n");
	ft_putstr((res[1] = ft_decimal_to_hexa(188)));
	ft_putstr("\nend");
	ft_putchar('\n');
	ft_putstr("start\n");
	ft_putstr((res[2] = ft_decimal_to_hexa(100)));
	ft_putstr("\nend");
	ft_putchar('\n');
	ft_putstr("start\n");
	ft_putstr((res[3] = ft_decimal_to_hexa(590)));
	ft_putstr("\nend");
	ft_putchar('\n');

	x = -1;
	while (++x < 4)
	{
		free(res[x]);
	}
	return (0);
}
