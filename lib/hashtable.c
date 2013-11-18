/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

/**
 * An open hashtable with a max capacity with a power of 2 which contains 
 * hashed entries. If a key is hashed to a place where an entry already exists
 * then the entry added will be contained in a linked list structure. The 
 * operations that can be performed on a hashtable are:
 * 
 * Put => Puts an item on the hashtable given a key.
 * Get => Gets an item from the hashtable given a key,
 * Set => Sets an item on the hashtable given a key.
 * Remove => Removes an item from the hashtable given a key.
 * Exists => Returns true if the given key exists on the table.
 * Traverse => Traverses through the hashtable in no specific order.
 * Display => Prints the hashtable to stdout using a toString method.
 * Clear => Clears the hashtable of all entries
 * Free => Clears the hashtable of all entries and frees it from memory.
 * 
 * @author Philip Diffenderfer
 */

#include <math.h>
#include <stdio.h>

#include "util.h"
#include "hashtable.h"

/**
 * A pool is a stack like structure that can pop and push StackNodes.
 * If there are no StackNodes to pop and a request is made then the 
 * pool will allocate a StackNode on the spot. A pool is restricted
 * by a maximum capcity.
 */
typedef struct 
{
	// The current number of nodes available for unpooling.
	int size;
	// The maximum number of nodes that can be pooled.
	int capacity;
	// The array of node pointers for pooling/unpooling.
	HashtableEntry** entries;

} Pool;

// The pool to use for any Queue's nodes.
Pool* pool;

// Creates a pool of HashtableEntries.
void pool_hashtable(unsigned int capacity)
{
	pool = alloc(Pool, 1);

	pool->capacity = capacity;
	pool->size = 0;
	pool->entries = alloc(HashtableEntry*, capacity);
}

// Destroys the pool of HashtableEntries.
void unpool_hashtable()
{
	if (pool == NULL)
		return;
	
	unsigned int i;
	for (i = 0; i < pool->size; i++)
		free(pool->entries[i]);

	free(pool->entries);
	free(pool);

	pool = NULL;
}

// Returns a node from the pool or allocates a new one.
HashtableEntry* pop_HashtableEntry()
{
	// Of pooling isn't supported then just allocate a new one.
	if (pool == NULL)
		return alloc(HashtableEntry, 1);

	HashtableEntry* entry;

	// If there are none on the pool then allocate a new one
	if (pool->size == 0)
	{
		entry = alloc(HashtableEntry, 1);
	}
	// If there is one on the pool grab one from the back.
	else
	{
		pool->size--;
		entry = pool->entries[pool->size];
		pool->entries[pool->size] = NULL;
	}

	return entry;
}

// Puts the node on the pool if there is space.
void push_HashtableEntry(HashtableEntry* entry)
{	
	// If the node passed in is null just exit
	if (entry == NULL)
		return;
	// If the pooling isn't supported then just free the node from memory.
	else if (pool == NULL)
	{
		free(entry);	
		return;
	}
	// If the pool exists but is filled then exit.
	else if (pool->size == pool->capacity)
		return;

	// push the node into the pool.
	entry->data = NULL;
	entry->key = 0;
	entry->next = NULL;
	pool->entries[pool->size++] = entry;
}

// Returns an empty hashtable with a capacity which is a power
// of 2. The actual capacity will be greater then or equal to the
// capacity given.
Hashtable* newHashtable(unsigned int capacity)
{
	Hashtable* h = alloc(Hashtable, 1);

	// The size must be a power of 2
	unsigned int actual = 1;
	while (actual < capacity)
		actual <<= 1;

	h->size =  0;
	h->capacity = actual;
	h->entries = calloc(HashtableEntry, actual);

	return h;
}

// Puts an item on the hashtable based on its key. If an item with
// the key already exists on the hashtable then nothing is done.
void hashtable_put(Hashtable* h, unsigned int key, void* item)
{
	if (item == NULL)
		return;

	int hash = key & (h->capacity - 1);	

	HashtableEntry* entry = pop_HashtableEntry();
	entry->key = key;
	entry->data = item;
	// The first item in this entry is now the next
	entry->next = h->entries[hash];
	// This item is set as the first entry
	h->entries[hash] = entry;

	h->size++;
}

