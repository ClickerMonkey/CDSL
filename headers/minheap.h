/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _MIN_HEAP
#define _MIN_HEAP

/**
 * This is a node for a min heap that holds generic data.
 */
typedef struct
{
	// The data contained in this node
	void* data;
	// The key used to sort this node
	int key;

} MinHeapNode;

/**
 * This is a min heap containing generic data which is ordered by some key 
 * value. The operations that can be performed on an array list are:
 * 
 * Add => Add an item to the min heap given a key.
 * PeekMax => Returns the item that has the lowest key.
 * PopMax => Removes and returns the item that has the lowest key.
 * Set => Sets an item with some key.
 * Update => Updates some key with a new key.
 * Exists => Returns true if a given key exists in the tree.
 * Traverse => Traverses the list of items using a Breadth-First-Search.
 * Display => Displays the heap structure given a toString method.
 * Clear => Clears all items from the list.
 * Free => Frees the list from memory.
 * 
 * @author Philip Diffenderfer
 */
typedef struct
{
	// The number of items in this heap.
	unsigned int size;
	// The minimum number of items allowed in this heap.
	unsigned int capacity;
	// The array of nodes that make up this heap.
	MinHeapNode** nodes;

} MinHeap;

/**
 * Creates a pool of StackNodes.
 * 
 * @param capacity => The maximum number of nodes that can be pooled.
 */
void pool_minheap(unsigned int capacity);

/**
 * Destroys the pool of StackNodes.
 */
void unpool_minheap();

/**
 * Initializes a new minimum heap based on the minimum capacity
 * of items the heap can store.
 * 
 * @param capacity => The initial maximum size of the min heap.
 */
MinHeap* newMinHeap(unsigned int capacity);

/**
 * Adds to the minimum heap and heapifies up to preserve the properties
 * of a min heap.
 * 
 * Efficiency: O(h) where h is the height of the heap.
 * 
 * @param h => The max heap to add to.
 * @param key => The value or key of the item to add.
 * @param item => The generic data to add to the heap.
 */
int minheap_add(MinHeap* h, int key, void* item);

/**
 * Adds to the minimum heap forcing the heap to resize if it doesn't
 * have enough space. This will heapify up to preserve the properties
 * of a min heap.
 * 
 * Efficiency: O(h) where h is the height of the heap.
 * 
 * @param h => The max heap to add to forcefully.
 * @param key => The value or key of the item to add.
 * @param item => The generic data to add to the heap.
 */
void minheap_addf(MinHeap* h, int key, void* item);

/**
 * Gets the item with the specified key and returns it. If the key isn't
 * found then NULL is returned.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The max heap to search for a key.
 * @param key => The key to search for in the max heap.
 */
void* minheap_get(MinHeap* h, int key);

/**
 * Removes the item with the minimum key from the top of the heap and
 * heapifies down to preserve the properties of a min heap.
 * 
 * Efficiency: O(h) where h is the height of the heap.
 * 
 * @param h => The min heap to pop from.
 */
void* minheap_popMin(MinHeap* h);

/**
 * Returns the item at the top of the min heap without removing it.
 * 
 * Efficiency: O(1)
 * 
 * @param h => The min heap to peek from.
 */
void* minheap_peekMin(MinHeap* h);

/**
 * Sets the item with the specified key. If the key is not found in the
 * heap then false is returned, a successful set returns true.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The heap to search for a key and set its item.
 * @param key => The key to seach for in the max heap.
 * @param item => The new item at the key.
 */
int minheap_set(MinHeap* h, int key, void* item);

/**
 * Updates an item's key on the heap with a new heap. The heap is
 * heapified to preserve the properties of a min heap.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The max heap to update an item from.
 * @param oldKey => The old key of the item to search for.
 * @param newKey => The new key of the item.
 */
int minheap_update(MinHeap* h, int oldKey, int newKey);

/**
 * Returns true if the min heap has no items in it.
 * 
 * Efficiency: O(1)
 * 
 * @param h => The min heap to check for emptiness.
 */
int minheap_isEmpty(MinHeap* h);

/**
 * Returns the height of the min heap.
 * 
 * Efficiency: O(1)
 * 
 * @param h => The min heap to calculate the height of.
 */
int minheap_getHeight(MinHeap* h);

/**
 * Resizes the minimum capacity of the min heap.
 * 
 * Efficiency: O(1)
 * 
 * @param h => The min heap to resize.
 * @param capacity => The new maximum size of the heap.
 */
void minheap_resize(MinHeap* h, unsigned int capacity);

/**
 * Does a breadth first search on the heap and for each item traversed 
 * the method 'process' is called passing in that item.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The max heap to traverse.
 * @param process => The method that is called every time an item is traversed.
 */
void minheap_traverseBreadth(MinHeap* h, void (*process)(void* item));

/**
 * Displays the min heap given a min width for the strings returned. Each
 * time an item is about to be printed the toString method is called to get
 * a string representation of the data in the heap.
 * 
 * @param h => The max heap to display to stdout.
 * @param maxLength => The maximum length of any string of an item to print.
 * @param toString => The method that is called for every item to be printed.
 */
void minheap_display(MinHeap* h, int minLength, char* (*toString)(void* item));

/**
 * Clears the min heap of all items.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The max heap to clear of all items.
 */
void minheap_clear(MinHeap* h);

/**
 * Clears the min heap of all items and frees the nodes and the heap from memory.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The min heap to clear and free from memory.
 */
void minheap_free(MinHeap* h);

#endif /* _MIN_HEAP */
