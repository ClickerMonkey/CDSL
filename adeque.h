/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _ARRAY_DEQUE
#define _ARRAY_DEQUE

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
typedef struct
{	
	void** data;
	// The maximum number of items that can be in the deque.
	int capacity;
	// The number of items in the deque.
	int size;
	// The index of the head of the deque.
	int head;
	// The index of the tail of the deque.
	int tail;

} ArrayDeque;

/**
 * Returns an empty deque allocated to the heap.
 * 
 * @param capacity => The maximum initial size of the deque.
 */
ArrayDeque* newArrayDeque(unsigned int capacity);

/**
 * Returns and removes the first item on the deque. If there
 * is no item on the deque then NULL is returned.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The deque to pop from.
 */
void* adeque_popFirst(ArrayDeque* q);

/**
 * Returns and removes the last item on the deque. If there
 * is no item on the deque then NULL is returned.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The deque to pop from.
 */
void* adeque_popLast(ArrayDeque* q);

/**
 * Returns the first item on the deque.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The deque to peek from.
 */
void* adeque_peekFirst(ArrayDeque* q);

/**
 * Returns the last item on the deque.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The deque to peek from.
 */
void* adeque_peekLast(ArrayDeque* q);

/**
 * Returns the item at the specified index in the deque.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The deque to peek from.
 */
void* adeque_peek(ArrayDeque* q, unsigned int index);

/**
 * Adds an item to the front of a deque.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The queue to add to.
 * @param item => The item to add.
 */
int adeque_pushFirst(ArrayDeque* q, void* item);

/**
 * Adds an item to the end of a deque.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The deque to add to.
 * @param item => The item to add.
 */
int adeque_pushLast(ArrayDeque* q, void* item);

/**
 * Adds an item to the front of the deque forcefully. If the deque
 * is full this will resize it by 2 times, then add the item on.
 * 
 * Efficiency: O(n) for resize, O(1) for simple offer.
 * 
 * @param q => The deque to add to.
 * @param item => The item to forcefully add.
 */
void adeque_pushfFirst(ArrayDeque* q, void* item);

/**
 * Adds an item to the back of the deque forcefully. If the deque
 * is full this will resize it by 2 times, then add the item on.
 * 
 * Efficiency: O(n) for resize, O(1) for simple offer.
 * 
 * @param q => The deque to add to.
 * @param item => The item to forcefully add.
 */
void adeque_pushfLast(ArrayDeque* q, void* item);

/**
 * Resizes an deque to a new capacity.
 * 
 * Efficiency: O(n)
 * 
 * @param q => The deque to resize.
 * @param capacity => The new capacity of the deque.
 */
void adeque_resize(ArrayDeque* q, unsigned int capacity);

/**
 * Returns whether the deque is empty or not.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The deque to check for emptiness.
 */
int adeque_isEmpty(ArrayDeque* q);

/**
 * Traverse the deque without affecting it starting at the front of the
 * deque and moving towards the back. Each item traversed will be sent
 * through the process method.
 * 
 * Efficiency: O(n)
 * 
 * @param q => The deque to traverse from front-to-back.
 * @param process => The method that is called every time an item is traversed.
 */
void adeque_traverseForward(ArrayDeque* q, void (*process)(void* item));

/**
 * Traverse the deque without affecting it starting at the back of the
 * deque and moving towards the front. Each item traversed will be sent
 * through the process method.
 * 
 * Efficiency: O(n)
 * 
 * @param q => The deque to traverse from back-to-front.
 * @param process => The method that is called every time an item is traversed.
 */
void adeque_traverseBackward(ArrayDeque* q, void (*process)(void* item));

/**
 * Clears the deque of all items.
 * 
 * Efficiency: O(1)
 *
 * @param q => The deque to clear all items from.
 */
int adeque_clear(ArrayDeque* q);

/**
 * Removes the deque completely from memory.
 * 
 * Efficiency: O(1)
 * 
 * @param q => The deque to clear and free from memory.
 */
void adeque_free(ArrayDeque* q);

#endif /* _ARRAY_DEQUE */
