/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#include <math.h>

#include "util.h"
#include "transform.h"

/**
 * A transformation is a geometric matrix used to modify vectors
 * based on a transform which can be scaled, sheared, rotated, or
 * translated across either the x-axis or y-axis.
 * 
 * @author Philip Diffenderfer
 */

// Initializes a new transform with scale, sheer, and translation.
Transform* newTransform(double transX, double transY, double shearX, double shearY, double scaleX, double scaleY)
{
	Transform* t = alloc(Transform, 1);
	
	t->transX = transX;
	t->transY = transY;
	t->shearX = shearX;
	t->shearY = shearY;
	t->scaleX = scaleX;
	t->scaleY = scaleY;

	return t;
}

// Initializes a new transform scale set to 1 and with 0 translation and shearing.
Transform* newTransformIdentity()
{
	Transform* t = alloc(Transform, 1);
	
	t->scaleX = t->scaleY = 1.0;
	t->transX = t->transY = t->shearX = t->shearY = 0.0;

	return t;
}

// Initializes a new transform based on an existing one.
Transform* newTransformCopy(Transform* source)
{	
	Transform* t = alloc(Transform, 1);
	
	t->transX = source->transX;
	t->transY = source->transY;
	t->shearX = source->shearX;
	t->shearY = source->shearY;
	t->scaleX = source->scaleX;
	t->scaleY = source->scaleY;

	return t;
}

// Sets this transforms data based on an existing one.
void trans_setCopy(Transform* t, Transform* source)
{
	t->transX = source->transX;
	t->transY = source->transY;
	t->shearX = source->shearX;
	t->shearY = source->shearY;
	t->scaleX = source->scaleX;
	t->scaleY = source->scaleY;
}

// Resets this Transform as an identity transformation. 
// Scaling is default, no shearing, and no translation.
void trans_setIdentity(Transform* t)
{
	t->scaleX = t->scaleY = 1.0;
	t->transX = t->transY = t->shearX = t->shearY = 0.0;
}

// Resets this Transform with only translation.
void trans_setTranslation(Transform* t, double x, double y)
{
	t->scaleX = t->scaleY = 1.0;
	t->shearX = t->shearY = 0.0;
	t->transX = x;
	t->transY = y;
}

// Resets this Transform with only scaling.
void trans_setScaling(Transform* t, double x, double y)
{
	t->scaleX = x;
	t->scaleY = y;
	t->transX = t->transY = t->shearX = t->shearY = 0.0;
}

// Resets this Transform with only shearing.
void trans_setShear(Transform* t, double x, double y)
{
	t->scaleX = t->scaleY = 1.0;
	t->transX = t->transY = 0.0;
	t->shearX = x;
	t->shearY = y;
}

// Resets this Transform with only rotation.
void trans_setRotation(Transform* t, double angle)
{
	double cosa = cos(angle);
	double sina = sin(angle);

	t->scaleX = t->scaleY = cosa;
	t->shearX = -(t->shearY = sina);
	t->transX = t->transY = 0.0;
}

// Transforms the vector v across this transformation changing
// its location based on the transform.
void trans_transformSet(Transform* t, Vector* v)
{
	double x = (t->scaleX * v->x) + (t->shearX * v->y) + t->transX;
	double y = (t->shearY * v->x) + (t->scaleY * v->y) + t->transY;
	v->x = x;
	v->y = y;
}

// Transforms the vector v across this transformation into the
// vector out.
void trans_transform(Transform* t, Vector* v, Vector* out)
{
	out->x = (t->scaleX * v->x) + (t->shearX * v->y) + t->transX;
	out->y = (t->shearY * v->x) + (t->scaleY * v->y) + t->transY;
}

// Transforms an array of vector's across this transformation
// changing each vectors location based on the transform.
void trans_transformVectors(Transform* t, Vector* vectors[], int count)
{
	while (--count >= 0)
		trans_transformSet(t, vectors[count]);
}

// Sets the transformation based on some angle in radians, scaling
// and a translation. This is the quickest way to set a transform 
// with all of these operations.
void trans_set(Transform* t, double angle, double scaleX, double scaleY, double transX, double transY)
{
	if (angle != 0.0)
	{
		double cosa = cos(angle);
		double sina = sin(angle);

		t->scaleX = scaleX * cosa;
		t->scaleY = scaleY * cosa;
		t->shearX = scaleY * sina;
		t->shearY = scaleX * sina;
		t->transX = transX;
		t->transY = transY;
	}
	else
	{
		t->scaleX = scaleX;
		t->scaleY = scaleY;
		t->shearX = t->shearY = 0.0;
		t->transX = transX;
		t->transY = transY;
	}
}

