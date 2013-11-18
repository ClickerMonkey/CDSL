/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#include <math.h>

#include "util.h"
#include "vector.h"

// Initializes a new vector at the origin (0,0).
Vector* emptyVector()
{
	return newVector(0.0, 0.0);
}

// Initializes a new vector at (1, 1).
Vector* scaleVector()
{
	return newVector(1.0, 1.0);
}

// Initializes a new vector at an x and y.
Vector* newVector(double x, double y)
{
	Vector* v = alloc(Vector, 1);

	v->x = x;
	v->y = y;

	return v;
}


// Sets the given vector based on x and y components.
void vec_set(Vector* v, double x, double y)
{
	v->x = x;
	v->y = y;
}

// Sets the given vector based on another vector.
void vec_setv(Vector* v, Vector* w)
{
	v->x = w->x;
	v->y = w->y;
}


// Adds the vector w to the vector v.
void vec_addi(Vector* v, Vector* w)
{
	v->x += w->x;
	v->y += w->y;
}

// Adds the vector w multiplied by scale to vector v.
void vec_addis(Vector* v, Vector* w, double scale)
{
	v->x += w->x * scale;
	v->y += w->y * scale;
}

// Adds the x and y components to the vector v. 
void vec_addiv(Vector* v, double x, double y)
{
	v->x += x;
	v->y += y;
}

// Adds v and w and returns the result.
Vector* vec_add(Vector* v, Vector* w)
{
	return newVector(v->x + w->x, v->y + w->y);
}


// Subtracts the vector w from the vector v.
void vec_subi(Vector* v, Vector* w)
{
	v->x -= w->x;
	v->y -= w->y;
}

// Subtracts w from v and returns the result.
Vector* vec_sub(Vector* v, Vector* w)
{
	return newVector(v->x - w->x, v->y - w->y);
}


// Multiplies the vector v by vector w.
void vec_muli(Vector* v, Vector* w)
{
	v->x *= w->x;
	v->y *= w->y;
}

// Multiplies the vector v by some scale.
void vec_mulis(Vector* v, float scale)
{
	v->x *= scale;
	v->y *= scale;
}
 
// Multiplies the vector v by x and y components.
void vec_muliv(Vector* v, double x, double y)
{
	v->x *= x;
	v->y *= y;
}

// Multiplies v and w and return the result.
Vector* vec_mul(Vector* v, Vector* w)
{
	return newVector(v->x * w->x, v->y * w->y);
}

 
// Divides v by w. If a component of w is zero this is ignored.
void vec_divi(Vector* v, Vector* w)
{
	if (w->x != 0.0)
		v->x /= w->x;
	if (w->y != 0.0)
		v->y /= w->y;
}

// Divides v by some scale.
void vec_divis(Vector* v, float scale)
{
	if (scale == 0.0)
		return;
	v->x /= scale;
	v->y /= scale;
}

// Divides v by an x and y.
void vec_diviv(Vector* v, double x, double y)
{
	if (x != 0.0)
		v->x /= x;
	if (y != 0.0)
		v->y /= y;
}

// Divides v by w and returns the result.
Vector* vec_div(Vector* v, Vector* w)
{
	return newVector(v->x / w->x, v->y / w->y);
}


// Negates this vector's values. (Positive value becomes
// negative, negative becomes positive)
void vec_neg(Vector* v)
{
	v->x = -v->x;
	v->y = -v->y;
}


// Sets v as the tangent of itself.
void vec_tan(Vector* v)
{
	double z = v->x;
	v->x = -v->y;
	v->y = z;
}


// Normalizes vector v, making its length to 1 but maintaining
// the same direction.
void vec_normalize(Vector* v)
{
	double sq = vec_magnitudeSq(v);
	// If its 0 then it can't be normalized
	if (sq == 0.0 || sq == 1.0)
		return;

	double distInv = 1.0 / sqrt(sq);
	v->x *= distInv;
	v->y *= distInv;
}

// Returns the normalized form of the vector v.
Vector* vec_normal(Vector* v)
{
	Vector* w = newVector(v->x, v->y);
	vec_normalize(w);
	return w;
}


// Rotates vector v by the normalized vector n.
void vec_rotate(Vector* v, Vector* n)
{
	double a = v->x, b = v->y;
	v->x = a * n->x - b * n->y;
	v->y = b * n->x + a * n->y;
}

// Rotates vector v by the normalized vector components x and y.
void vec_rotatev(Vector* v, double x, double y)
{
	double a = v->x, b = v->y;
	v->x = a * x - b * y;
	v->y = b * x + a * y;
}

 
// Given a surface normal this will reflect vector v across the normal.
void vec_reflecti(Vector* v, Vector* n)
{
	double dot = 2 * vec_dot(v, n);
	v->x = (dot * n->x) - v->x;
	v->y = (dot * n->y) - v->y;
}
 
// Given a surface normal's components this will reflect vector v along the normal.
void vec_reflectiv(Vector* v, double x, double y)
{
	double dot = 2 * vec_dotv(v, x, y);
	v->x = (dot * x) - v->x;
	v->y = (dot * y) - v->y;
}
 
