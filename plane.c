/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#include "util.h"
#include "plane.h"

/** 
 * A 2-dimensional plane with 3 coefficients: a, b, and c.
 *
 * @author Philip Diffenderer
 */

// Initializes a new plane based on a line-segment.
Plane* newPlane(Line* l)
{
	Plane* p = alloc(Plane, 1);

	p->a = (l->start->y - l->end->y);
	p->b = (l->end->x - l->start->x);
	p->c = (-p->a * l->start->x) - (p->b * l->start->y);

	return p;
}

// Initializes a new plane based on another planes.
Plane* copyPlane(Plane* q)
{
	Plane* p = alloc(Plane, 1);
	
	p->a = q->a;
	p->b = q->b;
	p->c = q->c;

	return p;
}

// Evaluates a vector to a plane.
int plane_evalV(Plane* p, Vector* v)
{
	double d = (p->a * v->x) + (p->b * v->y) + p->c;

	// A positive distance from the plane is in front
	if (d > EPSILON)
		return PLANE_FRONT;
	// A negative distance from the plane is in back
	if (d < EPSILON)
		return PLANE_BACK;
	// Its less then EPSILON away from the plane.
	return PLANE_TOP;
}

// Evaluates a line to a plane.
int plane_evalL(Plane* p, Line* l)
{
	// Evaluate both points on the line
	int s = plane_evalV(p, l->start);
	int e = plane_evalV(p, l->end);

	// The line is on top of this plane, or is completely on one side.
	if (s == e)
		return s;
	// The start point is on the plane but the end is not
	if (s == PLANE_TOP)
		return e;
	// The end point is on the plane but the start is not
	if (e == PLANE_TOP)
		return s;
	// The line crosses the plane 
	return PLANE_OVERLAP;
}
	
// Evaluates a polygon to a plane.
int plane_evalG(Plane* p, Polygon* g)
{
	int side = -1;
	int current = -1;
	int i;

	// Determine the point that decides the side of the polygon, NOT on top
	for (i = 0; (i < g->size) && (side == -1); i++)
		side = plane_evalV(p, g->points[i]);

	// Make sure all other points are on this side or atleast ontop, if not it overlaps
	for (; i < g->size; i++)
	{
		current = plane_evalV(p, g->points[i]);

		// If the current point is not ontop and not on the right side its an overlap
		if (current != PLANE_TOP && current != side)
			return PLANE_OVERLAP;
	}

	return side;
}

// Splits a line based on a plane and returns the front and back segments.
void plane_splitL(Plane* p, Line* l, Line* front, Line* back)
{
	Vector* inter = emptyVector();

	// Get the intersection point between the line and plane
	plane_interL(p, l, inter);
		
	// Evaluate which side of the plane the start and end are
	int s = plane_evalV(p, l->start);
	int e = plane_evalV(p, l->end);

	// If they're the same then they don't intersect
	if (s == e)
	{
		front = back = NULL;
	}
	// If the line crosses this plane...
	else if (s == PLANE_FRONT && e == PLANE_BACK)
	{
		line_setV(front, l->start, inter);
		line_setV(back, inter, l->end);
	}
	else if (s == PLANE_BACK && e == PLANE_FRONT)
	{
		line_setV(back, l->start, inter);
		line_setV(front, inter, l->end);
 	}

	free(inter);
}

// Splits a polygon based on a plane and returns the front and back polygons.
void plane_splitG(Plane* p, Polygon* g, Polygon* front, Polygon* back)
{
	unsigned int total = g->size;
	int i;

	Vector *inter = emptyVector();
	Vector *A, *B;
	int evalA, evalB;

	A = g->points[total - 1];
	evalA = plane_evalV(p, A);

	for (i = 0; i < total; i++)
	{
		// Evaluate the current point and compare it to the last point
		B = g->points[i];
		evalB = plane_evalV(p, B);

		if (evalB == PLANE_FRONT)
		{
			if (evalA == PLANE_BACK)
			{
				// Determine the intersection on the line A-B with the given plane.
				plane_interV(p, A, B, inter);
				// Add the intersection point to both polygons
				polygon_add(front, inter);
				polygon_add(back, inter);
			}
			// Add the point to the front polygon
			polygon_add(front, B);
		}
		else if (evalB == PLANE_BACK)
		{
			if (evalA == PLANE_FRONT)
			{
				// Determine the intersection on the line A-B with the given plane.
				plane_interV(p, A, B, inter);
				// Add the intersection point to both polygons
				polygon_add(front, inter);
				polygon_add(back, inter);
			}
			// Add the point to the back polygon
			polygon_add(back, B);
		}
		else
		{
			// The point lies on the plane so add it to both
			polygon_add(front, B);
			polygon_add(back, B);
		}

		A = B;
		evalA = evalB;
	}

	free(inter);
}

// Calculates the intersection of two planes.
void plane_interP(Plane* p, Plane* q, Vector* intersection)
{
	double div = 1.0 / ((p->a * q->b) - (p->b * q->a));

	intersection->x = (-(p->c * q->b) + (p->b * q->c)) * div;
	intersection->y = (-(p->a * q->c) + (p->c * q->a)) * div;
}

// Calculates the intersection of a line and a plane.
void plane_interL(Plane* p, Line* l, Vector* intersection)
{
	plane_interV(p, l->start, l->end, intersection);
}

// Calculates the intersection of a line and a plane.
void plane_interV(Plane* p, Vector* start, Vector* end, Vector* intersection)
{
	double a = (start->y - end->y);
	double b = (end->x - start->x);
	double c = (-a * start->x) - (b * start->y);

	double div = ((p->a * b) - (p->b * a));
	
	// This theoretically should never happen
	if (div == 0.0)
	{
		if (a == 0.0)
			intersection->x = start->x;
		if (b == 0.0)
			intersection->y = start->y;
		if (p->a == 0.0)
			intersection->x = -p->b;
		if (p->b == 0.0)
			intersection->y = p->c;
	}
	else
	{
		div = 1.0 / div;
		intersection->x = ((-p->c * b) + (p->b * c)) * div;
		intersection->y = ((-p->a * c) + (p->c * a)) * div;
	}
}

// Calculates the closest vector on a plane to another vector. The line between
// the closest and the vector to calculate from is perpendicular to the plane.
void plane_closest(Plane* p, Vector* v, Vector* closest)
{
	
}

// Calculates the signed distance from the plane to some point.
double plane_distance(Plane* p, Vector* v)
{
	return (p->a * v->x) + (p->b * v->y) + p->c;
}

// Given an x value on the plane this will project it onto the plane and return
// the corresponding y value to. The combinaton of the x and y is a point
// lying on the plane.
double plane_projectX(Plane* p, double x)
{
	if (p->b == 0.0)
		return 0.0;

	return  -(p->c + (p->a * x)) / p->b;
}

// Given an x value on the plane this will project it onto the plane and return
// the corresponding y value to. The combinaton of the x and y is a point
// lying on the plane. 
double plane_projectY(Plane* p, double y)
{
	if (p->a == 0.0)
		return 0.0;

	return -(p->c + (p->b * y)) / p->a;
}
