/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

/**
 * A 2-dimensional line with a starting and ending point.
 *
 * @author Philip Diffenderer
 */

#include <math.h>

#include "util.h"
#include "line.h"


// Initializes a new line with its starting and ending points.
Line* newLine(Vector* start, Vector* end)
{
	Line* l = alloc(Line, 1);

	l->start = (start != NULL ? start : emptyVector());
	l->end = (end != NULL ? end : emptyVector());

	return l;
}

// Sets the starting and ending points of the line.
void line_set(Line* l, double x1, double y1, double x2, double y2)
{
	l->start->x = x1;
	l->start->y = y1;
	l->end->x = x2;
	l->end->y = y2;
}

// Sets the starting and ending points of the line.
void line_setV(Line* l, Vector* start, Vector* end)
{
	l->start->x = start->x;
	l->start->y = start->y;
	l->end->x = end->x;
	l->end->y = end->y;
}

// Sets the start point of the line.
void line_setStart(Line* l, double x, double y)
{
	l->start->x = x;
	l->start->y = y;
}

// Sets the end point of the line.
void line_setEnd(Line* l, double x, double y)
{
	l->end->x = x;
	l->end->y = y;
}

// Returns the normal of the line. A normal is a vector tangent
// to the line with a length of 1.0
void line_getNormal(Line* l, Vector* out)
{
	double dx, dy, sq, d;
	dx = l->end->x - l->start->x;
	dy = l->end->y - l->start->y;
	sq = dx * dx + dy * dy;
	
	if (sq == 0.0)
		return;

	d = 1.0 / sqrt(sq);
	out->x = -dy * d;
	out->y = dx * d;
}

// Returns the difference between the start and end points.
void line_getDiff(Line* l, Vector* out)
{
	out->x = (l->end->x - l->start->x);
	out->y = (l->end->y - l->start->y);
}

// Returns the mid point of the line.
void line_getMid(Line* l, Vector* out)
{
	out->x = (l->end->x + l->start->x) * 0.5;
	out->y = (l->end->y + l->start->y) * 0.5;
}

// Gets a point on the axis of the line 'delta' away from start. Where
// the point returned is at the start point if delta is 0.0 and if
// delta is 1.0 then its at the end point.
void line_getPoint(Line* l, double delta, Vector* out)
{
	double dx = (l->end->x - l->start->x);
	double dy = (l->end->y - l->start->y);
	out->x = dx * delta + l->start->x;
	out->y = dy * delta + l->start->y;
}

// Returns the point thats on the axis of the line and the line between
// this point and the given vector is perpendicular to the line itself.
void line_project(Line* l, Vector* v, Vector* out)
{
	line_getPoint(l, line_getDelta(l, v), out);
}

// Returns a point on the line thats closest ot v. The point returned is
// between the start and end points.
void line_closest(Line* l, Vector* v, Vector* out)
{
	double delta = line_getDelta(l, v);
	if (delta > 1.0) delta = 1.0;
	if (delta < 0.0) delta = 0.0;
	line_getPoint(l, delta, out);
}

// Returns the 'delta' the vector is on the axis between the start and 
// end points.
double line_getDelta(Line* l, Vector* v)
{
	double dx, dy, sx, sy, sq, d;
	dx = l->end->x - l->start->x;
	dy = l->end->y - l->start->y;
	sq = dx * dx + dy * dy;

	if(sq == 0.0)
		return 0.0;

	d = 1.0 / sqrt(sq);
	sx = (v->x - l->start->x) * dx;
	sy = (v->y - l->start->y) * dy;

	return (sx + sy) * d;
}

// Returns the length of the line.
double line_getLength(Line* l)
{
	double dx = l->end->x - l->start->x;
	double dy = l->end->y - l->start->y;
	return sqrt(dx * dx + dy * dy);
}

// Returns the length of the line squared.
double line_getLengthSq(Line* l)
{
	double dx = l->end->x - l->start->x;
	double dy = l->end->y - l->start->y;
	return (dx * dx + dy * dy);
}

// Returns the signed distance between the line's axis and some vector.
double line_signedDistance(Line* l, Vector* v)
{	
	double dx, dy, sx, sy, sq, d;
	dx = l->end->x - l->start->x;
	dy = l->end->y - l->start->y;
	sq = dx * dx + dy * dy;

	if (sq == 0.0)
		return 0.0;

	d = 1.0 / sqrt(sq);
	sx = (l->start->y - v->y) * dx;
	sy = (l->start->x - v->x) * dy;

	return (sy - sx) * d;
}

// Returns true if the vector is above the line (on the same side as the normal).
int line_isAbove(Line* l, Vector* v)
{
	double dx, dy, sx, sy;
	dx = l->end->x - l->start->x;
	dy = l->end->y - l->start->y;
	sx = (l->start->y - v->y) * dx;
	sy = (l->start->x - v->x) * dy;
	return sx < sy;
}

// Returns true if the vector is below the line (on the opposite side of the normal).
int line_isBelow(Line* l, Vector* v)
{
	double dx, dy, sx, sy;
	dx = l->end->x - l->start->x;
	dy = l->end->y - l->start->y;
	sx = (l->start->y - v->y) * dx;
	sy = (l->start->x - v->x) * dy;
	return sx > sy;
}

// Returns true if the vector is atleast EPSILON away from the line.
int line_isOn(Line* l, Vector* v)
{
	double dx, dy, sx, sy;
	dx = l->end->x - l->start->x;
	dy = l->end->y - l->start->y;
	sx = (l->start->y - v->y) * dx;
	sy = (l->start->x - v->x) * dy;
	return abs(sx - sy) < EPSILON;
}

// Returns true if the vector is between the two axis perpendicular to the
// start and end points.
int line_inBounds(Line* l, Vector* v)
{	
	double dx, dy, sq, sx, sy, d;
	dx = l->end->x - l->start->x;
	dy = l->end->y - l->start->y;
	sq = dx * dx + dy * dy;
	sx = (v->x - l->start->x) * dx;
	sy = (v->y - l->start->y) * dy;
	d = sx + sy;
	return (d < sq && d > 0.0);
}
