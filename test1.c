/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:34:15 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/05 19:22:58 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdio.h>

int		main()
{
	char	*toto;

	ft_putstr("MAIN START\n\n\n");
	toto = malloc(10);
	toto[0] = 'c';
	toto[1] = 'h';
	toto[2] = 'a';
	toto[3] = 'r';
	toto[4] = 'l';
	toto[5] = 'i';
	toto[6] = 'e';
	toto[7] = '\0';

	ft_putendl(toto);
	printf("salut moi c'est %s .\n", toto);
	return (0);
}
