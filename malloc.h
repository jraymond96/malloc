/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:07:30 by jraymond          #+#    #+#             */
/*   Updated: 2019/11/20 19:09:22 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define TINY 1024
# define SMALL 10240

/*
//	type => if block free
*/
typedef struct s_data_block	t_data_block;

struct						s_data_block
{
	unsigned int			free : 1;
	int						size_zone;
	t_data_block			*next;
};

typedef struct s_meta_data	t_meta_data;

struct						s_meta_data
{
	int						size_zone;
	t_data_block			*next;
};

typedef struct s_blocks_start	t_blocks_start;

struct						s_block_start
{
	void					*tiny;
	void					*small;
	void					*large;
};

/*
** metadata globale
*/

t_blocks_start *g_meta_datas;
