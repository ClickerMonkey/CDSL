/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

/**
 * A Binary Search Tree containing generic data inserted by a key value. The
 * operations that can be performed on a binary search tree are:
 * 
 * Add => Adds an item to the tree based on a key.
 * Set => Tries to set an item in the tree with a matching key.
 * Get => Returns an item on the tree with a matching key.
 * Remove => Removes an item from the tree that has a matching tree.
 * Drop => Removes an item and its subtrees from a tree based on a key.
 * Exists => Returns true if a given key exists in the tree.
 * Traverse => Traverses the items in breadth first, depth first, pre-order,
 * 		post-order, and in-order.
 * Display => Displays the tree structure given a toString method.
 * Clear => Clears all items from the tree.
 * Free => Frees all item front the tree and the tree itself.
 * 
 * @author Philip Diffenderfer
 */

#include <stdio.h>

#include "util.h"
#include "binarytree.h"

/**
 * A pool is a stack like structure that can pop and push BinaryTreeNodes.
 * If there are no BinaryTreeNodes to pop and a request is made then the 
 * pool will allocate a BinaryTreeNodes on the spot. A pool is restricted
 * by a maximum capcity.
 */
typedef struct 
{
	// The current number of nodes available for unpooling.
	unsigned int size;
	// The maximum number of nodes that can be pooled.
	unsigned int capacity;
	// The array of node pointers for pooling/unpooling.
	BinaryTreeNode** nodes;

} Pool;


// The pool to use for any BinaryTree's nodes.
Pool* pool;


// Creates a pool of BinaryTreeNode.
void pool_binary(unsigned int capacity)
{
	pool = alloc(Pool, 1);

	pool->capacity = capacity;
	pool->size = 0;
	pool->nodes = alloc(BinaryTreeNode*, capacity);
}

