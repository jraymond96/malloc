#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>

typedef struct s_data_chunk	t_data_chunk;

struct						s_data_chunk
{
	int						free;
	int						size_zone;
	t_data_chunk			*next;
};

int main()
{
	char	*toto;

	toto = (char *)malloc(1000);
	printf("%p\n",  toto);
	toto = toto + 100;
	printf("%p\n",  toto);
	return (0);
}
