/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _BINARY_TREE
#define _BINARY_TREE

/**
 * A node contained in a Binary Search Tree that holds generic data and
 * a key used for storage. Every node has a left and right subtree.
 */
typedef struct BinaryTreeNode
{
	// The data contained in this node
	void* data;
	// The key used to insert and remove this node
	unsigned int key;

	// The left child of this tree
	struct BinaryTreeNode* left;
	// The right child of this tree
	struct BinaryTreeNode* right;

} BinaryTreeNode;

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
typedef struct
{
	// The number of children in this binary tree
	unsigned int size;
	// The root node of the binary tree
	BinaryTreeNode* root;

} BinaryTree;

/**
 * Creates a pool of BinaryTreeNodes.
 * 
 * @param capacity => The maximum number of nodes that can be pooled.
 */
void pool_binary(unsigned int capacity);

/**
 * Destroys the pool of BinaryTreeNodes.
 */
void unpool_binary();

/**
 * Returns a new Binary tree with no children.
 */
BinaryTree* newBinaryTree();

/**
 * Adds an item to the binary tree based on its key. If an item
 * with the same key already exists then nothing is done.
 * 
 * Efficiency: O(logn)
 * 
 * @param b => The binary tree to add to.
 * @param key => The key associated with the item to add.
 * @param item => The item to add into the tree.
 */
void binary_add(BinaryTree* b, unsigned int key, void* item);

/**
 * Sets an item in the binary tree based on its key. If an item
 * with the key doesn't exist then false is returned, else the
 * item is set and returns true.
 * 
 * Efficiency: O(logn)
 * 
 * @param b => The binary tree to set an item from.
 * @param key => The key associated with the item to set.
 * @param item => The new item in the tree.
 */
int binary_set(BinaryTree* b, unsigned int key, void* item);

/**
 * Gets an item from the binary tree based on a key. If an item
 * with the same key doesn't exist then NULL is returned.
 * 
 * Efficiency: O(logn)
 * 
 * @param b => The binary tree to get an item from.
 * @param key => The key associated with the item to get.
 * 
 */
void* binary_get(BinaryTree* b, unsigned int key);

/**
 * Removes an item from the binary tree based on a key. If an item
 * with the key doesn't exist then NULL is returned.
 * 
 * Efficiency: O(logn)
 * 
 * @param b => The binary tree to remove from.
 * @param key => The key associated with the item to remove.
 */
void* binary_remove(BinaryTree* b, unsigned int key);

/**
 * Drops an item from the binary tree and all subtrees below it 
 * based on a key. If an item with the key doesn't exist then NULL 
 * is returned and nothing is dropped.
 * 
 * Efficiency: O(logn)
 * 
 * @param b => The binary tree to drop from.
 * @param key => The key associated with the item to drop.
 */
void* binary_drop(BinaryTree* b, unsigned int key);

/**
 * Returns true if an item in the binary tree exists with the same
 * key. If no item's key matches then false is returned.
 * 
 * Efficiency: O(logn)
 * 
 * @param b => The binary tree to check for existence of a key.
 * @param key => The key associated with the item to check for existence.
 */
int binary_exists(BinaryTree* b, unsigned int key);

/**
 * Returns the height of the tree.
 * 
 * Efficiency: O(n)
 * 
 * @param b => The tree to compute the height of.
 */
int binary_getHeight(BinaryTree* b);

/**
 * Performs a depth-first-search on the binary tree and as each node
 * is visited the function 'process' passed in is called with the data
 * for that node.
 * 
 * @param b => The binary tree to traverse using depth-first-searh.
 * @param process => The method that is called every time an item is traversed.
 */
void binary_traverseDepth(BinaryTree* b, void (*process)(void* item));

/**
 * Performs a breadth-first-search on the binary tree and as each node
 * is visited the function 'process' passed in is called with the data
 * for that node.
 * 
 * @param b => The binary tree to traverse using breadth-first-searh.
 * @param process => The method that is called every time an item is traversed.
 */
void binary_traverseBreadth(BinaryTree* b, void (*process)(void* item));

/**
 * Performs a pre-order search on the binary tree and as each node
 * is visited the function 'process' passed in is called with the data
 * for that node.
 * 
 * @param b => The binary tree to traverse using pre-order traversal.
 * @param process => The method that is called every time an item is traversed.
 */
void binary_traversePreOrder(BinaryTree* b, void (*process)(void* item));

/**
 * Performs an in-order search on the binary tree and as each node
 * is visited the function 'process' passed in is called with the data
 * for that node.
 * 
 * @param b => The binary tree to traverse using in-order traversal.
 * @param process => The method that is called every time an item is traversed.
 */
void binary_traverseInOrder(BinaryTree* b, void (*process)(void* item));

/**
 * Performs a post-order search on the binary tree and as each node
 * is visited the function 'process' passed in is called with the data
 * for that node.
 * 
 * @param b => The binary tree to traverse using post-order traversal.
 * @param process => The method that is called every time an item is traversed.
 */
void binary_traversePostOrder(BinaryTree* b, void (*process)(void* item));

/**
 * Displays the binary tree given a max width for the strings returned. Each
 * time an item is about to be printed the toString method is called to get
 * a string representation of the data in the tree.
 * 
 * @param b => The binary tree to display to stdout.
 * @param maxLength => The maximum length of any string of an item to print.
 * @param toString => TThe method that is called for every item to be printed.
 */
void binary_display(BinaryTree* b, int maxLength, char* (*toString)(void* data));

/**
 * Clears the list of all data.
 * 
 * Efficiency: O(n)
 * 
 * @param b => The tree to clear all items from.
 */
void binary_clear(BinaryTree* b);

/**
 * Removes the list completely from memory.
 * 
 * Efficiency: O(n)
 * 
 * @param b => The tree to clear of all items and free from memory.
 */
void binary_free(BinaryTree* b);

#endif /* _BINARY_TREE */
