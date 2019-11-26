#include "malloc.h"
#include "libft.h"
#include <stdio.h>

void	print_info(t_data_chunk *elem)
{
	void			*end_malloc;
	t_data_chunk	*tmp;

	tmp = elem;
	if (!elem)
		ft_putstr("Nothing\n");
	else
	{
		while (elem)
		{
			if (! (elem->flags & FREE_CHUNK))
			{
				end_malloc = elem->next != NULL ? elem->next : (void *)((char *)elem + elem->size + SIZEMETADATA);
				printf("%p - %p : %d octects\n", (void *)((char *)elem + SIZEMETADATA), end_malloc, elem->size);
			}
			elem = elem->next;
		}
	}
}

void	show_alloc_mem()
{
	ft_putstr("TINY :\n");
	print_info(g_metas_datas[TINY_BLOCK]);
	ft_putstr("SMALL :\n");
	print_info(g_metas_datas[SMALL_BLOCK]);
	ft_putstr("LARGE :\n");
	print_info(g_metas_datas[LARGE_BLOCK]);
}
