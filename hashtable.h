/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _HASHTABLE
#define _HASHTABLE

/**
 * An entry for an open hashtable which contains the entries key
 * (hashed value), the data contained at this key, and the next entry
 * that has been hashed to the exact same position if it exists.
 */
typedef struct HashtableEntry
{
	// The data contained in this node
	void* data;
	// The key used to sort this node
	unsigned int key;
	// The next node hashed to the same position.
	struct HashtableEntry* next;

} HashtableEntry;

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
typedef struct
{
	// The number of items in this hashtable.
	unsigned int size;
	// The maximum number of base entries in the hashtable.
	unsigned int capacity;
	// The array of entries that make up this hashtable.
	HashtableEntry** entries;

} Hashtable;


/**
 * Creates a pool of HashtableEntries.
 * 
 * @param capacity => The maximum number of entries that can be pooled.
 */
void pool_hashtable(unsigned int capacity);

/**
 * Destroys the pool of HashtableEntries.
 */
void unpool_hashtable();

/**
 * Returns an empty hashtable with a capacity which is a power
 * of 2. The actual capacity will be greater then or equal to the
 * capacity given.
 * 
 * @param capacity => The maximum places on the table to put entries.
 */
Hashtable* newHashtable(unsigned int capacity);

/**
 * Puts an item on the hashtable based on its key. If an item with
 * the key already exists on the hashtable then nothing is done.
 * 
 * Efficiency: O(m) where m is how many entries were already hashed 
 * 	to the same position.
 * 	
 * @param h => The hashtable to put the item into.
 * @param key => The key used to determine the place in the hashtable.
 * @param item => The item to put into an entry in the hashtable.
 */
void hashtable_put(Hashtable* h, unsigned int key, void* item);

/**
 * Gets an item from the hashtable based on a key. If an item with
 * the key doesn't exist then NULL is returned.
 * 
 * Efficiency: O(m) where m is how many entries were already hashed 
 * 	to the same position.
 * 	
 * @param h => The hashtable to get an item from.
 * @param key => The key used to find the item based on an entry place.
 */
void* hashtable_get(Hashtable* h, unsigned int key);

/**
 * Sets an item on the hashtable based on a key. If an item with
 * the key doesn't exist then it returns false.
 * 
 * Efficiency: O(m) where m is how many entries were already hashed 
 * 	to the same position.
 * 	
 * @param h => The hashtable to update an entries item.
 * @param key => The key used to determine the place in the hashtable.
 * @param item => The new item to update the entry in the hashtable.
 */
int hashtable_set(Hashtable* h, unsigned int key, void* item);

/**
 * Removes and returns the entry with the same key. If an item with
 * they same key doesn't exist then NULL is returned.
 * 
 * Efficiency: O(m) where m is how many entries were already hashed 
 * 	to the same position.
 * 	
 * @param h => The hashtable to remove an item from.
 * @param key => The key used to determine the place in the hashtable.
 */
void* hashtable_remove(Hashtable* h, unsigned int key);

/**
 * Returns whether the given key exists in the hashtable.
 * 
 * Efficiency: O(m) where m is how many entries were already hashed 
 * 	to the same position.
 * 	
 * @param h => The hashtable to search through for key existence.
 * @param key => The key of an entry to determine existence of.
 */
int hashtable_exists(Hashtable* h, unsigned int key);

/**
 * Traverses the hashtable and calls the process method on each item.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The hashtable to traverse.
 * @param process => The method that is called every time an item is traversed.
 */
void hashtable_traverse(Hashtable* h, void (*process)(void* data));

/**
 * Displays the contents of the hashtable to the screen given a method
 * to convert the item into a string.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The hashtable to display to stdout.
 * @param toString => The method that is called for every item to be printed.
 */
void hashtable_display(Hashtable* h, char* (*toString)(void* item));

/**
 * Removes all entries from the hashtable.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The hashtable to clear all entries from.
 */
void hashtable_clear(Hashtable* h);

/**
 * Removes and frees all entries from the hashtable as well as the table.
 * 
 * Efficiency: O(n)
 * 
 * @param h => The hashtable to free from memory.
 */
void hashtable_free(Hashtable* h);

#endif /* _HASHTABLE */
