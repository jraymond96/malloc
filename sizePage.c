/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizePage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:06:47 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/05 12:11:42 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("size of one page: %d", getpagesize());
	return (0);
}