// Multiplies the given transform t by the transform a. Multiplication
// will result in a combination of the transforms properties.
void trans_multiply(Transform* t, Transform* a)
{
	double scX, scY, shX, shY, trX, trY;

	scX = (t->scaleX * a->scaleX) + (t->shearY * a->shearX);
	scY = (t->shearX * a->shearY) + (t->scaleY * a->scaleY);
	shX = (t->shearX * a->scaleX) + (t->scaleY * a->shearX);
	shY = (t->scaleX * a->shearY) + (t->shearY * a->scaleY);
	trX = (t->transX * a->scaleX) + (t->transY * a->transX) + a->transX;
	trY = (t->transX * a->shearY) + (t->transY * a->transY) + a->transY;

	t->scaleX = scX;
	t->scaleY = scY;
	t->transX = trX;
	t->transY = trY;
	t->shearX = shX;
	t->shearY = shY;
}

// Translates the given transform t by some x and y value.
void trans_translate(Transform* t, double x, double y)
{
	t->transX += x;
	t->transY += y;
}

// Scales the given transform t by some x and y value.
void trans_scale(Transform* t, double x, double y)
{
	t->scaleX *= x;
	t->transX *= x;
	t->shearX *= x;
	t->scaleY *= y;
	t->transY *= y;
	t->shearY *= y;
}

// Shears the given transform t on the x-axis.
void trans_shearX(Transform* t, double x)
{
	t->scaleX += t->shearY * x;
	t->shearX += t->scaleY * x;
	t->transX += t->transY * x;
}

// Shears the given transform t on the y-axis.
void trans_shearY(Transform* t, double y)
{
	t->shearY += t->scaleX * y;
	t->scaleY += t->shearX * y;
	t->transY += t->transX * y;
}

// Rotates the given transform t by some angle in radians.
void trans_rotate(Transform* t, double angle)
{
	if (angle == 0.0)
		return;
	
	double cosa = cos(angle);
	double sina = sin(angle);
	double scX, scY, shX, shY, trX, trY;
	
	scX = (t->scaleX * cosa) - (t->shearY * sina);
	scY = (t->shearX * sina) + (t->scaleY * cosa);
	shX = (t->shearX * cosa) - (t->scaleY * sina);
	shY = (t->scaleX * sina) + (t->shearY * cosa);
	trX = (t->transX * cosa) - (t->transY * sina);
	trY = (t->transX * sina) + (t->transY * cosa);

	t->scaleX = scX;
	t->scaleY = scY;
	t->transX = trX;
	t->transY = trY;
	t->shearX = shX;
	t->shearY = shY;
}

// Rotates the given transform t around some point with some angle
// in degrees.
void trans_rotateAround(Transform* t, double angle, double x, double y)
{
	trans_translate(t, -x, -y);
	trans_rotate(t, angle);
	trans_translate(t, x, y);
}

// Turns this Transform into its inverse. The Inverse is a transformation that undoes
// this transformations operations.
void trans_invert(Transform* t)
{
	double det = trans_determinant(t);
		
	if (det == 0.0)
		return;
	
	// Calculate the inverse of the determinant so only
	// one divide operation occurs.
	double detInv = 1.0 / det;
	double scX, scY, shX, shY, trX, trY;
	                         
	scX = t->scaleY * detInv; 
	scY = t->scaleX * detInv;
	shX = -t->shearX * detInv;
	shY = -t->shearY * detInv;
	trX = (t->shearX * t->transY - t->scaleY * t->transX) * detInv;
	trY = (t->shearY * t->transX - t->scaleX * t->transY) * detInv; 

	t->scaleX = scX;
	t->scaleY = scY;
	t->transX = trX;
	t->transY = trY;
	t->shearX = shX;
	t->shearY = shY;
}

// Calculates the determinant for this transform. This is used 
// to determine if a transform is invertible and also to invert it.
// If the determinant is 0 then it is invertible, any other value
// means this Transform is invertible.
double trans_determinant(Transform* t)
{
	return (t->scaleX * t->scaleY - t->shearY * t->shearX);
}

// Determines whether this transformation is equivalent to 
// the identity transform (a transform without scaling, 
// rotation, shearing, or translation).
int trans_isIdentity(Transform* t)
{
	return (equal(t->scaleX, 1.0) && equal(t->shearY, 0.0)
		  && equal(t->shearX, 0.0) && equal(t->scaleY, 1.0)
		  && equal(t->transX, 0.0) && equal(t->transY, 0.0));
}
