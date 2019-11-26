/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:37:17 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/26 19:09:10 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_data_chunk	*last_elem(t_data_chunk *begin)
{
	if (!begin)
		return (NULL);
	while (begin->next)
		begin = begin->next;
	return (begin);
}
