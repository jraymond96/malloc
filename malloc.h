/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:07:30 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/26 19:09:08 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY 1024
# define SMALL 10002

# define TINY_BLOCK 0
# define SMALL_BLOCK 1
# define LARGE_BLOCK 2

# define SIZEMETADATA 16
/*
** TODO: autorized define = sizeof() ??
*/

/*
** -------------------- MASK BITWISE FOR FLAGS IN STRUCT T_DATA_CHUNK --------------------
*/

# define FREE_CHUNK (1 << 0)
# define F_META_BLOCK (1 << 1)

/*
** int flags in struct t_data_chumk :	first bit : if chunk is free or not
										second bit : if chunk is first of block
*/

typedef struct s_data_chunk	t_data_chunk;

struct						s_data_chunk
{
	int						flags;
	int						size;
	void						*next;
};

t_data_chunk	*g_metas_datas[3];

t_data_chunk	*last_elem(t_data_chunk *begin);

/*
typedef struct s_blocks_start	t_blocks_start;

struct						s_blocks_start
{
	t_data_chunk					*tiny;
	t_data_chunk					*small;
	t_data_chunk					*large;
};

t_blocks_start *g_meta_datas;
*/
#endif
