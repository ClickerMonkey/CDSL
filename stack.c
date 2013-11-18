/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

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

#include "util.h"
#include "stack.h"

/**
 * A pool is a stack like structure that can pop and push StackNodes.
 * If there are no StackNodes to pop and a request is made then the 
 * pool will allocate a StackNode on the spot. A pool is restricted
 * by a maximum capcity.
 */
typedef struct 
{
	// The current number of nodes available for unpooling.
	unsigned int size;
	// The maximum number of nodes that can be pooled.
	unsigned int capacity;
	// The array of node pointers for pooling/unpooling.
	StackNode** nodes;

} Pool;


// The pool to use for any Queue's nodes.
Pool* pool;


// Creates a pool of StackNodes.
void pool_stack(unsigned int capacity)
{
	pool = alloc(Pool, 1);

	pool->capacity = capacity;
	pool->size = 0;
	pool->nodes = alloc(StackNode*, capacity);
}

// Destroys the pool of StackNodes.
void unpool_stack()
{
	if (pool == NULL)
		return;
	
	unsigned int i;
	for (i = 0; i < pool->size; i++)
		free(pool->nodes[i]);

	free(pool->nodes);
	free(pool);

	pool = NULL;
}

// Returns a node from the pool or allocates a new one.
StackNode* pop_StackNode()
{
	// Of pooling isn't supported then just allocate a new one.
	if (pool == NULL)
		return alloc(StackNode, 1);

	StackNode* node;

	// If there are none on the pool then allocate a new one
	if (pool->size == 0)
	{
		node = alloc(StackNode, 1);
	}
	// If there is one on the pool grab one from the back.
	else
	{
		pool->size--;
		node = pool->nodes[pool->size];
		pool->nodes[pool->size] = NULL;
	}

	return node;
}

// Puts the node on the pool if there is space.
void push_StackNode(StackNode* node)
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

	// push the node into the pool.
	node->data = NULL;
	node->previous = NULL;
	pool->nodes[pool->size++] = node;
}


// Returns a stack of no size allocated to the heap.
Stack* newStack()
{
	Stack* s = alloc(Stack, 1);

	s->top = NULL;
	s->size = 0;

	return s;
}

// Returns and removes the top item on the stack.
void* stack_pop(Stack* s)
{
	// Check that the stack passed in isn't null or empty
	if (stack_isEmpty(s))
		return NULL;
	
	// Grab the item on the top
	StackNode* top = s->top;

	void* data = top->data;
	// Remove the node from the top
	s->top = top->previous;
	// Try to pool the node if there's a pool
	push_StackNode(top);
	// Succesful pop, decrease size counter
	s->size--;

	// Clean up the empty list
	if (s->size == 0)
		s->top = NULL;

	return data;
}

// Returns the top item on the stack.
void* stack_peek(Stack* s)
{
	// Check that the stack passed in isn't null
	if (s->top == NULL)
		return NULL;

	return s->top->data;
}

// Adds an item to the top of a stack.
int stack_push(Stack* s, void* item)
{
	// Check that the stack passed in isn't null
	if (item == NULL)
		return false;

	// Try to pool the node if there's a pool
	StackNode* node = pop_StackNode();
	node->data = item;
	node->previous = s->top;
	s->top = node;

	// Succesful push, increase size counter
	s->size++;

	return true;
}

// Returns whether the stack is empty or not.
int stack_isEmpty(Stack* s)
{
	return (s->size == 0);
}

// Traverse the stack without affecting it starting at the top of the
// stack and moving towards the bottom. Each item traversed will be sent
// through the process method.
void stack_traverse(Stack* s, void (*process)(void* item))
{
	StackNode* current = s->top;

	while (current != NULL)
	{
		process(current->data);
		current = current->previous;
	}
}

// Clears the stack of all items and removes nodes from memory.
int stack_clear(Stack* s)
{
	// Check that the stack isn't null and has items
	if (stack_isEmpty(s))
		return false;

	StackNode* current = s->top;
	StackNode* previous;

	s->top = NULL;

	while (current != NULL)
	{
		previous = current;
		current = current->previous;
		free(previous);
	}

	s->size = 0;

	return true;
}

// Removes the stack completely from memory.
void stack_free(Stack* s)
{
	// Check that the stack passed in isn't null
	if (s == NULL)
		return;

	// Free all nodes from memory, then the stack itself
	stack_clear(s);
	free(s);
}
