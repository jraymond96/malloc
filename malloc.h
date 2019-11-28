/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:07:30 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/28 16:20:47 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <string.h>

# define PAGESIZE 4096

# define TINY 992
# define SMALL 126976

# define SMALLEST_T 16
# define SMALLEST_S 1024

# define TINY_ALIGN 16
# define SMALL_ALIGN 512

# define TINY_BLOCK 0
# define SMALL_BLOCK 1
# define LARGE_BLOCK 2

# define SIZEHEADERBLOCK 24
# define SIZEHEADERCHUNK 24
# define SIZE_HBLOCK_HCHUNK 48

/*
** subject said : your block need handle 100 malloc of tiny/small max size tiny/small
*/

# define SIZE_TBLOCK (((TINY + SIZEHEADERCHUNK) * 100) + SIZEHEADERBLOCK)
# define SIZE_SBLOCK (((SMALL + SIZEHEADERCHUNK) * 100) + SIZEHEADERBLOCK)

# define REALSIZE_TBLOCK (SIZE_TBLOCK + (PAGESIZE - (SIZE_TBLOCK % PAGESIZE)))
# define REALSIZE_SBLOCK (SIZE_SBLOCK + (PAGESIZE - (SIZE_SBLOCK % PAGESIZE)))

/*
**|-------------------------------------------------|
**|						MASK						|
**|-------------------------------------------------|
*/

# define FREE (1 << 0)

/*
**|-------------------------------------------------|
**|						STRCTURES					|
**|-------------------------------------------------|
*/

typedef struct s_header_chunk	t_chunk;

struct							s_header_chunk
{
	int							size;
	int							free;
	void						*prev;
	void						*next;
};


typedef struct s_header_block	t_block;

struct							s_header_block
{
	size_t						free_size;
	void						*prev;
	void						*next;
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
