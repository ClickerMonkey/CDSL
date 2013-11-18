/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

/**
 * This is a linked-list containing generic data. The operations that can be 
 * performed on an array list are:
 * 
 * Get => Gets an item at an index.
 * Add => Add an item to the end of the list.
 * AddFirst => Adds an item to the beginning of the list.
 * RemoveFirst => Removes and Returns the first item in the list.
 * Start => Starts the traversing of the list at the beginning.
 * Peek => Returns the current item being traversed.
 * Next => Goes to the next item to traverse.
 * Remove => Removes the current item being traversed from the list.
 * InsertAfter => Inserts an item after the current item being traversed.
 * InsertBefore => Inserts an item before the current item being traversed.
 * HasNext => Returns true when there's another item to traverse.
 * Traverse => Traverses the list of items.
 * Clear => Clears all items from the list.
 * Free => Frees the list from memory.
 * 
 * @author Philip Diffenderfer
 */

#include "util.h"
#include "list.h"

/**
 * A pool is a stack like structure that can pop and push QueueNodes.
 * If there are no QueueNodes to pop and a request is made then the 
 * pool will allocate a QueueNode on the spot. A pool is restricted
 * by a maximum capcity.
 */
typedef struct
{
	// The current number of nodes available for unpooling.
	int size;
	// The maximum number of nodes that can be pooled.
	int capacity;
	// The array of node pointers for pooling/unpooling.
	ListNode** nodes;

} Pool;


// The pool to use for any Queue's nodes.
Pool* pool;

// Creates a pool of ListNodes.
void pool_list(unsigned int capacity)
{
	pool = alloc(Pool, 1);

	pool->capacity = capacity;
	pool->size = 0;
	pool->nodes = alloc(ListNode*, capacity);
}

// Destroys the pool of ListNodes.
void unpool_list()
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
ListNode* pop_ListNode()
{
	if (pool == NULL)
		return alloc(ListNode, 1);

	ListNode* node;

	if (pool->size == 0)
	{
		node = alloc(ListNode, 1);
	}
	else
	{
		pool->size--;
		node = pool->nodes[pool->size];
		pool->nodes[pool->size] = NULL;
	}

	return node;
}

// Puts the node on the pool if there is space.
void push_ListNode(ListNode* node)
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

	node->data = NULL;
	node->next = NULL;
	pool->nodes[pool->size++] = node;
}


// Returns a new List with no items, allocated to the heap.
List* newList()
{
	List* l = alloc(List, 1);
	
	l->first = NULL;
	l->last = NULL;
	l->current = NULL;
	l->previous = NULL;
	l->size = 0;

	return l;
}

// A private function for inserting a node
ListNode* insertNode(List* l, ListNode* before, ListNode* after, void* data)
{
	ListNode* node = pop_ListNode();
	node->data = data;
	node->next = NULL;

	if (l->size == 0)
		l->first = l->last = node;
	else
	{
		if (before != NULL)
			before->next = node;
		else
			l->first = node;

		if (after != NULL)
			node->next = after;
		else
			l->last = node;
	}

	l->size++;

	return node;	
}

// Given a node to remove and the node after it this will remove
// a node from a list. This will return the node
ListNode* removeNode(List* l, ListNode* node, ListNode* before)
{
	if (node == NULL || l->size == 0)
		return NULL;

	ListNode* next = node->next;

	if (before != NULL)
		before->next = next;
	else
		l->first = next;

	push_ListNode(node);

	l->size--;

	if (l->size == 0)
		l->first = l->last = NULL;

	return next;
}

// Returns the i'th item in the list.
void* list_get(List* l, unsigned int index)
{
	// Check for a non-null list, and an index within the bounds
	if (index >= l->size || index < 0)
		return 0;

	ListNode* node = l->first;
	
	while (index-- > 0)
		node = node->next;

	return node->data;
}

// This will add an item to the end of the list.
void list_add(List* l, void* data)
{
	insertNode(l, l->last, NULL, data);
}

// This will add an item to the beginning of the list.
void list_addFirst(List* l, void *data)
{
	insertNode(l, NULL, l->first, data);
}

// This will remove and return the item on the beginning of the list.
void* list_removeFirst(List* l)
{
	if (l->size == 0)
		return NULL;

	void* data = l->first->data;
	ListNode* node = removeNode(l, l->first, NULL);

	if (l->size == 1)
		l->first = l->last = node;
	else
		l->first = node;

	return data;
}

// Returns true if this list has no items.
int list_isEmpty(List* l)
{
	return (l->size == 0);
}


// Starts the traversing of the linked list
void list_start(List* l)
{
	l->previous = NULL;
	l->current = l->first;
}

// During list traversal this will return the current item without going to the next.
void* list_peek(List* l)
{
	if (l->current == NULL)
		return NULL;
	
	return l->current->data;
}

// During list traversal this goes to the next item and returns it.
void* list_next(List* l)
{
	if (l->current == NULL)
		return NULL;

	l->previous = l->current;
	l->current = l->current->next;

	return l->previous->data;
}

// During list traversal this removes the current item from the 
// list and returns it.
void* list_remove(List* l)
{
	if (l->current == NULL || l->size == 0)
		return NULL;

	void* data = l->current->data;

	l->current = removeNode(l, l->current, l->previous);

	return data;
}

// During list traveral this will insert an item before the current item.
void list_insertBefore(List* l, void* data)
{
	insertNode(l, l->previous, l->current, data);
}

// During list traveral this will insert an item before the current item.
void list_insertAfter(List* l, void* data)
{
	if (l->current == NULL)
		return;

	insertNode(l, l->current, l->current->next, data);
}

// During list traversal this returns whether there are more items 
// to traverse.
int list_hasNext(List* l)
{
	return (l->current != NULL);
}

// Traverse the list without affecting it starting at the front of the
// list and moving towards the back. Each item traversed will be sent
// through the process method.
void list_traverse(List* l, void (*process)(void* item))
{
	ListNode* current = l->first;
	while (current != NULL)
	{
		process(current->data);
		current = current->next;
	}
}

// Clears the list of all data.
void list_clear(List* l)
{
	l->current = l->first;
	
	// Remove each node and place it on the pool
	while (l->current != NULL)
	{
		push_ListNode(l->current);
		l->current = l->current->next;
	}
	
	// Clear all the lists data
	l->first = NULL;
	l->last = NULL;
	l->current = NULL;
	l->previous = NULL;
	l->size = 0;

}
 
// Removes the list completely from memory.
void list_free(List* l)
{
	if (l == NULL)
		return;

	list_clear(l);
	free(l);
}
