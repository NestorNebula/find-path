#include <output.h>
#include <unistd.h>

void	print_c(char c, int fd)
{
	write(fd, &c, 1);
}

void	print_u(unsigned int u, int fd)
{
	if (u >= 10)
		print_u(u / 10, fd);
	print_c('0' + u % 10, fd);
}

void	print_s(const char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	write(fd, s, i);
}
