#include <queue.h>
#include <stdlib.h>

typedef struct queue_item {
	void			*data;
	struct queue_item	*next;
} QueueItem;

Queue	*init_queue(void)
{
	Queue	*queue;

	queue = malloc(sizeof(Queue));
	if (!queue)
		return (NULL);
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
	return (queue);
}

int	enqueue(Queue *queue, void *data)
{
	QueueItem	*item;

	item = malloc(sizeof(QueueItem));
	if (!item)
		return (0);
	item->data = data;
	item->next = NULL;
	if (!queue->size)
	{
		queue->head = item;
		queue->tail = item;
	}
	else
	{
		queue->tail->next = item;
		queue->tail = item;
	}
	queue->size++;
	return (1);
}

void	*dequeue(Queue *queue)
{
	QueueItem	*item;
	void		*data;

	if (!queue->size)
		return (NULL);
	item = queue->head;
	queue->head = queue->head->next;
	queue->size--;
	data = item->data;
	free(item);
	return (data);
}

void	free_queue(Queue *queue)
{
	free(queue);
}
