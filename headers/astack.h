/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _ARRAY_STACK
#define _ARRAY_STACK

/**
 * An array based stack containing generic data. The operations that can be 
 * performed on an array list are:
 * 
 * Pop => Removes and returns the item at the top of the stack.
 * Peek => Returns the item at the top of the stack.
 * Push => Adds an item to the top of the stack.
 * Resize => Doubles the capacity of the stack.
 * Traverse => Traverses the stack of items either up or down.
 * Clear => Clears all items from the stack.
 * Free => Frees the stack from memory.
 * 
 * @author Philip Diffenderfer
 */
typedef struct 
{	
	// The array of items on the stack
	void** data;
	// The maximum numbfer of items that can be in the stack.
	int capacity;
	// The number of items in the stack.
	int size;

} ArrayStack;

/**
 * Returns a array stack of no size allocated to the heap.
 * 
 * @param capacity => The maximum initial size of the stack.
 */
ArrayStack* newArrayStack(int capacity);

/**
 * Returns and removes the top item on the array stack.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to pop from.
 */
void* astack_pop(ArrayStack* s);

/**
 * Returns the top item on the array stack.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to peek at.
 */
void* astack_peek(ArrayStack* s);

/**
 * Adds an item to the top of a array stack.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to push an item onto.
 * @param item => The item to push onto the stack.
 */
int astack_push(ArrayStack* s, void* item);

/**
 * Adds an item to the top of a array stack forcefully. If the stack
 * is full this will resize it by 2 times, then add the item on.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to push an item onto.
 * @param item => The item to push onto the stack forcefully.
 */
int astack_pushf(ArrayStack* s, void* item);

/**
 * Returns whether the array stack is empty or not.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to check for emptiness.
 */
int astack_isEmpty(ArrayStack* s);

/**
 * Resizes an array stack to a new capacity.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to resize.
 * @param capacity => The new maximum size of the stack.
 */
void astack_resize(ArrayStack* s, int capacity);

/**
 * Traverse the stack without affecting it starting at the top of the
 * stack and moving towards the bottom. Each item traversed will be sent
 * through the process method.
 * 
 * @param s => The stack to traverse from top-to-bottom.
 * @param process => The method that is called every time an item is traversed.
 */
void astack_traverseDown(ArrayStack* s, void (*process)(void* item));

/**
 * Traverse the stack without affecting it starting at the bottom of the
 * stack and moving towards the top. Each item traversed will be sent
 * through the process method.
 * 
 * @param s => The stack to traverse from bottom-to-top.
 * @param process => The method that is called every time an item is traversed.
 */
void astack_traverseUp(ArrayStack* s, void (*process)(void* item));

/**
 * Clears the array stack of all items.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to clear of all items.
 */
int astack_clear(ArrayStack* s);

/**
 * Removes the array stack completely from memory.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to clear and free from memory.
 */
void astack_free(ArrayStack* s);

#endif /* _ARRAY_STACK */