// Gets an item from the hashtable based on a key. If an item with
// the key doesn't exist then NULL is returned.
void* hashtable_get(Hashtable* h, unsigned int key)
{
	int hash = key & (h->capacity - 1);

	// If there is no entry at this position then return null
	if (h->entries[hash] == NULL)
		return NULL;
	else
	{
		HashtableEntry* current = h->entries[hash];

		while (current != NULL && current->key != key)
			current = current->next;

		// If the hashed entry in the list doesn't exist then return NULL
		if (current == NULL)
			return NULL;

		return current->data;
	}
}

// Sets an item on the hashtable based on a key. If an item with
// the key doesn't exist then it returns false.
int hashtable_set(Hashtable* h, unsigned int key, void* item)
{
	int hash = key & (h->capacity - 1);

	// If there is no entry at this position then return null
	if (h->entries[hash] == NULL)
		return false;
	else
	{
		HashtableEntry* current = h->entries[hash];

		while (current != NULL && current->key != key)
			current = current->next;

		// If the hashed entry in the list doesn't exist then return NULL
		if (current == NULL)
			return false;

		current->data = item;

		return true;
	}
}

// Removes and returns the entry with the same key. If an item with
// they same key doesn't exist then NULL is returned.
void* hashtable_remove(Hashtable* h, unsigned int key)
{
	int hash = key & (h->capacity - 1);

	// If there is no entry at this position then return null
	if (h->entries[hash] == NULL)
		return NULL;
	else
	{
		HashtableEntry* current = h->entries[hash];
		HashtableEntry* previous = NULL;

		// Iterate through the linked list of entries until the
		// entry with the key is found or the end of the list is met.
		while (current != NULL && current->key != key)
		{
			previous = current;
			current = current->next;
		}

		// If the current entry is null or the key doesn't match
		// the last entry then the entry wasn't found.
		if (current == NULL || current->key != key)
			return NULL;

		// If previous is null then this is the first entry.
		if (previous == NULL)
			h->entries[hash] = current->next;
		// Replace the current entry with the next.
		else
			previous->next = current->next;

		void* data = current->data;
		// If pooling of entries is enabled then pool it, if not then
		// free it from memory.
		push_HashtableEntry(current);

		h->size--;

		return data;		
	}
}

// Returns whether the given key exists in the hashtable.
int hashtable_exists(Hashtable* h, unsigned int key)
{
	int hash = key & (h->capacity - 1);

	// If there is no entry at this position then return null
	if (h->entries[hash] == NULL)
		return false;
	else
	{
		HashtableEntry* current = h->entries[hash];

		while (current != NULL && current->key != key)
			current = current->next;

		if (current != NULL && current->key == key)
			return true;
		else
			return false;
	}
}

// Traverses the hashtable and calls the process method on each item.
void hashtable_traverse(Hashtable* h, void (*process)(void* data))
{
	int i;
	for (i = 0; i < h->capacity; i++)
	{
		HashtableEntry* current = h->entries[i];

		while (current != NULL)
		{
			process(current->data);
			current = current->next;
		}
	}
}

// Displays the contents of the hashtable to the screen given a method
// to convert the item into a string.
void hashtable_display(Hashtable* h, char* (*toString)(void* item))
{
	int i;

	char indexformat[10];
	sprintf(indexformat, "%s%dd)", "%", (int)log(h->size));

	for (i = 0; i < h->capacity; i++)
	{
		if (h->entries[i] == NULL)
			continue;
		
		printf(indexformat, i);
		
		HashtableEntry* current = h->entries[i];
	
		while (current != NULL)
		{
			printf("->%s", toString(current->data));
			current = current->next;
		}
		printf("\n");
	}
}

// Removes all entries from the hashtable.
void hashtable_clear(Hashtable* h)
{
	if (h->size == 0)
		return;

	int i;
	for (i = 0; i < h->capacity; i++)
	{
		HashtableEntry* current = h->entries[i];

		while (current != NULL)
		{
			push_HashtableEntry(current);
			current = current->next;
		}
	}

	h->size = 0;
}

// Removes and frees all entries from the hashtable as well as the table.
void hashtable_free(Hashtable* h)
{
	if (h == NULL)
		return;
	
	hashtable_clear(h);
	free(h->entries);
	free(h);
}
