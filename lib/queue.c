/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

/**
 * A referenced based queue containing generic data. The operations that can be
 * performed on an array list are:
 * 
 * Poll => Removes and returns the item at the front of the queue.
 * Peek => Returns the item at the front of the queue.
 * Offer => Adds an item to the end of the queue.
 * Traverse => Traverses the queue of items either forwards.
 * Clear => Clears all items from the queue.
 * Free => Frees the queue from memory.
 * 
 * @author Philip Diffenderfer
 */

#include "util.h"
#include "queue.h"

/**
 * A pool is a stack like structure that can pop and push QueueNodes.
 * If there are no QueueNodes to pop and a request is made then the 
 * pool will allocate a QueueNode on the spot. A pool is restricted
 * by a maximum capcity.
 */
typedef struct 
{
	// The current number of nodes available for unpooling.
	int size;
	// The maximum number of nodes that can be pooled.
	int capacity;
	// The array of node pointers for pooling/unpooling.
	QueueNode** nodes;

} Pool;


// The pool to use for any Queue's nodes.
Pool* pool;

// Creates a pool of QueueNodes.
void pool_queue(unsigned int capacity)
{
	pool = alloc(Pool, 1);

	pool->capacity = capacity;
	pool->size = 0;
	pool->nodes = alloc(QueueNode*, capacity);
}

// Destroys the pool of QueueNodes.
void unpool_queue()
{
	if (pool == NULL)
		return;
	
	int i;
	for (i = 0; i < pool->size; i++)
		free(pool->nodes[i]);

	free(pool->nodes);
	free(pool);

	pool = NULL;
}

// Returns a node from the pool or allocates a new one.
QueueNode* pop_QueueNode()
{
	if (pool == NULL)
		return alloc(QueueNode, 1);

	QueueNode* node;

	if (pool->size == 0)
	{
		node = alloc(QueueNode, 1);
	}
	else
	{
		pool->size--;
		node = pool->nodes[pool->size];
		pool->nodes[pool->size] = NULL;
	}

	return node;
}

// Puts the node on the pool if there is space.
void push_QueueNode(QueueNode* node)
{
	// If the node passed in is null just exit
	if (node == NULL)
		return;
	// If the pooling isn't supported then just free the node from memory.
	else if (pool == NULL)
	{
		free(node);	
		return;
	}
	// If the pool exists but is filled then exit.
	else if (pool->size == pool->capacity)
		return;

	node->data = NULL;
	node->next = NULL;
	pool->nodes[pool->size++] = node;
}

// Returns a queue with no size allocated to the heap.
Queue* newQueue()
{
	Queue* q = alloc(Queue, 1);

	q->head = NULL;
	q->tail = NULL;
	q->size = 0;

	return q;
}

// Returns and removes the first process on the queue.
void* queue_poll(Queue* q)
{
	// Check that the queue passed in isn't empty
	if (queue_isEmpty(q))
		return NULL;
	
	// Grab the process from the front
	QueueNode* first = q->head;

	void* data = first->data;
	// Remove the node from the front
	q->head = first->next;
	// Try to pool the node if there's a pool
	push_QueueNode(first);
	// Succesful poll, decrease size counter
	q->size--;

	// Clean up the empty list
	if (q->size == 0)
		q->head = q->tail = NULL;

	return data;
}

// Returns the first process on the queue.
void* queue_peek(Queue* q)
{
	// Check that the queue passed in isn't null
	if (q->head == NULL)
		return NULL;

	return q->head->data;
}

// Adds a process to the end of a queue.
int queue_offer(Queue* q, void* item)
{
	// Check that the queue passed in isn't null
	if (item == NULL)
		return false;

	QueueNode* node = pop_QueueNode();
	node->data = item;
	node->next = NULL;

	// If the queue is empty then set the head and tail
	if (q->head == NULL && q->tail == NULL)
	{
		q->head = q->tail = node;
	}
	// If there is a tail add it on to the end.
	else
	{
		q->tail->next = node;
		q->tail = node;
	}
	// Succesful offer, increase size counter
	q->size++;

	return true;
}

// Returns whether the queue is empty or not.
int queue_isEmpty(Queue* q)
{
	return (q->size == 0);
}

// Traverse the queue without affecting it starting at the front of the
// queue and moving towards the back. Each item traversed will be sent
// through the process method.
void queue_traverse(Queue* q, void (*process)(void* item))
{
	QueueNode* current = q->head;

	while (current != NULL)
	{
		process(current->data);
		current = current->next;
	}
}

// Clears the queue of all processes and removes nodes from memory.
int queue_clear(Queue* q)
{
	// If the queue is empty then we can't clear it.
	if (q->size == 0)
		return false;

	QueueNode* current = q->head;
	QueueNode* previous;

	q->head = NULL;
	q->tail = NULL;

	while (current != NULL)
	{
		previous = current;
		current = current->next;
		push_QueueNode(previous);
	}

	q->size = 0;

	return true;
}

// Removes the queue from memory.
void queue_free(Queue* q)
{
	// Check that the queue passed in isn't null
	if (q == NULL)
		return;

	// Free all nodes from memory, then the queue itself
	queue_clear(q);
	free(q);
}
