#include <grid.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * check_grid:
 * Checks if grid_str is a valid string grid, meaning it could be resolved.
 * If it is, returns 1 and sets the values pointed by rows and cols to 
 * the number of rows and columns in the grid, else returns 0.
 */
int	check_grid(const char *grid_str, int *rows, int *cols)
{
	int	i;
	int	start_end;

	start_end = 0;
	*rows = 0;
	i = 0;
	while (*grid_str != '\0')
	{
		if (*grid_str == '\n')
		{
			if ((*rows)++ && i != *cols)
				return (0);
			*cols = i;
			i = -1;
		}
		else if (*grid_str == START && !(start_end & 1))
			start_end ^= 1;
		else if (*grid_str == END && !(start_end & 2))
			start_end ^= 2;
		else if (*grid_str != SPACE && *grid_str != OBSTACLE)
			return (0);
		i++;
		grid_str++;
	}
	return (!i && *rows && *cols && start_end == 3);
}

/*
 * malloc_grid:
 * Initializes a grid with rows and cols.
 * Returns a pointer to the initialized grid if no error occurred,
 * else returns a NULL pointer.
 */
Grid	*malloc_grid(int rows, int cols)
{
	Grid	*grid;

	grid = malloc(sizeof(Grid));
	if (!grid)
		return (NULL);
	grid->content = malloc(sizeof(char *) * rows);
	if (!grid->content)
	{
		free(grid);
		return (NULL);
	}
	while (grid->rows < rows)
	{
		grid->content[grid->rows] = malloc(sizeof(char) * cols);
		if (!grid->content[grid->rows])
		{
			free_grid(grid);
			return (NULL);
		}
		grid->rows++;
	}
	grid->cols = cols;
	return (grid);
}

/*
 * Copies the content of grid_str in grid.
 * grid_str should be validated before calling this function, using check_grid.
 */
void	copy_grid(Grid *grid, const char *grid_str)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (*grid_str != '\0')
	{
		if (*grid_str == '\n')
		{
			row++;
			col = 0;
		}
		else
			grid->content[row][col++] = *grid_str;
		grid_str++;
	}
}

Grid	*init_grid(const char *grid_str)
{
	Grid	*grid;
	int	rows;
	int	cols;

	if (!check_grid(grid_str, &rows, &cols))
		return (NULL);
	grid = malloc_grid(rows, cols);
	if (!grid)
		return (NULL);
	copy_grid(grid, grid_str);
	return (grid);
}

void	print_grid(Grid *grid)
{
	int	i;

	i = 0;
	while (i < grid->rows)
	{
		write(1, grid->content[i++], grid->cols);	
		write(1, "\n", 1);
	}
}

void	free_grid(Grid *grid)
{
	int	i;
	
	i = 0;
	while (i < grid->rows)
		free(grid->content[i++]);
	free(grid->content);
	free(grid);
}
