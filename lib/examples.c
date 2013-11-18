/**
 * Programmer: Philip Diffenderfer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "stack.h"
#include "queue.h"
#include "astack.h"
#include "aqueue.h"
#include "hashtable.h"
#include "binarytree.h"
#include "maxheap.h"
#include "minheap.h"
#include "alist.h"

// Runs the example on how to use the linked-list data structure
void exampleList();
// Runs the example on how to use the stack data structure
void exampleStack();
// Runs the example on how to use the array stack data structure
void exampleArrayStack();
// Runs the example on how to use the queue data structure
void exampleQueue();
// Runs the example on how to use the array queue data structure
void exampleArrayQueue();
// Runs the example on how to use the hashtable data structure
void exampleHashtable();
// Runs the example on how to use the binary search tree data structure
void exampleBinaryTree();
// Runs the example on how to use the maximum heap data structure
void exampleMaxHeap();
// Runs the example on how to use the minimum heap data structure
void exampleMinHeap();
// Runs the example on how to use the array list data structure
void exampleArrayList();

int main(int argc, char* argv[])
{
	// Run the examples
	printf("\nLIST EXAMPLE\n\n");
	exampleList();

	printf("\nSTACK EXAMPLE\n\n");
	exampleStack();

	printf("\nARRAY STACK EXAMPLE\n\n");
	exampleArrayStack();

	printf("\nQUEUE EXAMPLE\n\n");
	exampleQueue();

	printf("\nARRAY QUEUE EXAMPLE\n\n");
	exampleArrayQueue();

	printf("\nHASHTABLE EXAMPLE\n\n");
	exampleHashtable();

	printf("\nBINARY SEARCH TREE EXAMPLE\n\n");
	exampleBinaryTree();

	printf("\nMAX HEAP EXAMPLE\n\n");
	exampleMaxHeap();

	printf("\nMIN HEAP EXAMPLE\n\n");
	exampleMinHeap();

	printf("\nARRAY LIST EXAMPLE\n\n");
	exampleArrayList();

	return 0;
}

void exampleQueue()
{
	// Use pooling for efficiency, if you don't want to use pooling
	// then comment out this line.
	pool_queue(16);

	Queue* Q = newQueue();

	// A queue with strings
	queue_offer(Q, "First");
	queue_offer(Q, "In");
	queue_offer(Q, "First");
	queue_offer(Q, "Out.");
	
	// Peek at the head of the queue
	printf("%s\n", (char*)queue_peek(Q));

	// Traverse through the queue polling each string
	while (!queue_isEmpty(Q))
		printf("%s ", (char*)queue_poll(Q));
	printf("\n");


	// A queue with integers, primitive data types require some trickyness
	queue_clear(Q);
	int x[] = {1, 2};
	int y = 3;
	queue_offer(Q, &x[0]);
	queue_offer(Q, &x[1]);
	queue_offer(Q, &y);
	
	while (!queue_isEmpty(Q))
		// You first need to cast it using (int*) and since its a pointer to
		// an integer you need to get the value of the pointer using *
		// You could similarly use:
		// 	int* z = queue_poll(Q);
		//		printf("%d ", *z);
		printf("%d ", *((int*)queue_poll(Q)));

	printf("\n");
	
	// This will clear the queue of any nodes and pool them and then free
	// the queue itself from memory
	queue_free(Q);
	
	// If you're not using pooling this can be commented out. This will
	// free all pooled nodes from memory. Always call this at the end 
	// of using any Queue.
	unpool_queue();
}

void exampleArrayQueue()
{
	ArrayQueue* Q = newArrayQueue(8);

	// A queue with strings
	aqueue_offer(Q, "First");
	aqueue_offer(Q, "In");
	aqueue_offer(Q, "First");
	aqueue_offer(Q, "Out.");
	
	// Peek at the head of the queue
	printf("%s\n", (char*)aqueue_peek(Q));

	// Traverse through the queue polling each string
	while (!aqueue_isEmpty(Q))
		printf("%s ", (char*)aqueue_poll(Q));
	printf("\n");

	// A queue with integers, primitive data types require some trickyness
	aqueue_clear(Q);
	int x[] = {1, 2};
	int y = 3;
	aqueue_offer(Q, &x[0]);
	aqueue_offer(Q, &x[1]);
	aqueue_offer(Q, &y);
	
	while (!aqueue_isEmpty(Q))
		// You first need to cast it using (int*) and since its a pointer to
		// an integer you need to get the value of the pointer using *
		// You could similarly use:
		// 	int* z = queue_poll(Q);
		//		printf("%d ", *z);
		printf("%d ", *((int*)aqueue_poll(Q)));

	printf("\n");
	
	// Fill it up and resize it if an offer has failed
	char* letters[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"};
	for (y = 0; y < 11; y++)
		aqueue_offerf(Q, letters[y]);

	while (!aqueue_isEmpty(Q))
		printf("%s ", (char*)aqueue_poll(Q));
	printf("\n");

	// This will clear the queue of any nodes and pool them and then free
	// the queue itself from memory
	aqueue_free(Q);
}

void exampleStack()
{
	// Use pooling for efficiency, if you don't want to use pooling
	// then comment out this line.
	pool_stack(16);

	Stack* S = newStack();

	// A stack with strings
	stack_push(S, "Out.");
	stack_push(S, "First");
	stack_push(S, "In");
	stack_push(S, "Last");

	// Peek at the top of the stack
	printf("%s\n", (char*)stack_peek(S));

	// Traverse through the stack popping each string
	while (!stack_isEmpty(S))
		printf("%s ", (char*)stack_pop(S));
	printf("\n");

	// Fill up the stack and then clear it.
	stack_push(S, "A");
	stack_push(S, "B");
	stack_push(S, "C");
	int size = S->size;
	
	stack_clear(S);
	if (stack_isEmpty(S))
		printf("The Stack had %d items but now has 0\n", size); 

	// This will clear the stack of any nodes and pool them and then free
	// the stack itself from memory
	stack_free(S);
	
	// If you're not using pooling this can be commented out. This will
	// free all pooled nodes from memory. Always call this at the end 
	// of using any Stack.
	unpool_stack();
}

void exampleArrayStack()
{
	ArrayStack* S = newArrayStack(8);

	// A stack with strings
	astack_push(S, "Out.");
	astack_push(S, "First");
	astack_push(S, "In");
	astack_push(S, "Last");

	// Peek at the top of the stack
	printf("%s\n", (char*)astack_peek(S));

	// Traverse through the stack popping each string
	while (!astack_isEmpty(S))
		printf("%s ", (char*)astack_pop(S));
	printf("\n");

	// Fill up the stack and then clear it.
	astack_push(S, "A");
	astack_push(S, "B");
	astack_push(S, "C");
	int size = S->size;
	
	astack_clear(S);
	if (astack_isEmpty(S))
		printf("The Stack had %d items but now has 0\n", size); 

	// Fill it up and resize it if a push has failed
	char* letters[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"};
	int x;
	for (x = 0; x < 11; x++)
		astack_pushf(S, letters[x]);

	while (!astack_isEmpty(S))
		printf("%s ", (char*)astack_pop(S));
	printf("\n");

	// This will clear the stack of any nodes and pool them and then free
	// the stack itself from memory
	astack_free(S);
}

void displayStrings(List* l)
{
	list_start(l);
	while (list_hasNext(l))
		printf("%s", (char*)list_next(l));
	printf("\n");
}

void displayIntegers(List* l)
{
	list_start(l);
	while (list_hasNext(l))
		printf("%d ", *((int*)list_next(l)));
	printf("\n");
}

void exampleList()
{
	// Use pooling for efficiency, if you don't want to use pooling
	// then comment out this line.
	pool_list(16);

	List* L = newList();

	list_add(L, "a");
	list_add(L, "b");
	list_add(L, "c");
	list_add(L, "d");
	list_add(L, "e");
	list_add(L, "f");
	
	// Display the current list
	displayStrings(L);		//ABCDEF

	// Remove first item
	list_removeFirst(L);
	displayStrings(L);		//BCDEF
	
	// Add first item back
	list_addFirst(L, "a");
	displayStrings(L);

	list_clear(L);
	if (list_isEmpty(L))
		printf("List was cleared.\n");

	// Add some strings and remove all that begin with -
	int nums[] = {1, 2, 3, 4, 6, 7, 8};
	int x;
	for (x = 0; x < 7; x++)
		list_add(L, &nums[x]);

	displayIntegers(L);

	list_start(L);
	while (list_hasNext(L))
	{
		// get does not move the current node
		x = *((int*)list_peek(L));
		if (x % 2 == 0)
			// remove will remove the node from the list altogether and
			// return the data removed.
			list_remove(L);
		else
			// next will just goto the next node and return the data.
			list_next(L);
	}
	
	// Print out the odd numbers
	displayIntegers(L);

	// Try removing all while traversing
	list_start(L);
	while (list_hasNext(L))
		list_remove(L);
	
	displayIntegers(L);

	if (L->first == NULL && L->last == NULL && L->size == 0)
		printf("All cleaned up!\n");

	// Traverse through an array of strings and find any that start
	// with . and after it add 0 and add one before it that is -
	list_add(L, ".1");
	list_add(L, " two ");
	list_add(L, ".3");
	list_add(L, " four ");
	list_add(L, ".5");

	displayStrings(L);
	
	list_start(L);
	char* c;
	while (list_hasNext(L))
	{	
		c = (char*)list_peek(L);

		if (c[0] == '.')
		{
			list_insertBefore(L, "-");
			list_insertAfter(L, "0");
		}

		list_next(L);
	}
	displayStrings(L);

	char* first = (char*)L->first->data;
	char* last = (char*)L->last->data;
	if (first[0] == '-' && last[0] == '+')
		printf("Insertions correct.\n");

	// This will clear the list of any nodes and pool them and then free
	// the list itself from memory
	list_free(L);
	
	// If you're not using pooling this can be commented out. This will
	// free all pooled nodes from memory. Always call this at the end 
	// of using any List.
	unpool_list();
}

char* toString(void* data)
{
	return (char*)data;
}

void exampleHashtable()
{
	// Use pooling for efficiency, if you don't want to use pooling
	// then comment out this line.
	pool_hashtable(16);

	Hashtable* H = newHashtable(8);

	hashtable_put(H, 23, "Hello");
	hashtable_put(H, 16, "World");
	// Hash another entry to 0 (besides World)
	hashtable_put(H, 8, "Again");
	hashtable_put(H, 24, "And again");
	hashtable_put(H, 40, "And again again");

	// Print out the size
	printf("The hashtable has %d entries.\n", H->size);

	hashtable_display(H, &toString);

	// Test the get function based on the keys
	printf("%s ", (char*)hashtable_get(H, 23));
	printf("%s\n", (char*)hashtable_get(H, 16));
	printf("%s\n", (char*)hashtable_get(H, 8));
	printf("%s\n", (char*)hashtable_get(H, 24));

	// Try one that doesn't exist and goes to a completely empty entry
	if (hashtable_get(H, 1) == NULL)
		printf("Entry with key 1 not found.\n");
	// Try one that doesn't exist and goes to an existing entry
	if (hashtable_get(H, 32) == NULL)
		printf("Entry with key 32 not found.\n");

	// Test exists on all added data
	if (hashtable_exists(H, 23) && hashtable_exists(H, 16) && 
		 hashtable_exists(H, 8) && hashtable_exists(H, 24) && hashtable_exists(H, 40))
		printf("The hashtable's entries are sound.\n");

	// Test removing of an entry that doesn't exist in the list
	printf("Removed: %s\n", (char*)hashtable_remove(H, 32));
	// Test removing of the first entry in the list
	printf("Removed: %s\n", (char*)hashtable_remove(H, 16));
	// Test removing of a middle entry in the list
	printf("Removed: %s\n", (char*)hashtable_remove(H, 24));
	// Test removing of an end entry in the list
	printf("Removed: %s\n", (char*)hashtable_remove(H, 40));
	// Test removing of the only entry
	printf("Removed: %s\n", (char*)hashtable_remove(H, 8));
	
	// Test setting the last entry remaining
	printf("Before: %s", (char*)hashtable_get(H, 23));
	hashtable_set(H, 23, "Changed!");
	printf("\tAfter: %s\n", (char*)hashtable_get(H, 23));

	// Test the set method for a non existing key
	if (!hashtable_set(H, 45, "Foo"))
		printf("Cannot set 45 to 'Foo', key 45 doesn't exist.\n");

	// Print out the size
	printf("The hashtable has %d entries.\n", H->size);
	
	// Clear the table and print out the size
	hashtable_clear(H);
	printf("Cleared. The hashtable has %d entries.\n", H->size);
	
	// This will clear the list of any nodes and pool them and then free
	// the list itself from memory
	hashtable_free(H);
	
	// If you're not using pooling this can be commented out. This will
	// free all pooled nodes from memory. Always call this at the end 
	// of using any List.
	unpool_hashtable();
}

void process(void* item)
{
	printf("%s", (char*)item);
}

void exampleBinaryTree()
{	
	// Use pooling for efficiency, if you don't want to use pooling
	// then comment out this line.
	pool_binary(32);
	
	BinaryTree* T = newBinaryTree();
	
	//             H
	//       D          L     
	//   B     F     J     N
	// A  C  E  G  I  K  M  O
	// Insert the data into the tree
	binary_add(T, 'H'-'A', "H");
	binary_add(T, 'D'-'A', "D");
	binary_add(T, 'L'-'A', "L");
	binary_add(T, 'B'-'A', "B");
	binary_add(T, 'F'-'A', "F");
	binary_add(T, 'J'-'A', "J");
	binary_add(T, 'N'-'A', "N");
	binary_add(T, 'A'-'A', "A");
	binary_add(T, 'C'-'A', "C");
	binary_add(T, 'E'-'A', "E");
	binary_add(T, 'G'-'A', "G");
	binary_add(T, 'I'-'A', "I");
	binary_add(T, 'K'-'A', "K");
	binary_add(T, 'M'-'A', "M");
	binary_add(T, 'O'-'A', "O");

	binary_display(T, 1, &toString);

	printf("Size: %d\n", T->size);
	printf("Height: %d\n", binary_getHeight(T));

	printf("Traversals:");

	// Display the tree inorder
	printf("\n%16s: ", "In Order");
	binary_traverseInOrder(T, &process);

	printf("\n%16s: ", "Pre Order");
	binary_traversePreOrder(T, &process);

	printf("\n%16s: ", "Post Order");
	binary_traversePostOrder(T, &process);

	printf("\n%16s: ", "Breadth First");
	binary_traverseBreadth(T, &process);

	printf("\n%16s: ", "Depth First");
	binary_traverseDepth(T, &process);

	printf("\n");

	// Remove a node with 2 subtree(s)
	printf("Removing L:\n");
	binary_remove(T, 'L'-'A');
	binary_display(T, 1, &toString);
	printf("New Size: %d\n", T->size);
	// Remove a node with 0 subtree(s) = leaf
	printf("Removing A:\n");
	binary_remove(T, 'A'-'A');
	binary_display(T, 1, &toString);
	printf("New Size: %d\n", T->size);
	// Remove a node with 1 subtree(s) = left
	printf("Removing J:\n");
	binary_remove(T, 'J'-'A');
	binary_display(T, 1, &toString);
	printf("New Size: %d\n", T->size);
	// Remove a node with 1 subtree(s) = right
	printf("Removing B:\n");
	binary_remove(T, 'B'-'A');
	binary_display(T, 1, &toString);
	printf("New Size: %d\n", T->size);
	// Remove a node with 1 subtree(s) = right
	printf("Dropping N:\n");
	binary_drop(T, 'N'-'A');
	binary_display(T, 1, &toString);
	printf("New Size: %d\n", T->size);

	// Remove the bottom level
	printf("Removing bottom level:\n");
	binary_remove(T, 'E'-'A');
	binary_remove(T, 'G'-'A');
	binary_display(T, 1, &toString);
	printf("New Size: %d\n", T->size);
	printf("New Height: %d\n", binary_getHeight(T));

	// Set F to A
	printf("Setting F to E:\n");
	binary_set(T, 'F'-'A', "E");
	binary_display(T, 1, &toString);
	
	binary_clear(T);
	if (T->size == 0)
		printf("Binary Tree Cleared\n");

	// Create another tree with larger strings
	binary_add(T, 3, "Dog");
	binary_add(T, 0, "Ant");
	binary_add(T, 1, "Bat");
	binary_add(T, 2, "Camel");
	binary_add(T, 4, "Eel");
	binary_add(T, 5, "Fish");
	binary_display(T, 5, &toString);

	binary_free(T);
	
	// If you're not using pooling this can be commented out. This will
	// free all pooled nodes from memory. Always call this at the end 
	// of using any List.
	unpool_binary();
}

void exampleMaxHeap()
{
	// Use pooling for efficiency, if you don't want to use pooling
	// then comment out this line.
	pool_maxheap(32);
	
	MaxHeap* H = newMaxHeap(31);
	
	maxheap_add(H, 99, "99");
	maxheap_add(H, 45, "45");
	maxheap_add(H, 57, "57");
	maxheap_add(H, 12, "12");
	maxheap_add(H, 87, "87");
	maxheap_add(H, 42, "42");
	maxheap_add(H, 67, "67");
	
	maxheap_display(H, 2, &toString);

	printf("Pop: '%s'\n", (char*)maxheap_popMax(H));

	maxheap_display(H, 2, &toString);

	printf("Pop: '%s'\n", (char*)maxheap_popMax(H));

	maxheap_display(H, 2, &toString);

	printf("Update 45 to 91\n");
	maxheap_update(H, 45, 91);
	maxheap_set(H, 91, "91");

	maxheap_display(H, 2, &toString);

	printf("Update 91 to 1\n");
	maxheap_update(H, 91, 1);
	maxheap_set(H, 1, "1");
	
	maxheap_display(H, 2, &toString);

	printf("Add 50\n");
	maxheap_add(H, 50, "50");
	
	maxheap_display(H, 2, &toString);

	printf("Pop: '%s'\n", (char*)maxheap_popMax(H));

	maxheap_display(H, 2, &toString);

	printf("Pop: '%s'\n", (char*)maxheap_popMax(H));
	printf("Pop: '%s'\n", (char*)maxheap_popMax(H));
	printf("Pop: '%s'\n", (char*)maxheap_popMax(H));
	printf("Pop: '%s'\n", (char*)maxheap_popMax(H));

	maxheap_display(H, 2, &toString);

	maxheap_clear(H);

	printf("\n");
	// Build a much bigger heap
	int total = 21;
	int keys[] = {0, 23, 3, 6, 41, 17, 21, 8, 9, 68, 2, 1, 34, 29, 38, 11, 15, 16, 45, 65, 39};
	char* items[] = {"0", "23", "3", "6", "41", "17", "21", "8", "9", "68", "2", "1", "34", "29", "38", "11", "15", "16", "45", "65", "39"};

	while (--total >= 0)
		maxheap_add(H, keys[total], items[total]);

	maxheap_display(H, 2, &toString);
	
	printf("Popping.. ");
	while (!maxheap_isEmpty(H))
		printf("%s ", (char*)maxheap_popMax(H));
	printf("\n");

	maxheap_free(H);

	
	// If you're not using pooling this can be commented out. This will
	// free all pooled nodes from memory. Always call this at the end 
	// of using any List.
	unpool_maxheap();
}

void exampleMinHeap()
{
	// Use pooling for efficiency, if you don't want to use pooling
	// then comment out this line.
	pool_minheap(32);
	
	MinHeap* H = newMinHeap(31);
	
	minheap_add(H, 99, "99");
	minheap_add(H, 45, "45");
	minheap_add(H, 57, "57");
	minheap_add(H, 12, "12");
	minheap_add(H, 87, "87");
	minheap_add(H, 42, "42");
	minheap_add(H, 67, "67");
	
	minheap_display(H, 2, &toString);

	printf("Pop: '%s'\n", (char*)minheap_popMin(H));

	minheap_display(H, 2, &toString);

	printf("Pop: '%s'\n", (char*)minheap_popMin(H));

	minheap_display(H, 2, &toString);

	printf("Update 45 to 91\n");
	minheap_update(H, 45, 91);
	minheap_set(H, 91, "91");

	minheap_display(H, 2, &toString);

	printf("Update 91 to 1\n");
	minheap_update(H, 91, 1);
	minheap_set(H, 1, "1");
	
	minheap_display(H, 2, &toString);

	printf("Add 50\n");
	minheap_add(H, 50, "50");
	
	minheap_display(H, 2, &toString);

	printf("Pop: '%s'\n", (char*)minheap_popMin(H));

	minheap_display(H, 2, &toString);

	printf("Pop: '%s'\n", (char*)minheap_popMin(H));
	printf("Pop: '%s'\n", (char*)minheap_popMin(H));
	printf("Pop: '%s'\n", (char*)minheap_popMin(H));
	printf("Pop: '%s'\n", (char*)minheap_popMin(H));

	minheap_display(H, 2, &toString);

	minheap_clear(H);

	printf("\n");
	// Build a much bigger heap
	int total = 21;
	int keys[] = {0, 23, 3, 6, 41, 17, 21, 8, 9, 68, 2, 1, 34, 29, 38, 11, 15, 16, 45, 65, 39};
	char* items[] = {"0", "23", "3", "6", "41", "17", "21", "8", "9", "68", "2", "1", "34", "29", "38", "11", "15", "16", "45", "65", "39"};

	while (--total >= 0)
		minheap_add(H, keys[total], items[total]);

	minheap_display(H, 2, &toString);
	
	printf("Popping.. ");
	while (!minheap_isEmpty(H))
		printf("%s ", (char*)minheap_popMin(H));
	printf("\n");

	minheap_free(H);

	
	// If you're not using pooling this can be commented out. This will
	// free all pooled nodes from memory. Always call this at the end 
	// of using any List.
	unpool_minheap();
}

int equals(void* a, void* b)
{
	return (strcmp((char*)a, (char*)b) == 0);
}

void exampleArrayList()
{
	ArrayList* l = newArrayList(4);

	alist_add(l, "Aye");
	alist_add(l, "Bee");
	alist_add(l, "Sea");
	alist_add(l, "Dee");
	alist_add(l, "Eee");
	alist_add(l, "Eff");
	alist_add(l, "Gee");
	alist_add(l, "Ach");
	alist_add(l, "Eye");
	alist_add(l, "Jay");
	alist_add(l, "Kay");
	alist_add(l, "Ell");

	printf("Size: %d\n", l->size);

	alist_traverseForward(l, &process);
	printf("\n");

	printf("Remove 'Sea'\n");
	alist_remove(l, "Sea", equals);
	alist_traverseForward(l, &process);
	printf("\n");

	printf("Remove at 0\n");
	alist_removeAt(l, 0);
	alist_traverseForward(l, &process);
	printf("\n");

	printf("Remove at size\n");
	alist_removeAt(l, l->size - 1);
	alist_traverseForward(l, &process);
	printf("\n");

	printf("Insert 'Aye' at 0\n");
	alist_insert(l, "Aye", 0);
	alist_traverseForward(l, &process);
	printf("\n");

	printf("Insert 'Ell' at size\n");
	alist_insert(l, "Ell", l->size);
	alist_traverseForward(l, &process);
	printf("\n");

	printf("Insert 'Sea' at 3\n");
	alist_insert(l, "Sea", 2);
	alist_traverseForward(l, &process);
	printf("\n");

	printf("0: '%s'\n", (char*)alist_get(l, 0));
	printf("3: '%s'\n", (char*)alist_get(l, 3));

	alist_free(l);
}
