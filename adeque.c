/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#include "util.h"
#include "adeque.h"

/**
 * An array based deque containing generic data. The operations that can be 
 * performed on a deque are:
 * 
 * PopFirst => Removes and returns the item on the front of the deque.
 * PopLast => Removes and returns the item at the end of the deque.
 * PeekFirst => Returns the item on the front of the deque.
 * PeekLast => Returns the item at the end of the deque.
 * PushFirst => Adds an item to the front of the deque.
 * PushLast => Adds an item to the end of the deque.
 * Resize => Doubles the capacity of the deque.
 * Traverse => Traverses the deque of items either forwards or backwards.
 * Clear => Clears all items from the deque.
 * Free => Frees the deque from memory.
 * 
 * @author Philip Diffenderfer
 */

// Returns an empty deque allocated to the heap.
ArrayDeque* newArrayDeque(unsigned int capacity)
{
	ArrayDeque* q = alloc(ArrayDeque, 1);
	
	// Determine the next size thats a power of 2
	unsigned int actual = 1;
	while (actual < capacity)
		actual <<= 1;

	q->capacity = actual;
	q->size = 0;
	q->head = 0;
	q->tail = -1;
	q->data = alloc(void*, actual);

	return q;
}

// Returns and removes the first item on the deque. If there
// is no item on the deque then NULL is returned.
void* adeque_popFirst(ArrayDeque* q)
{
	if (q->size == 0)
		return NULL;

	void* data = q->data[q->head];
	q->data[q->head] = NULL;
	q->head = (q->head + 1) & (q->capacity - 1);
	q->size--;

	return data;
}

// Returns and removes the last item on the deque. If there
// is no item on the deque then NULL is returned.
void* adeque_popLast(ArrayDeque* q)
{
	if (q->size == 0)
		return NULL;

	void* data = q->data[q->tail];
	q->data[q->tail] = NULL;
	q->tail = (q->tail - 1) & (q->capacity - 1);
	q->size--;

	return data;
}

// Returns the first item on the deque.
void* adeque_peekFirst(ArrayDeque* q)
{
	if (q->size == 0)
		return NULL;

	return q->data[q->head];
}

// Returns the last item on the deque.
void* adeque_peekLast(ArrayDeque* q)
{
	if (q->size == 0)
		return NULL;

	return q->data[q->tail];
}

// Returns the item at the specified index in the deque.
void* adeque_peek(ArrayDeque* q, unsigned int index)
{
	if (index < 0 || index >= q->size)
		return NULL;

	index = (q->head + index) & (q->capacity - 1);

	return q->data[index];
}

// Adds an item to the front of a deque.
int adeque_pushFirst(ArrayDeque* q, void* item)
{
	if (q->size == q->capacity)
		return false;
	
	q->head = (q->head - 1) & (q->capacity - 1);
	q->data[q->head] = item;
	q->size++;

	return true;
}

// Adds an item to the end of a deque.
int adeque_pushLast(ArrayDeque* q, void* item)
{
	if (q->size == q->capacity)
		return false;
	
	q->tail = (q->tail + 1) & (q->capacity - 1);
	q->data[q->tail] = item;
	q->size++;

	return true;
}

// Adds an item to the front of the deque forcefully. If the deque
// is full this will resize it by 2 times, then add the item on.
void adeque_pushfFirst(ArrayDeque* q, void* item)
{
	// If the deque reached maximum capacity then double the capacity
	if (q->size == q->capacity)
		adeque_resize(q, q->capacity << 1);
	
	q->head = (q->head - 1) & (q->capacity - 1);
	q->data[q->head] = item;
	q->size++;
}

// Adds an item to the back of the deque forcefully. If the deque
// is full this will resize it by 2 times, then add the item on.
void adeque_pushfLast(ArrayDeque* q, void* item)
{
	// If the deque reached maximum capacity then double the capacity
	if (q->size == q->capacity)
		adeque_resize(q, q->capacity << 1);
	
	q->tail = (q->tail + 1) & (q->capacity - 1);
	q->data[q->tail] = item;
	q->size++;
}

// Resizes an deque to a new capacity.
void adeque_resize(ArrayDeque* q, unsigned int capacity)
{
	// Don't bother resizing to the same capacity
	if (capacity == q->capacity)
		return;

	// Find the next power of 2 number after capacity
	unsigned int actual = 1;
	while (actual < capacity)
		actual <<= 1;

	// Calculate the old and new capacities
	unsigned int old = q->capacity;
	unsigned int new = max(actual, q->size);

	q->capacity = new;

	int n, o, i = 0;
	// If the deque was resized up then start at the head
	if (old < new)
	{
		// Resize the data BEFORE to have the space
		q->data = realloc(q->data, void*, new);

		while (i < q->size)
		{
			n = (i + q->head) & (new - 1);
			o = (i + q->head) & (old - 1);
			q->data[n] = q->data[o];
			i++;
		}
	}
	// If the deque was sized down then start at the tail
	else
	{
		while (i < q->size)
		{
			n = (q->tail - i) & (new - 1);
			o = (q->tail - i) & (old - 1);
			q->data[n] = q->data[o];
			i++;
		}
		// Resize the data AFTER so no data is cut off.
		q->data = realloc(q->data, void*, new);
	}
}

// Returns whether the deque is empty or not.
int adeque_isEmpty(ArrayDeque* q)
{
	return (q->size == 0);
}

// Traverse the deque without affecting it starting at the front of the
// deque and moving towards the back. Each item traversed will be sent
// through the process method.
void adeque_traverseForward(ArrayDeque* q, void (*process)(void* item))
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

// Traverse the deque without affecting it starting at the back of the
// deque and moving towards the front. Each item traversed will be sent
// through the process method.
void adeque_traverseBackward(ArrayDeque* q, void (*process)(void* item))
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

// Clears the deque of all items.
int adeque_clear(ArrayDeque* q)
{
	if (q->size == 0)
		return false;

	q->size = 0;
	q->head = 0;
	q->tail = -1;	

	return true;
}

// Removes the deque completely from memory.
void adeque_free(ArrayDeque* q)
{
	if (q == NULL)
		return;

	adeque_clear(q);
	free(q->data);
	free(q);
}

#endif /* _ARRAY_DEQUE */
