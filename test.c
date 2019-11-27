#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>

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

int main(int argc, char **argv)
{
	int	i;
	int	t;

	t = 10000000;
	i = 1;
	while (t)
	{
		i *= -1;
		i *= -1;
/*		i |= (1 << 31);
		i ^= (1 << 31);*/
		t--;
	}
	/*
	if (i & (1 << 31))
		printf("OK\n");
	else
		printf("KO\n");*/
	return (0);
	printf("bad: %zu\n", sizeof(t_bad));
	printf("good: %zu\n", sizeof(t_good));
	return (0);
	if (argc != 2)
	{
		printf("wrong arguments !\n");
		return (0);
	}
	i = atoi(argv[1]);
	printf("lib: %d\n", malloc_good_size(i));
//	printf("mylib: %zu\n", my_malloc_good_size(i));
	return (0);
}
