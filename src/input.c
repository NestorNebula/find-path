#include <input.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * read_char:
 * Reads a character from fd and appends it to the string pointed by input.
 * Returns 1 if a character was read, 0 otherwise.
 */
int	read_char(int fd, char **input, unsigned int len, size_t *size)
{
	char	*resized_input;

	if (len == *size)
	{
		resized_input = realloc(*input, sizeof(char) * (*size * 2 + 2));
		if (!resized_input)
			return (0);
		*input = resized_input;
		*size *= 2;
	}
	if (read(fd, *input + len, 1) > 0)
		return (1);
	return (0);
}

char	*read_input(int fd)
{
	char		*input;
	size_t		size;
	unsigned int	len;

	size = 4;
	input = malloc(sizeof(char) * (size + 2));
	if (!input)
		return (NULL);
	len = 0;
	if (read(fd, input, 1) <= 0 || input[0] != '(')
	{
		while (input[0] != '\n' && read(fd, input, 1) > 0);
		free(input);
		return (NULL);
	}
	while (read_char(fd, &input, len, &size) && input[len] != ')')
		len++;
	if (input[len] != ')')
	{
		free(input);
		return (NULL);
	}
	input[len++] = '\n';
	input[len] = '\0';
	return (input);
}
