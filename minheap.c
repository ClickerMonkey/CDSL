/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

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

#include <stdio.h>

#include "util.h"
#include "minheap.h"

/**
 * A pool is a stack like structure that can pop and push StackNodes.
 * If there are no StackNodes to pop and a request is made then the 
 * pool will allocate a StackNode on the spot. A pool is restricted
 * by a minimum capcity.
 */
typedef struct 
{
	// The current number of nodes available for unpooling.
	unsigned int size;
	// The minimum number of nodes that can be pooled.
	unsigned int capacity;
	// The array of node pointers for pooling/unpooling.
	MinHeapNode** nodes;

} Pool;


// The pool to use for any Queue's nodes.
Pool* pool;


// Creates a pool of StackNodes.
void pool_minheap(unsigned int capacity)
{
	pool = alloc(Pool, 1);

	pool->capacity = capacity;
	pool->size = 0;
	pool->nodes = alloc(MinHeapNode*, capacity);
}

// Destroys the pool of StackNodes.
void unpool_minheap()
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
MinHeapNode* pop_MinHeapNode()
{
	// Of pooling isn't supported then just allocate a new one.
	if (pool == NULL)
		return alloc(MinHeapNode, 1);

	MinHeapNode* node;

	// If there are none on the pool then allocate a new one
	if (pool->size == 0)
	{
		node = alloc(MinHeapNode, 1);
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
void push_MinHeapNode(MinHeapNode* node)
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

// Initializes a new minimum heap based on the minimum capacity
// of items the heap can store.
MinHeap* newMinHeap(unsigned int capacity)
{
	MinHeap* h = alloc(MinHeap, 1);
	
	h->size = 0;
	h->capacity = capacity;
	h->nodes = alloc(MinHeapNode*, capacity);

	return h;
}

// Heapifies from some index up.
void minheap_heapifyUp(MinHeap* h, unsigned int index)
{
	unsigned int parent = (index - 1) >> 1;

	MinHeapNode* bottom = h->nodes[index];

	while (index > 0 && h->nodes[parent]->key > bottom->key)
	{
		h->nodes[index] = h->nodes[parent];
		index = parent;
		parent = (parent - 1) >> 1;
	}
	h->nodes[index] = bottom;
}

// Heapifies from some index down.
void minheap_heapifyDown(MinHeap* h, unsigned int index)
{
	unsigned int larger, left, right;
	MinHeapNode* top = h->nodes[index];
	
	while (index < (h->size >> 1))
	{
		left = (index << 1) | 1;
		right = left + 1;
	
		if (right < h->size && (h->nodes[left]->key > h->nodes[right]->key))
			larger = right;
		else
			larger = left;
	
		if (top->key <= h->nodes[larger]->key)
			break;

		h->nodes[index] = h->nodes[larger];
		index = larger;
	}
	h->nodes[index] = top;
}

// Finds a node with the specified key with a linear search.
MinHeapNode* minheap_getNode(MinHeap* h, int key, unsigned int* index)
{
	unsigned int i;
	for (i = 0; i < h->size; i++)
		if (h->nodes[i]->key == key)
			return h->nodes[*index = i];
			
	return NULL;
}

// Adds to the minimum heap and heapifies up to preserve the properties
// of a min heap.
int minheap_add(MinHeap* h, int key, void* item)
{
	if (h->size == h->capacity)
		return false;

	MinHeapNode* node = pop_MinHeapNode();
	node->key = key;
	node->data = item;
	
	h->nodes[h->size] = node;
	minheap_heapifyUp(h, h->size);

	h->size++;

	return true;
}

// Adds to the minimum heap forcing the heap to resize if it doesn't
// have enough space. This will heapify up to preserve the properties
// of a min heap.
void minheap_addf(MinHeap* h, int key, void* item)
{
	if (h->size == h->capacity)
		minheap_resize(h, h->capacity << 1);
	
	minheap_add(h, key, item);
}

// Gets the item with the specified key and returns it. If the key isn't
// found then NULL is returned.
void* minheap_get(MinHeap* h, int key)
{
	unsigned int index = 0;
	MinHeapNode* node = minheap_getNode(h, key, &index);

	if (node == NULL)
		return NULL;

	return node->data;
}

// Removes the item with the minimum key from the top of the heap and
// heapifies down to preserve the properties of a min heap.
void* minheap_popMin(MinHeap* h)
{
	if (h->size == 0)
		return NULL;

	void* item = h->nodes[0]->data;

	push_MinHeapNode(h->nodes[0]);

	h->size--;
	h->nodes[0] = h->nodes[h->size];
	minheap_heapifyDown(h, 0);

	return item;
}

// Returns the item at the top of the min heap without removing it.
void* minheap_peekMin(MinHeap* h)
{
	if (h->size == 0)
		return NULL;

	return h->nodes[0]->data;
}

// Sets the item with the specified key. If the key is not found in the
// heap then false is returned, a successful set returns true.
int minheap_set(MinHeap* h, int key, void* item)
{
	unsigned int index = 0;
	MinHeapNode* node = minheap_getNode(h, key, &index);

	if (node == NULL)
		return false;

	node->data = item;
	
	return true;	
}

// Updates an item's key on the heap with a new heap. The heap is
// heapified to preserve the properties of a min heap.
int minheap_update(MinHeap* h, int oldKey, int newKey)
{
	unsigned int index = 0;
	MinHeapNode* node = minheap_getNode(h, oldKey, &index);

	if (node == NULL)
		return false;

	node->key = newKey;

	if (oldKey > newKey)
		minheap_heapifyUp(h, index);
	else
		minheap_heapifyDown(h, index);

	return true;
}

// Returns true if the min heap has no items in it.
int minheap_isEmpty(MinHeap* h)
{
	return (h->size == 0);
}

// Returns the height of the min heap.
int minheap_getHeight(MinHeap* h)
{
	return ilog2(h->size);
}

// Resizes the minimum capacity of the min heap.
void minheap_resize(MinHeap* h, unsigned int capacity)
{
	h->size = (h->size < capacity ? h->size : capacity);
	h->capacity = capacity;
	h->nodes = realloc(h->nodes, void*, capacity);
}

// Does a breadth first search on the heap and for each item traversed 
// the method 'process' is called passing in that item.
void minheap_traverseBreadth(MinHeap* h, void (*process)(void* item))
{
	unsigned int i;
	for (i = 0; i < h->size; i++)
		process(h->nodes[i]->data);
}

// Displays the min heap given a min width for the strings returned. Each
// time an item is about to be printed the toString method is called to get
// a string representation of the data in the heap.
void minheap_display(MinHeap* h, int minLength, char* (*toString)(void* item))
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
	sprintf(format, "%s%ds", "%", minLength);

	int i, j, level, total = 0;

	for (level = 0; level < height; level++)
	{
		// The number of nodes on this level
		int count = 1 << level;

		// The number of child nodes on this level
		int children = (1 << (height - level - 1)) - 1;
		// How many spaces between each node at this level
		int spacing = children * minLength + (children + 1);
// 		int spacing = (((height - level) << 1) - 1) * minLength;
		
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

// Clears the min heap of all items.
void minheap_clear(MinHeap* h)
{
	if (h->size == 0)
		return;

	unsigned int i;
	for (i = 0; i < h->size; i++)
		push_MinHeapNode(h->nodes[i]);

	h->size = 0;
}

// Clears the min heap of all items and frees the nodes and the heap from memory.
void minheap_free(MinHeap* h)
{
	if (h == NULL)
		return;

	minheap_clear(h);
	free(h->nodes);
	free(h);
}
