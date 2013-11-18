/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/


/**
 * A 2-dimensional array class. This simplifies the process of creating a 2d
 * array. There are get and set methods as well as resizing and copying.
 * 
 * @author Philip Diffenderfer
 */

#include "util.h"
#include "array2d.h"

// Initializes a 2-dimensional array of data based on a width and height.
Array2* newArray2(unsigned int width, unsigned int height)
{
	Array2* a = alloc(Array2, 1);

	int i;
	a->e = calloc(void**, height);
	for (i = 0; i < height; i++)
		a->e[i] = calloc(void*, width);

	a->width = width;
	a->height = height;

	return a;
}

// Sets the item in the 2d array based on the y(row) and x(column).
void array2_set(Array2* a, unsigned int y, unsigned int x, void* item)
{
	if (y >= a->height || x >= a->width)
		return;

	a->e[y][x] = item;
}

// Gets the item in the 2d arrat based on the y(row) and x(column).
void* array2_get(Array2* a, unsigned int y, unsigned int x)
{
	if (y >= a->height || x >= a->width)
		return NULL;

	return a->e[y][x];
}

//	Resizes the 2d array to a new size. All items will be preserved unless
//	the size decreases.
void array2_resize(Array2* a, unsigned int width, unsigned int height)
{
	int i;
	a->e = realloc(a->e, void*, height);
	for (i = 0; i < height; i++)
		a->e[i] = realloc(a->e[i], void, width);
}

// Copies this 2d array to another 2d array with a given copy function. The
// copy function is given an item and should return the copy of that item.
Array2* array2_copy(Array2* a, void* (*copy)(void* in))
{
	Array2* result = newArray2(a->width, a->height);

	int x, y;
	for (y = 0; y < a->height; y++)
		for (x = 0; x < a->width; x++)
			if (a->e[y][x] != NULL)
				result->e[y][x] = copy(a->e[y][x]);

	return result;
}

// Clears all the items in the 2d array and sets all spaces to NULL.
void array2_clear(Array2* a)
{
	int x, y;
	for (y = 0; y < a->height; y++)
		for (x = 0; x < a->width; x++)
			a->e[y][x] = NULL;
}

// Clears all the items in the 2d array and frees it from the heap.
void array2_free(Array2* a)
{
	if (a == NULL)
		return;

	int y;
	for (y = 0; y < a->height; y++)
		free(a->e[y]);
	free(a->e);
	free(a);
}

