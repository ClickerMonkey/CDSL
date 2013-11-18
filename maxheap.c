/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

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

#include <stdio.h>

#include "util.h"
#include "maxheap.h"

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
	MaxHeapNode** nodes;

} Pool;


// The pool to use for any Queue's nodes.
Pool* pool;


// Creates a pool of StackNodes.
void pool_maxheap(unsigned int capacity)
{
	pool = alloc(Pool, 1);

	pool->capacity = capacity;
	pool->size = 0;
	pool->nodes = alloc(MaxHeapNode*, capacity);
}

// Destroys the pool of StackNodes.
void unpool_maxheap()
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
MaxHeapNode* pop_MaxHeapNode()
{
	// Of pooling isn't supported then just allocate a new one.
	if (pool == NULL)
		return alloc(MaxHeapNode, 1);

	MaxHeapNode* node;

	// If there are none on the pool then allocate a new one
	if (pool->size == 0)
	{
		node = alloc(MaxHeapNode, 1);
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
void push_MaxHeapNode(MaxHeapNode* node)
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
	pool->nodes[pool->size++] = node;
}

// Initializes a new maximum heap based on the maximum capacity
// of items the heap can store.
MaxHeap* newMaxHeap(unsigned int capacity)
{
	MaxHeap* h = alloc(MaxHeap, 1);
	
	h->size = 0;
	h->capacity = capacity;
	h->nodes = alloc(MaxHeapNode*, capacity);

	return h;
}

// Heapifies from some index up.
void maxheap_heapifyUp(MaxHeap* h, unsigned int index)
{
	unsigned int parent = (index - 1) >> 1;

	MaxHeapNode* bottom = h->nodes[index];

	while (index > 0 && h->nodes[parent]->key < bottom->key)
	{
		h->nodes[index] = h->nodes[parent];
		index = parent;
		parent = (parent - 1) >> 1;
	}
	h->nodes[index] = bottom;
}

// Heapifies from some index down.
void maxheap_heapifyDown(MaxHeap* h, unsigned int index)
{
	unsigned int larger, left, right;
	MaxHeapNode* top = h->nodes[index];
	
	while (index < (h->size >> 1))
	{
		left = (index << 1) | 1;
		right = left + 1;
	
		if (right < h->size && (h->nodes[left]->key < h->nodes[right]->key))
			larger = right;
		else
			larger = left;
	
		if (top->key >= h->nodes[larger]->key)
			break;

		h->nodes[index] = h->nodes[larger];
		index = larger;
	}
	h->nodes[index] = top;
}

// Finds a node with the specified key with a linear search.
MaxHeapNode* maxheap_getNode(MaxHeap* h, int key, unsigned int* index)
{
	unsigned int i;
	for (i = 0; i < h->size; i++)
		if (h->nodes[i]->key == key)
			return h->nodes[*index = i];
			
	return NULL;
}

// Adds to the maximum heap and heapifies up to preserve the properties
// of a max heap.
int maxheap_add(MaxHeap* h, int key, void* item)
{
	if (h->size == h->capacity)
		return false;

	MaxHeapNode* node = pop_MaxHeapNode();
	node->key = key;
	node->data = item;
	
	h->nodes[h->size] = node;
	maxheap_heapifyUp(h, h->size);

	h->size++;

	return true;
}

// Adds to the maximum heap forcing the heap to resize if it doesn't
// have enough space. This will heapify up to preserve the properties
// of a max heap.
void maxheap_addf(MaxHeap* h, int key, void* item)
{
	if (h->size == h->capacity)
		maxheap_resize(h, h->capacity << 1);
	
	maxheap_add(h, key, item);
}

// Gets the item with the specified key and returns it. If the key isn't
// found then NULL is returned.
void* maxheap_get(MaxHeap* h, int key)
{
	unsigned int index = 0;
	MaxHeapNode* node = maxheap_getNode(h, key, &index);

	if (node == NULL)
		return NULL;

	return node->data;
}

// Removes the item with the maximum key from the top of the heap and
// heapifies down to preserve the properties of a max heap.
void* maxheap_popMax(MaxHeap* h)
{
	if (h->size == 0)
		return NULL;

	void* item = h->nodes[0]->data;

	push_MaxHeapNode(h->nodes[0]);

	h->size--;
	h->nodes[0] = h->nodes[h->size];
	maxheap_heapifyDown(h, 0);

	return item;
}

// Returns the item at the top of the max heap without removing it.
void* maxheap_peekMax(MaxHeap* h)
{
	if (h->size == 0)
		return NULL;

	return h->nodes[0]->data;
}

// Sets the item with the specified key. If the key is not found in the
// heap then false is returned, a successful set returns true.
int maxheap_set(MaxHeap* h, int key, void* item)
{
	unsigned int index = 0;
	MaxHeapNode* node = maxheap_getNode(h, key, &index);

	if (node == NULL)
		return false;

	node->data = item;
	
	return true;	
}

// Updates an item's key on the heap with a new heap. The heap is
// heapified to preserve the properties of a max heap.
int maxheap_update(MaxHeap* h, int oldKey, int newKey)
{
	unsigned int index = 0;
	MaxHeapNode* node = maxheap_getNode(h, oldKey, &index);

	if (node == NULL)
		return false;

	node->key = newKey;

	if (oldKey < newKey)
		maxheap_heapifyUp(h, index);
	else
		maxheap_heapifyDown(h, index);

	return true;
}

// Returns true if the max heap has no items in it.
int maxheap_isEmpty(MaxHeap* h)
{
	return (h->size == 0);
}

// Returns the height of the max heap.
int maxheap_getHeight(MaxHeap* h)
{
	return ilog2(h->size);
}

// Resizes the maximum capacity of the max heap.
void maxheap_resize(MaxHeap* h, unsigned int capacity)
{
	h->size = (h->size < capacity ? h->size : capacity);
	h->capacity = capacity;
	h->nodes = realloc(h->nodes, void*, capacity);
}

// Does a breadth first search on the heap and for each item traversed 
// the method 'process' is called passing in that item.
void maxheap_traverseBreadth(MaxHeap* h, void (*process)(void* item))
{
	unsigned int i;
	for (i = 0; i < h->size; i++)
		process(h->nodes[i]->data);
}

// Displays the max heap given a max width for the strings returned. Each
// time an item is about to be printed the toString method is called to get
// a string representation of the data in the heap.
void maxheap_display(MaxHeap* h, int maxLength, char* (*toString)(void* item))
{
	if (h->size == 0)
		return;

	if (h->size == 1)
	{
		printf("%s\n", toString(h->nodes[0]->data));
		return;
	}
	
	int height = ilog2(h->size) + 1;

	// Create the formatting string for every nod
	char format[10];
	sprintf(format, "%s%ds", "%", maxLength);

	int i, j, level, total = 0;

	for (level = 0; level < height; level++)
	{
		// The number of nodes on this level
		int count = 1 << level;

		// The number of child nodes on this level
		int children = (1 << (height - level - 1)) - 1;
		// How many spaces between each node at this level
		int spacing = children * maxLength + (children + 1);
// 		int spacing = (((height - level) << 1) - 1) * maxLength;
		
		for (i = 0; i < count && (total < h->size); i++)
		{
			printf(format, toString(h->nodes[total]->data));

			if (i < count - 1)
				for (j = 0; j < spacing; j++)
					printf(" ");

			total++;
		}
		printf("\n");
	}
}

// Clears the max heap of all items.
void maxheap_clear(MaxHeap* h)
{
	if (h->size == 0)
		return;

	unsigned int i;
	for (i = 0; i < h->size; i++)
		push_MaxHeapNode(h->nodes[i]);

	h->size = 0;
}

// Clears the max heap of all items and frees the nodes and the heap from memory.
void maxheap_free(MaxHeap* h)
{
	if (h == NULL)
		return;

	maxheap_clear(h);
	free(h->nodes);
	free(h);
}
