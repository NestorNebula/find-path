#include <resolve.h>
#include <queue.h>

/*
 * find_square:
 * Searches for a square with a content of square_content inside the grid
 * pointed by grid and returns its coordinates.
 * If no square can be found returns a square with coordinates corresponding
 * to the size of the grid.
 */
Square		find_square(Grid *grid, char square_content)
{
	Square	square;

	square.row = 0;
	while (square.row < grid->rows)
	{
		square.col = 0;
		while (square.col < grid->cols)
		{
			if (grid->content[square.row][square.col]
				== square_content)
				return (square);
			square.col++;
		}
		square.row++;
	}
	return (square);
}

/*
 * has_square:
 * Searches if a square with coordinates of row and col is already stored
 * in the square array pointed by square_array.
 * If a square is found, returns 1, else returns 0.
 */
int	has_square(SquareArray *square_array, int row, int col)
{
	unsigned int	i;

	i = 0;
	while (i < square_array->len)
	{
		if (square_array->content[i].row == row
			&& square_array->content[i].col == col)
			return (1);
		i++;
	}
	return (0);
}

/*
 * check_square:
 * Checks that row and col are in the limits of the grid, that the
 * corresponding square is a "space" or the ending square
 * and that it isn't already in the path, meaning it isn't already stored in 
 * the square array pointed by square_array.
 * Returns 1 if all the conditions are met, else returns 0.
 */
int		check_square(Grid *grid, SquareArray *square_array, int row, int col)
{
	return (row >= 0 && col >= 0 && row < grid->rows && col < grid->cols
		&& (grid->content[row][col] == SPACE 
			|| grid->content[row][col] == END)
		&& !has_square(square_array, row, col));
}

/*
 * Frees the queue and square array passed as arguments.
 * Also frees the data in the queue items, considering it as square arrays.
 * Returns a NULL pointer.
 */
void		*cleanup(Queue *queue, SquareArray *square_array)
{
	if (queue)
	{
		while (queue->size)
			free_square_array(dequeue(queue));
		free_queue(queue);
	}
	if (square_array)
		free_square_array(square_array);
	return (NULL);
}

/*
 * add_new_path:
 * Creates a copy of the square array pointed by square_array and
 * adds a square with values of row and col to it.
 * Stores the copy as a new path in the queue pointed by queue.
 * If no error occurred, returns 1, else returns 0.
 */
int	add_new_path(Queue *queue, SquareArray *square_array, int row, int col)
{
	SquareArray	*sa_copy;

	sa_copy = square_array_copy(square_array);
	if (!sa_copy)
		return ((long) cleanup(queue, square_array));
	if (!square_array_push(sa_copy, row, col) || !enqueue(queue, sa_copy))
		return ((long) cleanup(queue, square_array));
	return (1);
}

/*
 * handle_next_path:
 * Pops the first path of the queue pointed by queue and 
 * checks if it reached the ending square, represented by end.
 * If it didn't, tries adding an extended path for each direction to the queue
 * pointed by queue and returns a NULL pointer, else returns a pointer to the
 * square array containing the path.
 */
SquareArray	*handle_next_path(Grid *grid, Queue *queue, Square end)
{
	SquareArray	*sa;
	Square		s;

	sa = (SquareArray *) dequeue(queue);
	s = sa->content[sa->len - 1];
	if (s.row == end.row && s.col == end.col)
	{
		cleanup(queue, NULL);
		return (sa);
	}
	if (check_square(grid, sa, s.row - 1, s.col) 
		&& !add_new_path(queue, sa, s.row - 1, s.col))
		return (NULL);
	if (check_square(grid, sa, s.row, s.col + 1)
			&& !add_new_path(queue, sa, s.row, s.col + 1))
		return (NULL);
	if (check_square(grid, sa, s.row + 1, s.col)
			&& !add_new_path(queue, sa, s.row + 1, s.col))
		return (NULL);
	if (check_square(grid, sa, s.row, s.col - 1)
			&& !add_new_path(queue, sa, s.row, s.col - 1))
		return (NULL);
	return (cleanup(NULL, sa));
}

SquareArray	*resolve(Grid *grid)
{
	Queue		*queue;
	SquareArray	*sa;
	Square		square;
	
	square = find_square(grid, START);
	queue = init_queue();
	if (!queue)
		return (NULL);
	sa = init_square_array(2);
	if (!sa)
		return (cleanup(queue, NULL));
	square_array_push(sa, square.row, square.col);
	if (!enqueue(queue, sa))
		return (cleanup(queue, sa));
	square = find_square(grid, END);
	while (queue->size)
	{
		sa = handle_next_path(grid, queue, square);
		if (sa)
			return (sa);
	}
	return (cleanup(queue, NULL));
}
