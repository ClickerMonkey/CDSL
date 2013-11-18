/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _MAX_HEAP
#define _MAX_HEAP

/**
 * This is a node for a max heap that holds generic data.
 */
typedef struct
{
	// The data contained in this node
	void* data;
	// The key used to sort this node
	int key;

} MaxHeapNode;

/**
 * This is a max heap containing generic data which is ordered by some key 
 * value. The operations that can be performed on an array list are:
 * 
 * Add => Add an item to the max heap given a key.
 * PeekMax => Returns the item that has the highest key.
 * PopMax => Removes and returns the item that has the highest key.
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
	// The maximum number of items allowed in this heap.
	unsigned int capacity;
	// The array of nodes that make up this heap.
	MaxHeapNode** nodes;

} MaxHeap;

/**
 * Creates a pool of StackNodes.
 * 
 * @param capacity => The maximum number of nodes that can be pooled.
 */
void pool_maxheap(unsigned int capacity);

/**
 * Destroys the pool of StackNodes.
 */
void unpool_maxheap();

/**
 * Initializes a new maximum heap based on the maximum capacity
 * of items the heap can store.
 * 
 * @param capacity => The initial maximum size of the max heap.
 */
MaxHeap* newMaxHeap(unsigned int capacity);

/**
 * Adds to the maximum heap and heapifies up to preserve the properties
 * of a max heap.
 * 
 * Efficiency: O(h) where h is the height of the heap.
 * 
 * @param h => The max heap to add to.
 * @param key => The value or key of the item to add.
 * @param item => The generic data to add to the heap.
 */
int maxheap_add(MaxHeap* h, int key, void* item);

/**
 * Adds to the maximum heap forcing the heap to resize if it doesn't
 * have enough space. This will heapify up to preserve the properties
 * of a max heap.
 * 
 * Efficiency: O(h) where h is the height of the heap.
 * 
 * @param h => The max heap to add to forcefully.
 * @param key => The value or key of the item to add.
 * @param item => The generic data to add to the heap.
 */
void maxheap_addf(MaxHeap* h, int key, void* item);

/**
 * Gets the item with the specified key and returns it. If the key isn't
 * found then NULL is returned.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The max heap to search for a key.
 * @param key => The key to search for in the max heap.
 */
void* maxheap_get(MaxHeap* h, int key);

/**
 * Removes the item with the maximum key from the top of the heap and
 * heapifies down to preserve the properties of a max heap.
 * 
 * Efficiency: O(h) where h is the height of the heap.
 * 
 * @param h => The max heap to pop from.
 */
void* maxheap_popMax(MaxHeap* h);

/**
 * Returns the item at the top of the max heap without removing it.
 * 
 * Efficiency: O(1)
 * 
 * @param h => The max heap to peek from.
 */
void* maxheap_peekMax(MaxHeap* h);

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
int maxheap_set(MaxHeap* h, int key, void* item);

/**
 * Updates an item's key on the heap with a new heap. The heap is
 * heapified to preserve the properties of a max heap.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The max heap to update an item from.
 * @param oldKey => The old key of the item to search for.
 * @param newKey => The new key of the item.
 */
int maxheap_update(MaxHeap* h, int oldKey, int newKey);

/**
 * Returns true if the max heap has no items in it.
 * 
 * Efficiency: O(1)
 * 
 * @param h => The max heap to check for emptiness.
 */
int maxheap_isEmpty(MaxHeap* h);

/**
 * Returns the height of the max heap.
 * 
 * Efficiency: O(1)
 * 
 * @param h => The max heap to calculate the height of.
 */
int maxheap_getHeight(MaxHeap* h);

/**
 * Resizes the maximum capacity of the max heap.
 * 
 * Efficiency: O(1)
 * 
 * @param h => The max heap to resize.
 * @param capacity => The new maximum size of the heap.
 */
void maxheap_resize(MaxHeap* h, unsigned int capacity);

/**
 * Does a breadth first search on the heap and for each item traversed 
 * the method 'process' is called passing in that item.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The max heap to traverse.
 * @param process => The method that is called every time an item is traversed.
 */
void maxheap_traverseBreadth(MaxHeap* h, void (*process)(void* item));

/**
 * Displays the max heap given a max width for the strings returned. Each
 * time an item is about to be printed the toString method is called to get
 * a string representation of the data in the heap.
 * 
 * @param h => The max heap to display to stdout.
 * @param maxLength => The maximum length of any string of an item to print.
 * @param toString => The method that is called for every item to be printed.
 */
void maxheap_display(MaxHeap* h, int maxLength, char* (*toString)(void* item));

/**
 * Clears the max heap of all items.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The max heap to clear of all items.
 */
void maxheap_clear(MaxHeap* h);

/**
 * Clears the max heap of all items and frees the nodes and the heap from memory.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The max heap to clear and free from memory.
 */
void maxheap_free(MaxHeap* h);

#endif /* _MAX_HEAP */
