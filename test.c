#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"malloc.h"
# define MASK (1 << i)
/*size_t	my_malloc_good_size(size_t size)
{
	size_t	modulo;

	if (size <= 16)
		return (16);
}
*/

typedef struct	s_bad t_bad;

struct			s_bad
{
	int		i;
	double	y;
	char	x[3];
	char	c;
};

typedef struct	s_good t_good;

struct			s_good
{
	double	y;
	int		i;
	char	x[3];
	char	c;
};

void	titi(t_good *toto)
{
	t_good	new;

	new.y = 1;
	new.i = 2;
	new.x[0] = 'c';
	new.x[1] = 'i';
	new.x[2] = 'o';
	new.y = 'c';

	toto = malloc(sizeof(t_good));
	memcpy(toto, &new, sizeof(t_good));
}

int main(int argc, char **argv)
{
//	int	i;
//	int	t;
	char	*toto;


	toto = malloc(10);

	toto[0] = 'c';
	toto[1] = 'h';
	toto[2] = 'a';
	toto[3] = 'r';
	toto[4] = 'l';
	toto[5] = 'i';
	toto[6] = 'e';
	toto[7] = '\0';

	ft_putstr(toto);
/*	toto = NULL;
	titi(toto);
	printf("toto.x : %c", toto->x[0]);
	printf("bad: %zu\n", sizeof(t_bad));
	printf("good: %zu\n", sizeof(t_good));
	printf("size_t: %zu\n", sizeof(size_t));
	printf("t_block: %zu\n", sizeof(t_block));
	printf("t_chunk: %zu\n", sizeof(t_chunk));
	return (0);
	if (argc != 2)
	{
		printf("wrong arguments !\n");
		return (0);
	}
	i = atoi(argv[1]);
	printf("lib: %d\n", malloc_good_size(i));
//	printf("mylib: %zu\n", my_malloc_good_size(i));*/
	return (0);
}
