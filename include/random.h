#ifndef RANDOM_H
# define RANDOM_H

/*
 * init_random:
 * Initializes the random list of numbers.
 * This function must be called before calling random_number, 
 * else random_number will always return the same numbers in the same order.
 */
void	init_random(void);

/*
 * random_number:
 * Returns a random number modulo mod.
 */
int		random_number(int mod);

#endif
