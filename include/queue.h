#ifndef QUEUE_H
# define QUEUE_H

# include <stddef.h>

typedef struct queue_item QueueItem;

typedef struct queue {
	QueueItem	*head;
	QueueItem	*tail;
	size_t		size;
} Queue;

/*
 * init_queue:
 * Initializes a queue and returns a pointer to it.
 * Returns a NULL pointer if an error occurred.
 */
Queue	*init_queue(void);

/*
 * enqueue:
 * Adds the data pointed by data to the end of the queue pointed by queue.
 * Returns 1 if the data was added properly to the queue, else returns 0.
 */
int		enqueue(Queue *queue, void *data);

/*
 * dequeue:
 * Removes the head of the queue pointed by queue and returns a pointer to
 * the data stored inside of it.
 * If the queue is empty, returns a NULL pointer instead.
 */
void	*dequeue(Queue *queue);

/*
 * free_queue:
 * Frees the memory taken by the queue pointed by queue.
 */
void	free_queue(Queue *queue);

#endif
