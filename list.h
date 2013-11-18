/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _LIST
#define _LIST

/**
 * This is a node for a singly linked-list that holds generic data.
 */
typedef struct ListNode
{
	// The data contained in this node
	void* data;
	// The next node in the list
	struct ListNode* next;

} ListNode;

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
typedef struct
{
	// The number of elements in this list.
	int size;

	// The first node in this list.
	ListNode* first;
	// The last node in this list.
	ListNode* last;

	// The current node being traversed.
	ListNode* current;
	// The previous node being traversed.
	ListNode* previous;

} List;

/**
 * Creates a pool of ListNodes.
 * 
 * @param capacity => The maximum number of nodes that can be pooled.
 */
void pool_list(unsigned int capacity);

/**
 * Destroys the pool of ListNodes.
 */
void unpool_list();


/**
 * Returns a new List with no items, allocated to the heap.
 */
List* newList();

/**
 * Returns the i'th item in the list.
 * 
 * Efficiency: O(index)
 * 
 * @param l => The list to get from.
 * @param index => The index of the item to return in the list.
 */
void* list_get(List* l, unsigned int index);

/**
 * This will add an item to the end of the list.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list to add to.
 * @param data => The generic data to add to the end of the list.
 */
void list_add(List* l, void* data);

/**
 * This will add an item to the beginning of the list.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list to add to.
 * @param data => The generic data to add to the beginning of the list.
 */
void list_addFirst(List* l, void *data);

/**
 * This will remove and return the item on the beginning of the list.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list to remove the first item from.
 */
void* list_removeFirst(List* l);

/**
 * Returns true if this list has no items.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list to check for emptiness.
 */
int list_isEmpty(List* l);


/**
 * Starts the traversing of the linked list
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list to start traversing.
 */
void list_start(List* l);

/**
 * During list traversal this will return the current item without going to the next.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list currently being traversed to return the current item.
 */
void* list_peek(List* l);

/**
 * During list traversal this goes to the next item and returns it.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list to proceed to the next item during traversal.
 */
void* list_next(List* l);

/**
 * During list traversal this removes the current item from the 
 * list and returns it.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list to remove the current item during traversal.
 */
void* list_remove(List* l);

/**
 * During list traveral this will insert an item before the current item.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list to insert into before the current item during traversal.
 * @param data => The generic data to insert before the current item.
 */
void list_insertBefore(List* l, void* data);

/**
 * During list traveral this will insert an item before the current item.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list to insert into after the current item during traversal.
 * @param data => The generic data to insert after the current item.
 */
void list_insertAfter(List* l, void* data);

/**
 * During list traversal this returns whether there are more items 
 * to traverse.
 * 
 * Efficiency: O(1)
 * 
 * @param l => The list being traversed.
 */
int list_hasNext(List* l);

/**
 * Traverse the list without affecting it starting at the front of the
 * list and moving towards the back. Each item traversed will be sent
 * through the process method.
 * 
 * Efficiency: O(n)
 * 
 * @param l => The list to traverse.
 * @param process => The method that is called every time an item is traversed.
 */
void list_traverse(List* l, void (*process)(void* item));

/**
 * Clears the list of all data.
 * 
 * Efficiency: O(n)
 * 
 * @param l => The list to clear of all items.
 */
void list_clear(List* l);

/**
 * Removes the list completely from memory.
 * 
 * Efficiency: O(n)
 * 
 * @param l => The list to clear and free from memory.
 */
void list_free(List* l);

#endif /* _LIST */
