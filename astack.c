/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

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

#include "util.h"
#include "astack.h"

// Returns an array stack of a fixed size.
ArrayStack* newArrayStack(int capacity)
{
	ArrayStack* s = alloc(ArrayStack, 1);

	s->size = 0;
	s->capacity = capacity;
	s->data = alloc(void*, capacity);

	return s;
}

// Returns and removes the top item on the array stack.
void* astack_pop(ArrayStack* s)
{
	// We can't pop for a null or empty stack
	if (s->size == 0)
		return NULL;

	s->size--;

	void* data = s->data[s->size];	
	s->data[s->size] = NULL;

	return data;	
}

// Returns the top item on the array stack.
void* astack_peek(ArrayStack* s)
{
	// We can't return anything for a null stack or empty stack
	if (s->size == 0)
		return NULL;

	return s->data[s->size - 1];
}

// Adds an item to the top of a array stack.
int astack_push(ArrayStack* s, void* item)
{
	// Don't push it if the stack given is null, the item is
	// null, or we've met the maximum capacity of the stack
	if (item == NULL || s->size == s->capacity)
		return false;

	s->data[s->size++] = item;
	
	return true;
}

// Adds an item to the top of a array stack.
int astack_pushf(ArrayStack* s, void* item)
{
	// Don't push it if the stack or item given is null.
	if (item == NULL)
		return false;
	// If we met the maximum capacity then double its size
	if (s->size == s->capacity)
		astack_resize(s, s->capacity << 1);

	s->data[s->size++] = item;
	
	return true;
}

// Returns whether the array stack is empty or not.
int astack_isEmpty(ArrayStack* s)
{
	return (s->size == 0);
}

// Resizes an array stack to a new capacity.
void astack_resize(ArrayStack* s, int capacity)
{
	// The size can't be larger then the new capacity
	s->size = min(s->size, capacity);
	s->capacity = capacity;
	// Reallocate space for more size
	s->data = realloc(s->data, void*, capacity);
}

// Traverse the stack without affecting it starting at the top of the
// stack and moving towards the bottom. Each item traversed will be sent
// through the process method.
void astack_traverseDown(ArrayStack* s, void (*process)(void* item))
{
	if (s->size == 0)
		return;
	
	int index = s->size - 1;
	while (index >= 0)
		process(s->data[index--]);
}

// Traverse the stack without affecting it starting at the bottom of the
// stack and moving towards the top. Each item traversed will be sent
// through the process method.
void astack_traverseUp(ArrayStack* s, void (*process)(void* item))
{
	if (s->size == 0)
		return;
	
	int index = 0;
	while (index < s->size)
		process(s->data[index++]);
}

// Clears the array stack of all items.
int astack_clear(ArrayStack* s)
{
	// Don't clear the array stack if it's null or empty
	if (s->size == 0)
		return false;

	s->size = 0;
	
	return true;
}

// Removes the array stack completely from memory.
void astack_free(ArrayStack* s)
{
	if (s == NULL)
		return;

	// clear it completely, free the array, then free the stack
	astack_clear(s);
	free(s->data);
	free(s);
}

