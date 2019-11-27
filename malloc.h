/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:07:30 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/27 20:54:59 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <string.h>

# define TINY 992
# define SMALL 126976

# define TINY_MULTIPLE 16
# define SMALL_MULTIPLE 512

# define TINY_BLOCK 0
# define SMALL_BLOCK 1
# define LARGE_BLOCK 2

# define SIZEHEADERBLOCK 16
# define SIZEHEADERCHUNK 24

/*
**|-------------------------------------------------|
**|						MASK						|
**|-------------------------------------------------|
*/

# define NEG_BYTE (1 << 31)

/*
**|-------------------------------------------------|
**|						STRCTURES					|
**|-------------------------------------------------|
*/

typedef struct s_header_chunk	t_chunk;

struct							s_header_chunk
{	
	int							flags;
	int							size;
	void						*prev;
	void						*next;
};


typedef struct s_header_block	t_block;

struct							s_header_block
{
	void						*prev;
	void						*next;
	size_t						size_free;
};

/*
**|-------------------------------------------------|
**|						GLOBAL						|
**|-------------------------------------------------|
*/

t_block							*g_start_header_block[3];

/*
**|-------------------------------------------------|
**|						FUNCTIONS					|
**|-------------------------------------------------|
*/

t_block							*last_header_block(t_block *begin);
t_chunk							*last_header_chunk(t_chunk *begin);

void							*request_large_block(size_t size);
void							*get_large_block(size_t size);

#endif
