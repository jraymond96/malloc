#include  <stdlib.h>
#include  <stdio.h>

typedef struct s_data_chunk	t_data_chunk;

struct						s_data_chunk
{
	int						free;
	int						size_zone;
	t_data_chunk			*next;
};

int main()
{
	t_data_chunk	toto;
	printf("%lu\n",  sizeof(toto));
	return (0);
}
