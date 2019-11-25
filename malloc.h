/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:07:30 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/21 16:07:00 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY 1024
# define SMALL 10002

# define TINY_ZONE	0
# define SMALL_ZONE	1
# define LARGE_ZONE	2

# define TINYSPLIT 20
# define SIZEMETADATA 16
/*
//	type => if block free
*/
typedef struct s_data_chunk	t_data_chunk;

struct						s_data_chunk
{
	int						free;
	int						size;
	void						*next;
};

typedef struct s_blocks_start	t_blocks_start;

struct						s_blocks_start
{
	t_data_chunk					*tiny;
	t_data_chunk					*small;
	t_data_chunk					*large;
};

/*
** metadata globale
*/

t_blocks_start *g_meta_datas;

t_data_chunk	*g_metas_datas[3];

#endif
