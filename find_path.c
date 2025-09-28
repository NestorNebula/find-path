#include <grid.h>
#include <resolve.h>
#include <io.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/*
 * handle_arguments:
 * Checks that the program has a valid number of arguments.
 * Depending on the number of arguments, sets the value pointed by fd.
 * Returns 1 if everything is valid else returns 0.
 */
int	handle_arguments(int argc, char **argv, int *fd)
{
	if (argc > 2)
	{
		print_s("Usage: find_path OR find_path filename.\n", stderr);
		return (0);
	}
	else if (argc == 2)
	{
		*fd = open(argv[1], O_RDONLY);
		if (!*fd)
		{
			print_s("Invalid filename argument: \"", stderr);
			print_s(argv[1], stderr);
			print_s("\".", stderr);
			return (0);
		}
	}
	else
		*fd = stdin;
	return (1);
}

/*
 * create_grid:
 * Reads input from the fd stream and init grid using the input.
 * If the input and the grid are valid, sets the pointer pointed by grid_ptr
 * to point towards the grid and returns 1. Else returns 0.
 */
int	create_grid(Grid **grid_ptr, int fd)
{
	Grid	*grid;
	char	*input;

	input = read_input(fd);
	if (!input)
	{
		print_s("Input isn't in the correct format.\n", stderr);
		return (0);
	}
	grid = init_grid(input);
	free(input);
	if (!grid)
	{
		print_s("Invalid grid.\n", stderr);
		return (0);
	}
	*grid_ptr = grid;
	return (1);
}

/*
 * set_solution:
 * Updates grid pointed by grid so that it contains the path in the
 * square array pointed by sa.
 */
void	set_solution(Grid *grid, SquareArray *sa)
{
	unsigned int	i;
	Square		*s;

	i = 0;
	while (i + 1 < sa->len)
	{
		s = sa->content + i;
		if (s->row < (s + 1)->row)
			grid->content[s->row][s->col] = 'D';
		else if (s->row > (s + 1)->row)
			grid->content[s->row][s->col] = 'U';
		else if (s->col < (s + 1)->col)
			grid->content[s->row][s->col] = 'R';
		else
			grid->content[s->row][s->col] = 'L';
		i++;
	}
}

int	main(int argc, char **argv)
{
	Grid		*grid;
	SquareArray	*sa;
	int		fd;

	if (!handle_arguments(argc, argv, &fd) || !create_grid(&grid, fd))
		return (0);
	if (argc > 1)
		close(fd);
	print_s("\nGrid:\n", stdout);
	print_grid(grid);
	sa = resolve(grid);
	if (!sa)
		print_s("\nGrid couldn't be solved.\n", stderr);
	else
	{
		set_solution(grid, sa);
		print_s("\nShortest path:\n", stdout);
		print_grid(grid);
		free_square_array(sa);
	}
	free_grid(grid);
	return (0);
}