// Destroys the pool of BinaryTreeNode.
void unpool_binary()
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
BinaryTreeNode* pop_BinaryTreeNode()
{
	// Of pooling isn't supported then just allocate a new one.
	if (pool == NULL)
		return alloc(BinaryTreeNode, 1);

	BinaryTreeNode* node;

	// If there are none on the pool then allocate a new one
	if (pool->size == 0)
	{
		node = alloc(BinaryTreeNode, 1);
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
void push_BinaryTreeNode(BinaryTreeNode* node)
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
	node->left = NULL;
	node->right = NULL;
	pool->nodes[pool->size++] = node;
}


// Returns a new Binary tree with no children.
BinaryTree* newBinaryTree()
{
	BinaryTree* b = alloc(BinaryTree, 1);

	b->root = NULL;
	b->size = 0;

	return b;
}

// Based on the key this will search through the subtree of current for
// a node with the same key. If the key isn't found then the parent of where
// the key should be will be returned
BinaryTreeNode* binary_getNode(BinaryTreeNode* current, unsigned int key)
{
	// If the current node already matches the key then return it
	if (key == current->key)
		return current;

	// A non recursive search for a node
	BinaryTreeNode* parent = current;

	while (current != NULL)
	{	
		if (key == current->key)
			return current;
	
		// Set the parent node of the current node
		parent = current;

		// If the key is less then the current node's key then go through
		// the nodes left subtree
		if (key < current->key)
			current = current->left;
		// Go through the right subtree
		else
			current = current->right;
	}

	// No matching node was found so return the parent.
	return parent;

}

// This will free the node and the nodes left and right subtrees.
void binary_clearNode(BinaryTree* b, BinaryTreeNode* node)
{
	// Free this nodes left and right sides before freeing this node
	if (node->left != NULL)
		binary_clearNode(b, node->left);
	if (node->right != NULL)
		binary_clearNode(b, node->right);

	b->size--;
	// Send it to the pool or free it.
	push_BinaryTreeNode(node);
}

// Adds an item to the binary tree based on its key. If an item
// with the same key already exists then nothing is done.
void binary_add(BinaryTree* b, unsigned int key, void* item)
{
	if (item == NULL)
		return;

	BinaryTreeNode* node = pop_BinaryTreeNode();
	node->key = key;
	node->data = item;
	node->right = node->left = NULL;

	if (b->size == 0)
		b->root = node;
	else
	{
		BinaryTreeNode* parent = binary_getNode(b->root, key);
		
		// If the parent node has the same key then it already exists
		if (key == parent->key)
			return;
		else if (key < parent->key)
			parent->left = node;
		else
			parent->right = node;	
	}

	b->size++;
}

// Sets an item in the binary tree based on its key. If an item
// with the key doesn't exist then false is returned, else the
// item is set and returns true.
int binary_set(BinaryTree* b, unsigned int key, void* item)
{
	if (item == NULL || b->size == 0)
		return false;

	BinaryTreeNode* node = binary_getNode(b->root, key);

	// If the keys match then set it
	if (key != node->key)
		return false;

	node->data = item;
	return true;
}

// Gets an item from the binary tree based on a key. If an item
// with the same key doesn't exist then NULL is returned.
void* binary_get(BinaryTree* b, unsigned int key)
{
	if (b->size == 0)
		return false;

	BinaryTreeNode* node = binary_getNode(b->root, key);

	// If the keys match then set it
	if (key != node->key)
		return NULL;

	return node->data;
}

// Removes an item from the binary tree based on a key. If an item
// with the key doesn't exist then NULL is returned.
void* binary_remove(BinaryTree* b, unsigned int key)
{
	// A non recursive search for a node
	BinaryTreeNode* parent = NULL;
	BinaryTreeNode* current = b->root;
	int left = -1;

	while (current != NULL)
	{	
		if (key == current->key)
			break;
	
		// Set the parent node of the current node
		parent = current;

		// If the key is less then the current node's key then go through
		// the nodes left subtree
		if (key < current->key)
		{
			current = current->left;
			left = true;
		}
		// Go through the right subtree
		else
		{
			current = current->right;
			left = false;
		}
	}

	// No matching node was found so return NULL.
	if (current == NULL)
		return NULL;

	void* item = current->data;

	// If there's no subtrees then just remove this one.
	if (current->left == NULL && current->right == NULL)
	{
		if (left)
			parent->left = NULL;
		else
			parent->right = NULL;
	}
	// If there's no left subtree then move the right subtree up
	else if (current->left == NULL)
	{
		BinaryTreeNode* right = current->right;
		current->left = right->left;
		current->right = right->right;
		current->key = right->key;
		current->data = right->data;

		push_BinaryTreeNode(right);
	}
	else if (current->right == NULL)
	{
		BinaryTreeNode* left = current->left;
		current->left = left->left;
		current->right = left->right;
		current->key = left->key;
		current->data = left->data;

		push_BinaryTreeNode(left);
	}
	// Remove this node and adjust the tree. To find a replacement
	// node go on the left subtree and get the key farthest to the right.
	else
	{
		BinaryTreeNode* before = current;
		BinaryTreeNode* closest = current->left;

		while (closest->right != NULL)
		{
			before = closest;
			closest = closest->right;
		}

		before->right = NULL;
		current->key = closest->key;
		current->data = closest->data;
		
		push_BinaryTreeNode(closest);
	}
	
	b->size--;

	return item;
}

// Drops an item from the binary tree and all subtrees below it 
// based on a key. If an item with the key doesn't exist then NULL 
// is returned and nothing is dropped.
void* binary_drop(BinaryTree* b, unsigned int key)
{
	BinaryTreeNode* node = binary_getNode(b->root, key);

	if (node->key != key)
		return NULL;

	void* item = node->data;

	binary_clearNode(b, node);
	binary_remove(b, key);
	// Correct the 1 to many removes
	b->size++;

	return item;
}

// Returns true if an item in the binary tree exists with the same
// key. If no item's key matches then false is returned.
int binary_exists(BinaryTree* b, unsigned int key)
{
	if (b->size == 0)
		return false;

	BinaryTreeNode* node = binary_getNode(b->root, key);

	return (node->key == key);	
}

// Determines the height of a subtree based on a starting node
int binary_height(BinaryTreeNode* node, int height)
{
	int left = height;
	int right = height;

	if (node->left != NULL)
		left = binary_height(node->left, height + 1);
	if (node->right != NULL)
		right = binary_height(node->right, height + 1);

	return (left > right ? left : right);
}

// Returns the height of the tree.
int binary_getHeight(BinaryTree* b)
{
	if (b->size == 0)
		return 0;

	return binary_height(b->root, 1);
}

// Performs a depth-first-search on the binary tree and as each node
// is visited the function 'process' passed in is called with the data
// for that node.
void binary_traverseDepth(BinaryTree* b, void (*process)(void* item))
{
	// Its the same as the pre-order traversal
	binary_traversePreOrder(b, process);
}

// Performs a breadth-first-search on the binary tree and as each node
// is visited the function 'process' passed in is called with the data
// for that node.
void binary_traverseBreadth(BinaryTree* b, void (*process)(void* item))
{
	if (b->size == 0)
		return;
	// The size of the tree must be larger then 1 to do bfs
	if (b->size == 1)
	{
		process(b->root);
		return;
	}

	// Determine the max size of the queue
	int max = 1 << binary_getHeight(b);
	int mod = max - 1;

	// Use a queue to do a breadth first search
	void** queue = alloc(void*, max);
	int start = 0;
	int end = 0;
	int size = 1;

	// Put the root on the queue
	queue[0] = b->root;

	while (size > 0)
	{
		// Dequeue the first item
		BinaryTreeNode* node = queue[start];
		start = (start + 1) & mod;
		size--;

		// Process the current node's data to the function passed in.
		process(node->data);
	
		// Check the node's left and right subtrees
		if (node->left != NULL)
		{
			end = (end + 1) & mod;
			queue[end] = node->left;
			size++;
		}
		if (node->right != NULL)
		{
			end = (end + 1) & mod;
			queue[end] = node->right;
			size++;
		}
	}
}

// A recursive pre-order traversal
void binary_preorder(BinaryTreeNode* node, void (*process)(void* item))
{
	process(node->data);

	if (node->left != NULL)
		binary_preorder(node->left, process);

	if (node->right != NULL)
		binary_preorder(node->right, process);
}

// Performs a pre-order search on the binary tree and as each node
// is visited the function 'process' passed in is called with the data
// for that node.
void binary_traversePreOrder(BinaryTree* b, void (*process)(void* item))
{
	if (b->size == 0)
		return;

	binary_preorder(b->root, process);
}

// A recursive in-order traversal
void binary_inorder(BinaryTreeNode* node, void (*process)(void* item))
{
	if (node->left != NULL)
		binary_inorder(node->left, process);

	process(node->data);

	if (node->right != NULL)
		binary_inorder(node->right, process);
}

// Performs an in-order search on the binary tree and as each node
// is visited the function 'process' passed in is called with the data
// for that node.
void binary_traverseInOrder(BinaryTree* b, void (*process)(void* item))
{
	if (b->size == 0)
		return;

	binary_inorder(b->root, process);
}

// A recursive pre-order traversal
void binary_postorder(BinaryTreeNode* node, void (*process)(void* item))
{
	if (node->left != NULL)
		binary_postorder(node->left, process);

	if (node->right != NULL)
		binary_postorder(node->right, process);

	process(node->data);
}

// Performs a post-order search on the binary tree and as each node
// is visited the function 'process' passed in is called with the data
// for that node.
void binary_traversePostOrder(BinaryTree* b, void (*process)(void* item))
{
	if (b->size == 0)
		return;

	binary_postorder(b->root, process);
}

// Displays the binary tree given a max width for the strings returned. Each
// time an item is about to be printed the toString method is called to get
// a string representation of the data in the tree.
void binary_display(BinaryTree* b, int maxLength, char* (*toString)(void* data))
{
	// Determine the height so we know how many lines
	int height = binary_getHeight(b);

	if (height == 0)
		return;

	// Create the formatting string for every nod
	char format[10];
	sprintf(format, "%s%ds", "%", maxLength);

	// If the size is 1 then just print out the root and exit
	if (height == 1)
	{
		printf(format, toString(b->root->data));
		return;
	}

	// The maximum size of a level
	int levelMax = 1 << (height - 1);
	// The child level
	BinaryTreeNode** children = calloc(BinaryTreeNode*, levelMax);
	// The current level
	BinaryTreeNode** current = calloc(BinaryTreeNode*, levelMax);

	current[0] = b->root;
	
	// Print out the tree now by performing a breadth-first-search
	int level, offset, padding, i, j;
	for (level = 0; level < height; level++)
	{
		// Calculate the offset of blank space for each first node and
		// The padding between each node at this level
		offset = (1 << (height - level - 1)) - 1;
		padding = ((offset << 1) + 1) * maxLength;
		offset *= maxLength;

		// Print out the offset
		for (i = 0; i < offset; i++)
			printf(" ");

		// The total number of possible nodes on this level
		int total = 1 << level;

		for (j = 0; j < total; j++)
		{
			//If there is no node here do empty space
			if (current[j] == NULL)
				printf(format, "");
			else
				printf(format, toString(current[j]->data));
	
			// Print the empty space between
			if (j < total - 1)
				for (i = 0; i < padding; i++)
					printf(" ");
		}
		
		// Adjust the parent and child node arrays
		if (level < height - 1)
		{
			for (i = 0; i < total; i++)
			{
				if (current[i] != NULL)
				{
					children[i * 2] = current[i]->left;	
					children[i * 2 + 1] = current[i]->right;
				}
				else
				{
					children[i * 2] = children[i * 2 + 1] = NULL;
				}
			}

			BinaryTreeNode** temp = current;
			current = children;
			children = temp;
		}

		printf("\n");
	}

	free(current);
	free(children);
}

// Clears the list of all data.
void binary_clear(BinaryTree* b)
{
	if (b->size == 0)
		return;

	binary_clearNode(b, b->root);

	b->root = NULL;
	b->size = 0;
}

// Removes the list completely from memory.
void binary_free(BinaryTree* b)
{
	if (b == NULL)
		return;

	binary_clear(b);
	free(b);
}
