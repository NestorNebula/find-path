#ifndef INPUT_H
# define INPUT_H

/*
 * read_input:
 * Reads an input from fd until reaching 
 * a closing parenthese or the EOF character.
 * The input is expected to start with an open parenthese and
 * to end with a closing parenthese. Any other input will be rejected.
 * Returns the input as a string if no error occurred, 
 * else returns a NULL pointer.
 */
char	*read_input(int fd);

/*
 * read_str:
 * Reads a string from the fd stream until encountering last_char.
 * Returns the string read if no error occurred, else returns a NULL pointer.
 */
char	*read_str(int fd, char last_char);

#endif
