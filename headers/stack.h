/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _STACK
#define _STACK

/**
 * A node for the referenced-based stack. This contains the generic data in the
 * stack as well as the previous node in the stack.
 */
typedef struct StackNode
{
	// The generic data contained in this node.
	void* data;
	// The previously pushed node on the stack.
	struct StackNode* previous;

} StackNode;

/**
 * A referenced based stack containing generic data. The operations that can be
 * performed on an array list are:
 * 
 * Pop => Removes and returns the item at the top of the stack.
 * Peek => Returns the item at the top of the stack.
 * Push => Adds an item to the top of the stack.
 * Traverse => Traverses the stack of items either up or down.
 * Clear => Clears all items from the stack.
 * Free => Frees the stack from memory.
 * 
 * @author Philip Diffenderfer
 */
typedef struct 
{	
	// The node for the first item on the stack
	StackNode* top;
	// The number of items in the stack.
	unsigned int size;

} Stack;

/**
 * Creates a pool of StackNodes.
 * 
 * @param capacity => The maximum number of nodes that can be pooled.
 */
void pool_stack(unsigned int capacity);

/**
 * Destroys the pool of StackNodes.
 */ 
void unpool_stack();

/**
 * Returns a stack of no size allocated to the heap.
 */
Stack* newStack();

/**
 * Returns and removes the top item on the stack.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to pop from.
 */
void* stack_pop(Stack* s);

/**
 * Returns the top item on the stack.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to peek at.
 */
void* stack_peek(Stack* s);

/**
 * Adds an item to the top of a stack.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to push an item onto.
 * @param item => The item to push onto the stack.
 */
int stack_push(Stack* s, void* item);

/**
 * Returns whether the stack is empty or not.
 * 
 * Efficiency: O(1)
 * 
 * @param s => The stack to check for emptiness.
 */
int stack_isEmpty(Stack* s);

/**
 * Traverse the stack without affecting it starting at the top of the
 * stack and moving towards the bottom. Each item traversed will be sent
 * through the process method.
 * 
 * @param s => The stack to traverse from top-to-bottom.
 * @param process => The method that is called every time an item is traversed.
 */
void stack_traverse(Stack* s, void (*process)(void* item));

/**
 * Clears the stack of all items and removes nodes from memory.
 * 
 * Efficiency: O(n)
 * 
 * @param s => The stack to clear of all items.
 */
int stack_clear(Stack* s);

/**
 * Removes the stack completely from memory.
 * 
 * Efficiency: O(n)
 * 
 * @param s => The stack to clear and free from memory.
 */
void stack_free(Stack* s);

#endif /* _STACK */
