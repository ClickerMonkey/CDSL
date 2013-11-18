/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#include "util.h"

// Determines the log base 2 of a number.
unsigned int ilog2(unsigned int n)
{
	unsigned int log2 = 0;
	while ((n >> log2) > 1) 
		++log2;
	return log2;
}
