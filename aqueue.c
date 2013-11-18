/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

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

#include "util.h"
#include "aqueue.h"

// Returns a queue of no size allocated to the heap.
ArrayQueue* newArrayQueue(unsigned int capacity)
{
	ArrayQueue* q = alloc(ArrayQueue, 1);
	
	// Determine the next size thats a power of 2
	int actual = 1;
	while (actual < capacity)
		actual <<= 1;

	q->capacity = actual;
	q->size = 0;
	q->head = 0;
	q->tail = -1;
	q->data = alloc(void*, actual);

	return q;
}

// Returns and removes the first item on the queue.
void* aqueue_poll(ArrayQueue* q)
{
	if (q->size == 0)
		return NULL;

	void* data = q->data[q->head];
	q->data[q->head] = NULL;
	q->head = (q->head + 1) & (q->capacity - 1);
	q->size--;

	return data;
}

// Returns the first item on the queue.
void* aqueue_peek(ArrayQueue* q)
{
	if (q->size == 0)
		return NULL;

	return q->data[q->head];
}

// Adds an item to the end of a queue.
int aqueue_offer(ArrayQueue* q, void* item)
{
	// Don't push it if the queue or item given is null.
	if (item == NULL)
		return false;

	q->tail = (q->tail + 1) & (q->capacity - 1);
	q->data[q->tail] = item;
	q->size++;

	return true;
}

// Adds an item to the end of a queue.
int aqueue_offerf(ArrayQueue* q, void* item)
{
	// Don't push it if the queue or item given is null.
	if (item == NULL)
		return false;
	// If we met the maximum capacity then double its size
	if (q->size == q->capacity)
		aqueue_resize(q, q->capacity << 1);

	q->tail = (q->tail + 1) & (q->capacity - 1);
	q->data[q->tail] = item;
	q->size++;

	return true;
}

// Resizes an array queue to a new capacity.
void aqueue_resize(ArrayQueue* q, int capacity)
{
	if (capacity < 1)
		return;

	void** old = q->data;
	
	// The size can't be larger then the new capacity
	q->size = min(q->size, capacity);
	q->data = alloc(void*, capacity);

	// Copy it over to the new array
	int actual = 0;
	int index = q->head;
	while (actual < q->size)
	{
		q->data[actual] = old[index];

		index = (index + 1) & (q->capacity - 1);
		actual++;
	}
	// Free the old queue data pointer from memory.
	free(old);

	// Now that all data has been transfered reset the head, tail, and 
	// the actual capacity of the array queue now.
	q->head = 0;
	q->tail = q->size - 1;
	q->capacity = capacity;
}

// Returns whether the queue is empty or not.
int aqueue_isEmpty(ArrayQueue* q)
{
	return (q->size == 0);
}

// Traverse the queue without affecting it starting at the front of the
// queue and moving towards the back. Each item traversed will be sent
// through the process method.
void aqueue_traverseForward(ArrayQueue* q, void (*process)(void* item))
{
	if (q->size == 0)
		return;

	int index = q->head;
	int mod = (q->capacity - 1);
	int i = 0;

	while (i < q->size)
	{
		process(q->data[index]);
		index = (index + 1) & mod;
		i++;
	}
}

// Traverse the queue without affecting it starting at the back of the
// queue and moving towards the front. Each item traversed will be sent
// through the process method.
void aqueue_traverseBackward(ArrayQueue* q, void (*process)(void* item))
{
	if (q->size == 0)
		return;

	int index = q->tail;
	int mod = (q->capacity - 1);
	int i = 0;

	while (i < q->size)
	{
		process(q->data[index]);
		index = (index - 1) & mod;
		i++;
	}
}

// Clears the queue of all items.
int aqueue_clear(ArrayQueue* q)
{
	if (q->size == 0)
		return false;

	q->head = 0;
	q->tail = -1;

	return true;
}

// Removes the queue completely from memory.
void aqueue_free(ArrayQueue* q)
{
	if (q == NULL)
		return;

	aqueue_clear(q);
	free(q->data);
	free(q);
}
