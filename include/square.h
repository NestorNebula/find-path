#ifndef SQUARE_H
# define SQUARE_H

# include <stddef.h>

typedef struct square {
	int	row;
	int	col;
} Square;

typedef struct square_array {
	Square			*content;
	size_t			size;
	unsigned int	len;
} SquareArray;

/*
 * init_square_array:
 * Initializes a SquareArray with a size of size.
 * Returns a pointer to the SquareArray if no error occurred,
 * else returns a NULL pointer.
 */
SquareArray	*init_square_array(size_t size);

/*
 * square_array_push:
 * Adds a Square with values of row and col to the SquareArray
 * pointed by square_array.
 * Returns 1 if the Square was added properly, else returns 0.
 */
int			square_array_push(SquareArray *square_array, int row, int col);

/*
 * square_array_pop:
 * Removes the last Square from the SquareArray pointed by square_array.
 * Returns a Square similar to the Square popped.
 * A check that the SquareArray isn't empty should be done before calling
 * this function, else the values in the Square returned are undefined.
 */
Square		square_array_pop(SquareArray *square_array);

/*
 * square_array_copy:
 * Creates a copy of the SquareArray pointed by square_array and 
 * returns a pointer to it.
 * If an error occurred, returns a NULL pointer instead.
 */
SquareArray	*square_array_copy(SquareArray *square_array);

/*
 * free_square_array:
 * Frees the SquareArray pointed by square_array and its content.
 */
void		free_square_array(SquareArray *square_array);

#endif