// Given a surface normal this will reflect vector v along the normal and return the result.
Vector* vec_reflect(Vector* v, Vector* n)
{
	Vector* r = newVector(v->x, v->y);
	vec_reflecti(r, n);
	return r;
}


// This will return a projected y value given a x value. The
// given x value is an imaginary x component to a point along
// this vectors direction and this function returns the y that
// completes the point along this vector with the given x.
// If this vector has a zero x component this will throw an
// error since there can be no projected y.
double vec_projectX(Vector* v, double x)
{
	return (x / v->x) * v->y;
}

// This will return a projected x value given a y value. The
// given y value is an imaginary y component to a point along
// this vectors direction and this function returns the x that
// completes the point along this vector with the given y.
// If this vector has a zero y component this will throw an
// error since there can be no projected x.
double vec_projectY(Vector* v, double y)
{
	return (y / v->y) * v->x;
}

// Mirrors this vector across the x-axis negating 
// the y component.
void vec_mirrorX(Vector* v)
{
	v->y = -v->y;
}

// Mirrors this vector across the y-axis negating 
// the x component.
void vec_mirrorY(Vector* v)
{
	v->x = -v->x;
}


// Reflects this vector into the second quadrant of a graph
// so the coordinates are both positive.
void vec_abs(Vector* v)
{
	v->x = abs(v->x);
	v->y = abs(v->y);
}


// Returns the 'sign' of one vector compared to this one. This
// will return -1 if the given vector is on the right side of this
// vector and it will return 1 if the given vector is on the left
// side of this vector.
int vec_sign(Vector* v, Vector* w)
{
	return ((v->y * w->x) > (v->x * w->y) ? -1 : 1);
}


// Returns the angle in radians of the vector from the origin.
double vec_angle(Vector* v)
{
	return (atan2(-v->y, -v->x) + 3.141592653589);
}


// Returns the dot product of this vector and another.
double vec_dot(Vector* v, Vector* w)
{
	return (v->x * w->x) + (v->y * w->y);
}

// Returns the dot product of this vector and an x and y.
double vec_dotv(Vector* v, double x, double y)
{
	return (v->x * x) + (v->y * y);
}


// Returns the cross product of this vector and another.
double vec_cross(Vector* v, Vector* w)
{
	return (v->x * w->y) - (v->y * w->x);
}

// Returns the cross product of this vector and an x and y.
double vec_crossv(Vector* v, double x, double y)
{
	return (v->x * y) - (v->y * x);
}


// Returns true if the length of this vector is exactly 1.
int vec_isNormal(Vector* v)
{
	return (vec_magnitudeSq(v) == 1.0);
}


// Returns the distance v is from the origin.
double vec_magnitude(Vector* v)
{
	return sqrt((v->x * v->x) + (v->y * v->y));
}

// Returns the distance squared v is from the origin.
double vec_magnitudeSq(Vector* v)
{
	return (v->x * v->x) + (v->y * v->y);
}

// Returns the distance squared between v and w.
double vec_distSq(Vector* v, Vector* w)
{
	double dx = (v->x - w->x);
	double dy = (v->y - w->y);
	return (dx * dx + dy * dy);
}

// Returns the distance squared between v and an x and y.
double vec_distSqv(Vector* v, double x, double y)
{
	double dx = (v->x - x);
	double dy = (v->y - y);
	return (dx * dx + dy * dy);
}

// Returns the distance between v and w.
double vec_dist(Vector* v, Vector* w)
{
	double dx = (v->x - w->x);
	double dy = (v->y - w->y);
	return sqrt(dx * dx + dy * dy);
}

// Returns the distance between v and and an x and y.
double vec_distv(Vector* v, double x, double y)
{
	double dx = (v->x - x);
	double dy = (v->y - y);
	return sqrt(dx * dx + dy * dy);
}


// Clips the length of the vector v between min and max.
double vec_clipLength(Vector* v, double min, double max)
{
	double sq = vec_magnitudeSq(v);
	if (sq == 0.0)
		return 0.0;

	double length = sqrt(sq);
	double lengthInv = 1.0 / length;

	if (length < min)
		length = min;
	if (length > max)
		length = max;
	
	v->x *= lengthInv * length;
	v->y *= lengthInv * length;
	
	return length;
}


// Given a start and ending vector of a line or plane this returns
// the signed distance v is from the line.
double vec_distSigned(Vector* v, Vector* start, Vector* end)
{
	double sq = vec_distSq(start, end);
	if (sq == 0.0)
		return vec_dist(v, start);

	double distance = sqrt(sq);
	double distanceInv = 1.0 / distance;

	double a = (end->y - start->y) * (start->x - v->x);
	double b = (end->x - start->x) * (start->y - v->y);
	return (a - b) * distanceInv;	
}


// Returns true if v is equal to w.
int vec_isEqual(Vector* v, Vector* w)
{
	return (v->x == w->x && v->y == w->y);
}

// Returns true if v is NOT equal to w.
int vec_isNotEqual(Vector* v, Vector* w)
{
	return (v->x != w->x || v->y != w->y);
}
