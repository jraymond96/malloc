/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:07:30 by jraymond          #+#    #+#             */
/*   Updated: 2020/02/09 17:25:11 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <string.h>

# define PAGESIZE 4096
# define FD 2

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
** subject said : your block need handle 100 malloc
**   of tiny/small max size tiny/small
*/

/*
**# define SIZE_TBLOCK (((TINY + SIZEHEADERCHUNK) * 100) + SIZEHEADERBLOCK)
**# define SIZE_SBLOCK (((SMALL + SIZEHEADERCHUNK) * 100) + SIZEHEADERBLOCK)
**
**# define REALSIZE_TBLOCK (SIZE_TBLOCK + (PAGESIZE - (SIZE_TBLOCK % PAGESIZE)))
**# define REALSIZE_SBLOCK (SIZE_SBLOCK + (PAGESIZE - (SIZE_SBLOCK % PAGESIZE)))
**
**# define FIRSTSIZE_TBLOCK REALSIZE_TBLOCK - SIZE_HBLOCK_HCHUNK
**# define FIRSTSIZE_SBLOCK REALSIZE_SBLOCK - SIZE_HBLOCK_HCHUNK
*/

# define SIZE_TBLOCK 101624
# define SIZE_SBLOCK 12700024

# define REALSIZE_TBLOCK 102400
# define REALSIZE_SBLOCK 12701696

# define FIRSTSIZE_TBLOCK 102352
# define FIRSTSIZE_SBLOCK 12701648


/*
**|-------------------------------------------------|
**|						MASK						|
**|-------------------------------------------------|
*/
/*
**# define FREE (1 << 0)
*/
# define FREE 1

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

t_block							*g_header_block[3];

/*
**|-------------------------------------------------|
**|						FUNCTIONS					|
**|-------------------------------------------------|
*/

t_block							*last_header_block(t_block *begin);
t_chunk							*last_header_chunk(t_chunk *begin);
void							*request_large_block(size_t size);
void							*request_tiny_small_block(int type_block);
void							*get_large_block(size_t size);
void							*handle_tiny_small_block(size_t size);
t_block							*ptr_is_large_block(void *ptr);
t_chunk							*search_in_tiny_small_blocks(
										t_block **block_content_chunk,
										void *ptr);
void							show_alloc_mem();
t_block							*is_large_block(void *ptr);
t_block							*is_tiny_small_block(void *ptr, int type_block);
int								ptr_is_exist_chunk(void *ptr, t_block *block);
void							handle_defragmentation(t_chunk *ptr,
														t_block *block);
void							munmap_block(int type_block, t_block *block);
void							handle_free_chunk(void *ptr, t_block *block);
t_chunk							*get_chunk(int type_block, int size);
void							print_showalloc(void *start_addr,
												void *end_addr,
												long size);

#endif
