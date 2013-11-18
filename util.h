/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _UTIL
#define _UTIL

#include <stdlib.h>

// Boolean constants
#define true	1
#define false 	0


// Simple way of allocating memory.
// Example: int* e = alloc(int, 2);
#define alloc(type, size) 			(malloc((size) * sizeof(type)))

// Simple way of allocating memory for arrays so initial data is 0 or NULL.
// Example: int* e = calloc(int 10);
#define calloc(type, size)			(calloc(sizeof(type), size))

// Simple way of resizing or reallocating memory.
// Example: e = realloc(e, int, 100);
#define realloc(ptr, type, size)	(realloc(ptr, (size) * sizeof(type)))


// The max value inbetween numbers that make them equal (due to roundoff errors)
#define EPSILON	0.000001

// The PI constant
#define PI			3.1415926535

// Max and min functions
#define min(a, b) 	((a) < (b) ? (a) : (b))
#define max(a, b)	((a) > (b) ? (a) : (b))

// Equal function using EPSILON
#define equal(a, b)	(((a - b) < EPSILON) && ((a - b) > -EPSILON))

// Determines the log base 2 of a positive integer
unsigned int ilog2(unsigned int n);

#endif /* _UTIL */
