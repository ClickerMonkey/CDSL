/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _ARRAY_LIST
#define _ARRAY_LIST

/**
 * This is an array-list containing generic data. The operations that can be 
 * performed on an array list are:
 * 
 * Add => Add an item to the end of the list.
 * Insert => Insert an item into the list at some point.
 * Remove => Remove an item from the list.
 * RemoveAt => Remove an item at an index in the list.
 * Resize => Doubles the capacity of the array list.
 * Traverse => Traverses the list of items.
 * Clear => Clears all items from the list.
 * Free => Frees the list from memory.
 * 
 * @author Philip Diffenderfer
 */
typedef struct
{
	// The number of elements in this list.
	unsigned int size;
	// The maximum number of items that can be in the list
	unsigned int capacity;
	// The array of data in this list.
	void** data;

} ArrayList;

/**
 * Returns a new array list with no data and an initial size of 16.
 */
ArrayList* emptyArrayList();

/**
 * Returns a new array list with no items, allocated to the heap.
 * 
 * @param initialSize => The starting length of the array of data.
 */
ArrayList* newArrayList(unsigned int initialSize);

/**
 * Returns the i'th item in the array list.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The array list to get from.
 * @param index => The index of the data to get in the list.
 */
void* alist_get(ArrayList* l, unsigned int index);

/**
 * This will add an item to the end of the list.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The array list to add to.
 * @param item => The generic data to add to the list.
 */
void alist_add(ArrayList* l, void* item);

/**
 * Inserts data into an array list at the given index. If the index is past
 * the end of the list then the data will not be added to the end. If the
 * index is between the beginning and end of the list then all data after
 * the given index will be shifted to make space for the item. This will return
 * true if the data was added and false if not.
 * 
 * Efficiency: O(s-i) where 's' is the size of the list and 'i' is the index given.
 * 
 * @param l => The array list to insert into.
 * @param item => The generic data to insert into the list.
 * @param index => The index at which to place the data.
 */
int alist_insert(ArrayList* l, void* item, unsigned int index);

/**
 * Removes and returns the item at the given index. If no item exists at the
 * given index or its completely outside the bounds of the list NULL is returned.
 * 
 * Efficiency: O(s-i) where 's' is the size of the list and 'i' is the index given.
 * 
 * @param l => The array list to remove from.
 * @param index => The index of an item in the list to remove.
 */
void* alist_removeAt(ArrayList* l, unsigned int index);

/**
 * Removes and returns the item that is equal to the given item
 * based on the equal method passed in.
 * 
 * Efficiency: O(s-i) where 's' is the size of the list and 'i' is the index of the item.
 * 
 * @param l => The array list to remove from.
 * @param item => The data to remove from the list.
 * @param equals => The method that determines if two items are equal.
 */
void* alist_remove(ArrayList* l, void* item, int (*equals)(void*, void*));

/**
 * Returns true if this list has no items.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The array list to test.
 */
int alist_isEmpty(ArrayList* l);

/**
 * Resizes the given array list with a new capacity. If the new size passed
 * in is smaller then the number of items currently in the list then the
 * items at the end of the list are removed.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The array list to resize.
 * @param newSize => The new size of the array list.
 */
void alist_resize(ArrayList* l, unsigned int newSize);

/**
 * Traverse the list without affecting it starting at the front of the
 * list and moving towards the back. Each item traversed will be sent
 * through the process method.
 * 
 * Efficiency: O(n)
 * 
 * @param l => The array list to traverse from front-to-back.
 * @param process => The method that is called every time an item is traversed.
 */
void alist_traverseForward(ArrayList* l, void (*process)(void* item));

/**
 * Traverse the list without affecting it starting at the back of the
 * list and moving towards the front. Each item traversed will be sent
 * through the process method.
 * 
 * Efficiency: O(n)
 * 
 * @param l => The array list to traverse from back-to-front.
 * @param process => The method that is called every time an item is traversed.
 */
void alist_traverseBackward(ArrayList* l, void (*process)(void* item));

/**
 * Clears the list of all data.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The array list to clear of all data.
 */
void alist_clear(ArrayList* l);

/**
 * Removes the list completely from memory.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The array list to free from memory.
 */
void alist_free(ArrayList* l);

#endif /* _ARRAY_LIST */
