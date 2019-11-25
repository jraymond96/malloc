#include "malloc.h"
#include "libft.h"
#include <stdio.h>

void	print_info(t_data_chunk *elem)
{
	void	*end_malloc;

	if (!elem)
		ft_putstr("Nothing\n");
	else
	{
		while (elem)
		{
			end_malloc = elem->next != NULL ? elem->next : (void *)((char *)elem + elem->size + SIZEMETADATA);
			printf("%p - %p\n", (void *)((char *)elem + SIZEMETADATA), end_malloc);
			elem = elem->next;
		}
	}
}

void	show_alloc_mem()
{
	ft_putstr("TINY :\n");
	print_info(g_metas_datas[TINY_ZONE]);
	ft_putstr("SMALL :\n");
	print_info(g_metas_datas[SMALL_ZONE]);
	ft_putstr("LARGE :\n");
	print_info(g_metas_datas[LARGE_ZONE]);
}
