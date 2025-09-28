#include <grid.h>
#include <square.h>
#include <io.h>
#include <random.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/*
 * Checks that a filename was provided to the program and opens a stream
 * to write into it and updates the value pointed by fd accordingly.
 * Returns 1 if no error occurred, else returns 0.
 */
int	handle_arguments(int argc, char **argv, int *fd)
{
	if (argc != 2)
	{
		print_s("Usage: gen_grid filename.\n", stderr);
		return (0);
	}
	*fd = open(argv[1], O_CREAT | O_WRONLY, 0644);
	if (!*fd)
	{
		print_s("Couldn't open file \"", stderr);
		print_s(argv[1], stderr);
		print_s("\".\n", stderr);
		return (0);
	}
	return (1);
}

/*
 * set_param:
 * Reads the user input from stdin, updating the value pointed by param_ptr.
 * Sets the value to def if the updated value wasn't between min and max.
 * Returns 1 if the value was set correctly, else returns 0.
 */
int	set_param(int *param_ptr, int min, int max, int def)
{
	char	*input;

	input = read_str(stdin, '\n');
	if (!input)
		return (0);
	*param_ptr  = atoi(input);
	if (*param_ptr < min || *param_ptr > max)
		*param_ptr = def;
	return (1);
}

/*
 * get_params:
 * Prompts the user for the parameters needed by the program,
 * updating the value pointed by each pointer.
 * Returns 1 if every value could be set, else returns 0.
 */
int	get_params(int *rows, int *cols, int *obs_percentage)
{
	print_s("Rows: ", stdout);
	if (!set_param(rows, 1, 100, 10))
		return (0);
	print_s("Cols: ", stdout);
	if (!set_param(cols, 1, 100, 10))
		return (0);
	print_s("Obstacles percentage: ", stdout);
	if (!set_param(obs_percentage, 0, 100, 25))
		return (0);
	return (1);
}

/*
 * set_start_end:
 * Randomly assigns row and col values to squares pointed by start and end,
 * using the values of rows and cols as modulo.
 * Returns 1 if the values were correctly assigned, else returns 0.
 */
int	set_start_end(Square *start, Square *end, int rows, int cols)
{
	if (rows <= 1 && cols <= 1)
		return (0);
	start->row = -1;
	start->col = -1;
	end->row = -1;
	end->col = -1;
	while (start->row == end->row && start->col == end->col)
	{
		start->row = random_number(rows);
		start->col = random_number(cols);
		end->row = random_number(rows);
		end->col = random_number(cols);
	}
	return (1);
}

/*
 * write_square:
 * Writes a character in the stream pointed by fd depending on the values
 * of s, start_end and obs_percentage.
 */
void	write_square(int fd, Square s, Square *start_end, int obs_percentage)
{
	if (s.row == start_end[0].row && s.col == start_end[0].col)
		print_c(START, fd);
	else if (s.row == start_end[1].row && s.col == start_end[1].col)
		print_c(END, fd);
	else if (random_number(100) >= obs_percentage)
		print_c(SPACE, fd);
	else
		print_c(OBSTACLE, fd);
}

/*
 * write_grid:
 * Writes a grid in the fd stream using the rows, cols and obs_percentage
 * parameters.
 * Returns 1 if the grid was created properly, else returns 0.
 */
int	write_grid(int fd, int rows, int cols, int obs_percentage)
{
	Square	square;
	Square	start_end[2];

	if (!set_start_end(start_end, start_end + 1, rows, cols))
		return (0);
	print_c('(', fd);
	square.row = 0;
	while (square.row < rows)
	{
		square.col = 0;
		while (square.col < cols)
		{
			write_square(fd, square, start_end, obs_percentage);
			square.col++;
		}
		if (++square.row != rows)
			print_c('\n', fd);
	}
	print_c(')', fd);
	return (1);
}

int	main(int argc, char **argv)
{
	int	fd;
	int	rows;
	int	cols;
	int	obs_percentage;

	if (!handle_arguments(argc, argv, &fd))
		return (0);
	if (!get_params(&rows, &cols, &obs_percentage))
		return (0);
	init_random();
	if (!write_grid(fd, rows, cols, obs_percentage))
		print_s("Grid couldn't be created.\n", stderr);
	else
		print_s("Grid created successfully.\n", stdout);
	close(fd);
	return (0);
}
