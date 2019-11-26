#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>

int main()
{
	int	i;
	int	y;

	i = 3;
	y = 0;

	y = y | (1 << 1);

	printf("y : %d\n", y);
	if (i & (1 << 0))
		printf("1 exist\n");
	else
		printf("1 didn't exist\n");
	if (i & (1 << 1))
		printf("2 exist\n");
	else
		printf("2 didn't exist\n");
	return (0);
}
