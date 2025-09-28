#include <random.h>
#include <stdlib.h>
#include <time.h>

void	init_random(void)
{
	srand(time(NULL));
}

int		random_number(int mod)
{
	return (rand() % mod);
}
