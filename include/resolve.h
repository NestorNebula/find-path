#ifndef RESOLVE_H
# define RESOLVE_H

# include <square.h>
# include <grid.h>

/*
 * resolve:
 * Finds the shortest path from the starting square to the ending square
 * of the grid.
 * Returns a SquareArray including all the squares used to go to the
 * ending square from the starting square.
 * If an error occurred or if no path could be found, returns a NULL pointer.
 */
SquareArray	*resolve(Grid *grid);

#endif
