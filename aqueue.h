/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _ARRAY_QUEUE
#define _ARRAY_QUEUE

/**
 * An array based queue containing generic data. The operations that can be 
 * performed on an array list are:
 * 
 * Poll => Removes and returns the item at the front of the queue.
 * Peek => Returns the item at the front of the queue.
 * Offer => Adds an item to the end of the queue.
 * Resize => Doubles the capacity of the queue.
 * Traverse => Traverses the queue of items either forwards or backwards.
 * Clear => Clears all items from the queue.
 * Free => Frees the queue from memory.
 * 
 * @author Philip Diffenderfer
 */
typedef struct
{	
	void** data;
	// The maximum number of items that can be in the queue.
	int capacity;
	// The number of items in the queue
	int size;
	// The index of the head of the queue
	int head;
	// The index of the tail of the queue
	int tail;

} ArrayQueue;

/**
 * Returns a queue of no size allocated to the heap.
 */
ArrayQueue* newArrayQueue(unsigned int capacity);

/**
 * Returns and removes the first item on the queue. If there
 * is no item on the queue then NULL is returned.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The queue to dequeue from.
 */
void* aqueue_poll(ArrayQueue* q);

/**
 * Returns the first item on the queue.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The queue to peek from.
 */
void* aqueue_peek(ArrayQueue* q);

/**
 * Adds an item to the end of a queue.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The queue to enqueue to.
 * @param item => The item to enqueue.
 */
int aqueue_offer(ArrayQueue* q, void* item);

/**
 * Adds an item to the back of an array queue forcefully. If the queue
 * is full this will resize it by 2 times, then add the item on.
 * 
 * Efficiency: O(n) for resize, O(1) for simple offer.
 * 
 * @param q => The queue to dequeue from.
 * @param item => The item to forcefully enqueue.
 */
int aqueue_offerf(ArrayQueue* q, void* item);

/**
 * Resizes an array queue to a new capacity.
 * 
 * Efficiency: O(n)
 * 
 * @param q => The queue to dequeue from.
 * @param capacity => The new capacity of the queue.
 */
void aqueue_resize(ArrayQueue* q, int capacity);

/**
 * Returns whether the queue is empty or not.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The queue to check for emptiness.
 */
int aqueue_isEmpty(ArrayQueue* q);

/**
 * Traverse the queue without affecting it starting at the front of the
 * queue and moving towards the back. Each item traversed will be sent
 * through the process method.
 * 
 * Efficiency: O(n)
 * 
 * @param q => The queue to traverse from front-to-back.
 * @param process => The method that is called every time an item is traversed.
 */
void aqueue_traverseForward(ArrayQueue* q, void (*process)(void* item));

/**
 * Traverse the queue without affecting it starting at the back of the
 * queue and moving towards the front. Each item traversed will be sent
 * through the process method.
 * 
 * Efficiency: O(n)
 * 
 * @param q => The queue to traverse from back-to-front.
 * @param process => The method that is called every time an item is traversed.
 */
void aqueue_traverseBackward(ArrayQueue* q, void (*process)(void* item));

/**
 * Clears the queue of all items.
 * 
 * Efficiency: O(1)
 *
 * @param q => The queue to clear all items from.
 */
int aqueue_clear(ArrayQueue* q);

/**
 * Removes the queue completely from memory.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The queue to clear and free from memory.
 */
void aqueue_free(ArrayQueue* q);

#endif /* _ARRAY_QUEUE */
