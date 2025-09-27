#ifndef OUTPUT_H
# define OUTPUT_H

/*
 * print_c:
 * Prints the character c to the fd stream.
 */
void	print_c(char c, int fd);

/*
 * print_u:
 * Prints u, an unsigned integer, to the fd stream.
 */
void	print_u(unsigned int u, int fd);

/*
 * print_s:
 * Prints the string s to the fd stream.
 */
void	print_s(const char *s, int fd);

#endif
