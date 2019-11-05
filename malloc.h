/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:07:30 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/05 16:09:47 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define TINY 1024
# define SMALL 4096

/*
//	type is boolean for know if this elem give info on page or on malloc zone.
*/
typedef struct s_meminfo
{
	unsigned int	type : 1;
	int				size_zone;
	int				addr_start;
	t_meminfo		*next;
}				t_meminfo;

typedef struct s_pageinfo
{
	t_meminfo	*tiny;
	t_meminfo	*small;
	t_meminfo	*large;
}				t_pageinfo;
