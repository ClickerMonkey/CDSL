/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#include "util.h"
#include "alist.h"

/**
 * This is an array-list containing generic data. The operations that can be 
 * performed on an array list are:
 * 
 * Add => Add an item to the end of the list
 * Insert => Insert an item into the list at some point
 * Remove => Remove an item from the list
 * RemoveAt => Remove an item at an index in the list.
 * Resize => Doubles the capacity of the array list
 * Traverse => Traverses the list of items
 * Clear => Clears all items from the list
 * Free => Frees the list from memory.
 * 
 * @author Philip Diffenderfer
 */

// Returns a new array list with no data and an initial size of 16.
ArrayList* emptyArrayList()
{
	return newArrayList(16);
}

// Returns a new array list with no items, allocated to the heap.
ArrayList* newArrayList(unsigned int initialSize)
{
	ArrayList* l = alloc(ArrayList, 1);

	l->size = 0;
	l->capacity = initialSize;
	l->data = calloc(void*, initialSize);

	return l;
}

// Returns the i'th item in the array list.
void* alist_get(ArrayList* l, unsigned int index)
{
	if (index < 0 || index >= l->size)
		return NULL;

	return l->data[index];
}

// This will add an item to the end of the list.
void alist_add(ArrayList* l, void* data)
{
	// If the list is full then resize it.
	if (l->size == l->capacity)
		alist_resize(l, l->capacity << 1);

	l->data[l->size] = data;
	l->size++;
}

// Inserts data into an array list at the given index. If the index is past
// or at the end of the list then the data will be added to the end. If the
// index is between the beginning and end of the list then all data after
// the given index will be shifted to make space for the item.
int alist_insert(ArrayList* l, void* data, unsigned int index)
{
	if (index < 0 || index > l->size)
		return false;

	// If the list is full then resize it.
	if (l->size == l->capacity)
		alist_resize(l, l->capacity << 1);

	unsigned int i = l->size;
	while (i > index)
	{
		l->data[i] = l->data[i - 1];
		i--;
	}

	l->data[index] = data;
	l->size++;
	
	return true;
}

// Removes and returns the item at the given index. If no item exists at the
// given index or its completely outside the bounds of the list NULL is returned.
void* alist_removeAt(ArrayList* l, unsigned int index)
{
	if (index < 0 || index >= l->size)
		return NULL;
	
	void* data = l->data[index];

	while (index < l->size)
	{
		l->data[index] = l->data[index + 1];
		index++;
	}

	l->size--;
	l->data[l->size] = NULL;

	return data;
}

// Removes and returns the item that is equal to the given item
// based on the equal method passed in.
void* alist_remove(ArrayList* l, void* item, int (*equals)(void*, void*))
{
	// First try to find it, then remove it.
	unsigned int i = 0;
	for (i = 0; i < l->size; i++)
		if (equals(item, l->data[i]))
			return alist_removeAt(l, i);

	// The item was not found in the list
	return NULL;
}

// Returns true if this list has no items.
int alist_isEmpty(ArrayList* l)
{
	return (l->size == 0);
}

// Resizes the given array list with a new capacity. If the new size passed
// in is smaller then the number of items currently in the list then the
// items at the end of the list are removed.
void alist_resize(ArrayList* l, unsigned int newSize)
{
	l->size = min(l->size, newSize);
	l->capacity = newSize;
	l->data = realloc(l->data, void*, newSize);
}

// Traverse the list without affecting it starting at the front of the
// list and moving towards the back. Each item traversed will be sent
// through the process method.
void alist_traverseForward(ArrayList* l, void (*process)(void* item))
{
	unsigned int i;
	for (i = 0; i < l->size; i++)
		process(l->data[i]);
}

// Traverse the list without affecting it starting at the back of the
// list and moving towards the front. Each item traversed will be sent
// through the process method.
void alist_traverseBackward(ArrayList* l, void (*process)(void* item))
{
	unsigned int i;
	for (i = l->size - 1; i >= 0; i--)
		process(l->data[i]);
}

// Clears the list of all data.
void alist_clear(ArrayList* l)
{
	l->size = 0;
}

// Removes the list completely from memory.
void alist_free(ArrayList* l)
{
	if (l == NULL)
		return;

	alist_clear(l);
	free(l->data);
	free(l);
}
