#include <square.h>
#include <stdlib.h>

SquareArray	*init_square_array(size_t size)
{
	SquareArray	*square_array;

	square_array = malloc(sizeof(SquareArray));
	if (!square_array)
		return (NULL);
	square_array->content = malloc(sizeof(Square) * size);
	if (!square_array->content)
	{
		free(square_array);
		return (NULL);
	}
	square_array->size = size;
	square_array->len = 0;
	return (square_array);
}

int		square_array_push(SquareArray *square_array, int row, int col)
{
	Square	*resized_content;

	if (square_array->len == square_array->size)
	{
		resized_content = 
			realloc(square_array->content,
				sizeof(Square) * square_array->size * 2);
		if (!resized_content)
			return (0);
		square_array->content = resized_content;
		square_array->size *= 2;
	}
	square_array->content[square_array->len].row = row;
	square_array->content[square_array->len].col = col;
	square_array->len++;
	return (1);
}

Square		square_array_pop(SquareArray *square_array)
{
	if (square_array->len)
		square_array->len--;
	return (square_array->content[square_array->len]);
}

SquareArray	*square_array_copy(SquareArray *square_array)
{
	SquareArray	*sa_copy;
	unsigned int	i;

	sa_copy = init_square_array(square_array->size);
	if (!sa_copy)
		return (NULL);
	i = 0;
	while (i < square_array->len)
	{
		square_array_push(sa_copy, square_array->content[i].row, 
			square_array->content[i].col);
		i++;
	}
	return (sa_copy);
}

void		free_square_array(SquareArray *square_array)
{
	free(square_array->content);
	free(square_array);
}
