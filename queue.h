/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _QUEUE
#define _QUEUE

/**
 * A node for the referenced-based queue. This contains the generic data in the
 * queue as well as the next node in the queue.
 */
typedef struct QueueNode
{
	// The data contained in this node
	void* data;
	// The next node in the queue
	struct QueueNode* next;

} QueueNode;

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
typedef struct 
{	
	// The node for the first process on the queue
	QueueNode* head;
	// The node for the last process on the queue
	QueueNode* tail;
	// The number of processes in the queue
	unsigned int size;

} Queue;

/**
 * Creates a pool of QueueNodes.
 * 
 * @param capacity => The maximum number of nodes that can be pooled.
 */
void pool_queue(unsigned int capacity);

/**
 * Destroys the pool of QueueNodes.
 */
void unpool_queue();

/**
 * Returns a queue of no size allocated to the heap.
 */
Queue* newQueue();

/**
 * Returns and removes the first item on the queue.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The queue to dequeue from.
 */
void* queue_poll(Queue* q);

/**
 * Returns the first item on the queue.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The queue to peek from.
 */
void* queue_peek(Queue* q);

/**
 * Adds an item to the end of a queue.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The queue to enqueue to.
 * @param item => The item to enqueue.
 */
int queue_offer(Queue* q, void* item);

/**
 * Returns whether the queue is empty or not.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The queue to check for emptiness.
 */
int queue_isEmpty(Queue* q);

/**
 * Traverse the queue without affecting it starting at the front of the
 * queue and moving towards the back. Each item traversed will be sent
 * through the process method.
 * 
 * @param q => The queue to traverse from front-to-back.
 * @param process => The method that is called every time an item is traversed.
 */
void queue_traverse(Queue* q, void (*process)(void* item));

/**
 * Clears the queue of all items and removes nodes from memory.
 * 
 * Efficiency: O(n)
 *
 * @param q => The queue to clear all items from.
 */
int queue_clear(Queue* q);

/**
 * Removes the queue completely from memory.
 * 
 * Efficiency: O(n)
 * 
 * @param q => The queue to clear and free from memory.
 */
void queue_free(Queue* q);

#endif /* _QUEUE */
