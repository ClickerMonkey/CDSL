/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _PLANE
#define _PLANE

#include "vector.h"
#include "line.h"
#include "polygon.h"

// If some geometry is completely in front of the plane
#define PLANE_FRONT		0
// If some geometry is completely in back of the plane
#define PLANE_BACK		1
// If some geometry is directly on top of the plane
#define PLANE_TOP			2
// If some geometry crosses/intersects the plane
#define PLANE_OVERLAP	3

/**
 * A 2-dimensional plane with 3 coefficients: a, b, and c.
 *
 * @author Philip Diffenderer
 */
typedef struct
{
	// The a, b, and c coefficients
	double a;
	double b;
	double c;

} Plane;

/**
 * Initializes a new plane based on a line-segment.
 * 
 * @param l => The line to set the infinite plane on.
 */
Plane* newPlane(Line* l);

/**
 * Initializes a new plane based on another planes.
 * 
 * @param p => The plane to copy from.
 */
Plane* copyPlane(Plane* q);

/**
 * Evaluates a vector to a plane.
 * 
 * @param p => The plane to use to evaluate from.
 * @param v => The vector to evaluate to the plane.
 */
int plane_evalV(Plane* p, Vector* v);

/**
 * Evaluates a line to a plane.
 * 
 * @param p => The plane to use to evaluate from.
 * @param l => The line to evaluate to the plane.
 */
int plane_evalL(Plane* p, Line* l);

/**
 * Evaluates a polygon to a plane.
 * 
 * @param p => The plane to use to evaluate from.
 * @param g => The polygon to evaluate to the plane.
 */
int plane_evalG(Plane* p, Polygon* g);

/**
 * Splits a line based on a plane and returns the front and back segments.
 *
 * @param p => The plane to use to split.
 * @param l => The line to split.
 * @param front => The segment split from the line on the front of the plane
 * @param back => The segment split from the line on the back of the plane
 */
void plane_splitL(Plane* p, Line* l, Line* front, Line* back);

/**
 * Splits a polygon based on a plane and returns the front and back polygons.
 *
 * @param p => The plane to use to split.
 * @param g => The polygon to split.
 * @param front => The section split from the polygon on the front of the plane
 * @param back => The section split from the polygon on the back of the plane
 */
void plane_splitG(Plane* p, Polygon* g, Polygon* front, Polygon* back);

/**
 * Calculates the intersection of two planes.
 * 
 * @param p => The first plane.
 * @param q => The second plane.
 * @param intersectio => The intersection point returned if any.
 */
void plane_interP(Plane* p, Plane* q, Vector* intersection);

/**
 * Calculates the intersection of a line and a plane.
 *
 * @param p => The plane.
 * @param l => The line.
 * @param intersection => The intersection point returned if any.
 */
void plane_interL(Plane* p, Line* l, Vector* intersection);

/**
 * Calculates the intersection of a line and a plane.
 *
 * @param p => The plane.
 * @param start => The starting point on the line.
 * @param end => The ending point on the line.
 * @param intersection => The intersection point returned if any.
 */
void plane_interV(Plane* p, Vector* start, Vector* end, Vector* intersection);

/**
 * Calculates the closest vector on a plane to another vector. The line between
 * the closest and the vector to calculate from is perpendicular to the plane.
 *
 * @param p => The plane to get a point on.
 * @param v => The vector to calculate the closest point to.
 * @param closest => The closest point on the plane to the other point.
 */
void plane_closest(Plane* p, Vector* v, Vector* closest);

/**
 * Calculates the signed distance from the plane to some point.
 * 
 * @param p => The plane to calculate from.
 * @param v => The vector to calculate to.
 */
double plane_distance(Plane* p, Vector* v);

/**
 * Given an x value on the plane this will project it onto the plane and return
 * the corresponding y value to. The combinaton of the x and y is a point
 * lying on the plane.
 * 
 * @param p => The plane to project on.
 * @param x => The x value on the plane.
 */
double plane_projectX(Plane* p, double x);

/**
 * Given an x value on the plane this will project it onto the plane and return
 * the corresponding y value to. The combinaton of the x and y is a point
 * lying on the plane. 
 *
 * @param p => The plane to project on.
 * @param y => The y value on the plane.
 */
double plane_projectY(Plane* p, double y);

#endif /* _PLANE */
