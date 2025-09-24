#ifndef GRID_H
# define GRID_H

# define START 'S'
# define END 'E'
# define SPACE '.'
# define OBSTACLE 'X'

typedef struct grid {
	char	**content;
	int	rows;
	int	cols;
} Grid;

/*
 * init_grid:
 * Converts the grid_str parameter to a grid and returns it.
 * If grid_str doesn't represent a valid grid or another error occurs,
 * returns a NULL pointer.
 */
Grid	*init_grid(const char *grid_str);

/*
 * print_grid:
 * Prints the grid pointed by grid to stdout.
 */
void	print_grid(Grid *grid);

/*
 * free_grid:
 * Frees the grid pointed by grid.
 */
void	free_grid(Grid *grid);

#endif
