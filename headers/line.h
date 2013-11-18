/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _LINE
#define _LINE

#include "vector.h"

/**
 * A 2-dimensional line with a starting and ending point.
 *
 * @author Philip Diffenderer
 */
typedef struct
{
	// The starting point of the line
	Vector* start;
	// The ending point of the line
	Vector* end;

} Line;

/**
 * Initializes a new line with its starting and ending points.
 * 
 * @param start => The starting point of the line.
 * @param end => The ending point of the line.
 */
Line* newLine(Vector* start, Vector* end);

/**
 * Sets the starting and ending points of the line.
 * 
 * @param l => The line to set.
 * @param x1 => The x component of the starting point.
 * @param y1 => The y component of the starting point.
 * @param x2 => The x component of the ending point.
 * @param y2 => The y component of the ending point.
 */
void line_set(Line* l, double x1, double y1, double x2, double y2);

/**
 * Sets the starting and ending points of the line.
 * 
 * @param l => The line to set.
 * @param start => The starting point of the line.
 * @param end => The ending point of the line.
 */
void line_setV(Line* l, Vector* start, Vector* end);

/**
 * Sets the start point of the line.
 * 
 * @param l => The line to set.
 * @param x => The x component of the starting point.
 * @param y => The y component of the starting point.
 */
void line_setStart(Line* l, double x, double y);

/**
 * Sets the end point of the line.
 * 
 * @param l => The line to set.
 * @param x => The x component of the ending point.
 * @param y => The y component of the ending point.
 */
void line_setEnd(Line* l, double x, double y);

/**
 * Returns the normal of the line. A normal is a vector tangent
 * to the line with a length of 1.0
 * 
 * @param l => The line to calculate the normal of.
 * @param out => The vector to set as the normal.
 */
void line_getNormal(Line* l, Vector* out);

/**
 * Returns the difference between the start and end points.
 * 
 * @param l => The line to calculate the difference of.
 * @param out => The vector to set as the difference.
 */
void line_getDiff(Line* l, Vector* out);

/**
 * Returns the mid point of the line.
 * 
 * @param l => The line to calculate the mid point.
 * @param out => The vector to set as the mid point.
 */
void line_getMid(Line* l, Vector* out);

/**
 * Gets a point on the axis of the line 'delta' away from start. Where
 * the point returned is at the start point if delta is 0.0 and if
 * delta is 1.0 then its at the end point.
 * 
 * @param l => The line to calculate a point along.
 * @param delta => The delta value between 1.0 and 0.0.
 * @param out => The vector to set as the point along the line.
 */
void line_getPoint(Line* l, double delta, Vector* out);

/**
 * Returns the point thats on the axis of the line and the line between
 * this point and the given vector is perpendicular to the line itself.
 * 
 * @param l => The line to calculate a projected vector on.
 * @param v => The vector to project from.
 * @param out => The vector to set as the projection.
 */
void line_project(Line* l, Vector* v, Vector* out);

/**
 * Returns a point on the line thats closest ot v. The point returned is
 * between the start and end points.
 * 
 * @param l => The line to calculate the closest point from.
 * @param v => The vector to determine the closest from.
 * @param out => The vector to set as the closest point.
 */
void line_closest(Line* l, Vector* v, Vector* out);

/**
 * Returns the 'delta' the vector is on the axis between the start and 
 * end points.
 * 
 * @param l => The line to calculate the delta from.
 * @param v => The vector to use to calculate the delta.
 */
double line_getDelta(Line* l, Vector* v);

/**
 * Returns the length of the line.
 * 
 * @param l => The line to calculate the length of.
 */
double line_getLength(Line* l);
/**
 * Returns the length of the line squared.
 * 
 * @param l => The line to calculate the length squared of.
 */
double line_getLengthSq(Line* l);

/**
 * Returns the signed distance between the line's axis and some vector.
 * 
 * @param l => The line to calculate the signed distance from.
 * @param v => The vector to calculate the signed distance from.
 */
double line_signedDistance(Line* l, Vector* v);

/**
 * Returns true if the vector is above the line (on the same side as the normal).
 * 
 * @param l => The line to test whether the vector is above it.
 * @param v => The vector to test whether its above the line.
 */
int line_isAbove(Line* l, Vector* v);

/**
 * Returns true if the vector is below the line (on the opposite side of the normal).
 * 
 * @param l => The line to test whether the vector is below it.
 * @param v => The vector to test whether its below the line.
 */
int line_isBelow(Line* l, Vector* v);

/**
 * Returns true if the vector is atleast EPSILON away from the line.
 * 
 * @param l => The line to test whether the vector is on it.
 * @param v => The vector to test whether its on the line.
 */
int line_isOn(Line* l, Vector* v);

/**
 * Returns true if the vector is between the two axis perpendicular to the
 * start and end points.
 * 
 * @param l => The line to test for bounds checking.
 * @param v => The vector to test whether its in the lines bounds.
 */
int line_inBounds(Line* l, Vector* v);

#endif /* _LINE */
