/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _ARRAY_2D
#define _ARRAY_2D

/**
 * A 2-dimensional array class. This simplifies the process of creating a 2d
 * array. There are get and set methods as well as resizing and copying.
 * 
 * @author Philip Diffenderfer
 */
typedef struct 
{
	// How many rows down
	unsigned int height;
	// How many columns across
	unsigned int width;
	// The data in the array
	void*** e;

} Array2;

/**
 * Initializes a 2-dimensional array of data based on a width and height.
 * 
 * @param width => The number of columns.
 * @param height => The number of rows.
 */
Array2* newArray2(unsigned int width, unsigned int height);

/**
 * Sets the item in the 2d array based on the y(row) and x(column).
 * 
 * Efficiency: O(1)
 * 
 * @param a => The 2d array to set the item into at a row and column
 * @param y => The row to set the item in.
 * @param x => The column to set the item in.
 * @param item => The item to set at the specific row and column.
 */
void array2_set(Array2* a, unsigned int y, unsigned int x, void* item);

/**
 * Gets the item in the 2d arrat based on the y(row) and x(column).
 * 
 * Efficiency: O(1)
 * 
 * @param a => The 2d array to get the item from at a row and column
 * @param y => The row to get the item from.
 * @param x => The column to get the item from.
 */
void* array2_get(Array2* a, unsigned int y, unsigned int x);

/**
 *	Resizes the 2d array to a new size. All items will be preserved unless
 *	the size decreases.
 * 
 * Efficiency: O(1)
 * 
 * @param a => The 2d array to resize.
 * @param width => The new number of columns in the 2d array.
 * @param height => The new number of rows in the 2d array.
 */
void array2_resize(Array2* a, unsigned int width, unsigned int height);

/**
 * Copies this 2d array to another 2d array with a given copy function. The
 * copy function is given an item and should return the copy of that item.
 * 
 * Efficiency: O(w*h)
 * 
 * @param a => The 2d to copy from.
 * @param copy => The method that copies the given item and returns a new one.
 */
Array2* array2_copy(Array2* a, void* (*copy)(void* in));

/**
 *	Clears all the items in the 2d array and sets all spaces to NULL.
 * 
 * Efficiency: O(w*h)
 * 
 * @param a => The 2d array to clear.
 */
void array2_clear(Array2* a);

/**
 *	Clears all the items in the 2d array and frees it from the heap.
 * 
 * Efficiency: O(h)
 * 
 * @param a => The 2d array to free from memory.
 */
void array2_free(Array2* a);

#endif /* _ARRAY_2D */
