/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _TRANSFORM
#define _TRANSFORM

#include "vector.h"

/**
 * A transformation is a geometric matrix used to modify vectors
 * based on a transform which can be scaled, sheared, rotated, or
 * translated across either the x-axis or y-axis.
 * 
 * @author Philip Diffenderfer
 */
typedef struct
{

	double transX;
	double transY;
	double shearX;
	double shearY;
	double scaleX;
	double scaleY;

} Transform;

/**
 * Initializes a new transform with scale, sheer, and translation.
 * 
 * @param scaleX => Scaling on the x-axis.
 * @param scaleY => Scaling on the y-axis.
 * @param shearX => Shearing on the x-axis.
 * @param shearY => Shearing on the y-axis.
 * @param transX => Translation on the x-axis.
 * @param transY => Translation on the y-axis.
 */
Transform* newTransform(double transX, double transY, double shearX, double shearY, double scaleX, double scaleY);

/**
 * Initializes a new transform scale set to 1 and with 0 translation and shearing.
 */
Transform* newTransformIdentity();

/**
 * Initializes a new transform based on an existing one.
 * 
 * @param source => The transform to copy its elements from.
 */
Transform* newTransformCopy(Transform* source);

/**
 * Sets this transforms data based on an existing one.
 * 
 * @param t => The transform to copy to.
 * @param source => The transform to copy its elements from.
 */
void trans_setCopy(Transform* t, Transform* source);

/**
 * Resets this Transform as an identity transformation. 
 * Scaling is default, no shearing, and no translation.
 * 
 * @param t => The transform to set.
 */
void trans_setIdentity(Transform* t);

/**
 * Resets this Transform with only translation.
 * 
 * @param t => The transform to set.
 * @param transX => The amount of translation on the x-axis.
 * @param transY => The amount of translation on the y-axis.
 */
void trans_setTranslation(Transform* t, double x, double y);

/**
 * Resets this Transform with only scaling.
 * 
 * @param t => The transform to set.
 * @param scaleX => The amount of scaling on the x-axis.
 * @param scaleY => The amount of scaling on the y-axis.
 */
void trans_setScaling(Transform* t, double x, double y);

/**
 * Resets this Transform with only shearing.
 * 
 * @param t => The transform to set.
 * @param shearX => The amount of shearing on the x-axis.
 * @param shearY => The amount of shearing on the y-axis.
 */
void trans_setShear(Transform* t, double x, double y);

/**
 * Resets this Transform with only rotation.
 * 
 * @param t => The transform to set.
 * @param angle => The angle of rotation in radians.
 */
void trans_setRotation(Transform* t, double angle);

/**
 * Transforms the vector v across this transformation changing
 * its location based on the transform.
 * 
 * @param t => The transform to use.
 * @param v => The vector to transform.
 */
void trans_transformSet(Transform* t, Vector* v);

/**
 * Transforms the vector v across this transformation into the
 * vector out.
 * 
 * @param t => The transform to use.
 * @param v => The vector to transform.
 * @param out => The transformed vector.
 */
void trans_transform(Transform* t, Vector* v, Vector* out);

/**
 * Transforms an array of vector's across this transformation
 * changing each vectors location based on the transform.
 * 
 * @param t => The transform to use.
 * @param vectors => The array of vectors to transform.
 * @param count => The number of vectors to transform in the array.
 */
void trans_transformVectors(Transform* t, Vector* vectors[], int count);

/**
 * Sets the transformation based on some angle in radians, scaling
 * and a translation. This is the quickest way to set a transform 
 * with all of these operations.
 * 
 * @param t => The transform to set.
 * @param angle => The angle to rotate the transform.
 * @param scaleX => The scaling on the x-axis of this transform.
 * @param scaleY => The scaling on the y-axis of this transform.
 * @param transX => The translation on the x-axis of this transform.
 * @param transY => The translation on the y-axis of this transform.
 */
void trans_set(Transform* t, double angle, double scaleX, double scaleY, double transX, double transY);

/**
 * Multiplies the given transform t by the transform a. Multiplication
 * will result in a combination of the transforms properties.
 * 
 * @param t => The transform to multiply.
 * @param a => The transform to multiply by.
 */
void trans_multiply(Transform* t, Transform* a);

/**
 * Translates the given transform t by some x and y value.
 * 
 * @param t => The transform to translate.
 * @param x => The amount of translation on the x-axis.
 * @param y => The amount of translation on the y-axis.
 */
void trans_translate(Transform* t, double x, double y);

/**
 * Scales the given transform t by some x and y value.
 * 
 * @param t => The transform to scale.
 * @param x => The amount of scaling on the x-axis.
 * @param y => The amount of scaling on the y-axis.
 */
void trans_scale(Transform* t, double x, double y);

/**
 * Shears the given transform t on the x-axis.
 * 
 * @param t => The transform to shear.
 * @param x => The amount of shearing on the x-axis.
 */
void trans_shearX(Transform* t, double x);

/**
 * Shears the given transform t on the y-axis.
 * 
 * @param t => The transform to shear.
 * @param y => The amount of shearing on the y-axis.
 */
void trans_shearY(Transform* t, double y);

/**
 * Rotates the given transform t by some angle in radians.
 * 
 * @param t => The transform to rotate.
 * @param angle => The amount of rotation in radians.
 */
void trans_rotate(Transform* t, double angle);

/**
 * Rotates the given transform t around some point with some angle
 * in degrees.
 * 
 * @param t => The transform to rotate around a point.
 * @param angle => The amount of rotation in radians.
 * @param x => The x value of the point to rotate around.
 * @param y => The y value of the point to rotate around.
 */
void trans_rotateAround(Transform* t, double angle, double x, double y);

/**
 * Turns this Transform into its inverse. The Inverse is a transformation that undoes
 * this transformations operations.
 * 
 * @param t => The transform to invert.
 */
void trans_invert(Transform* t);

/**
 * Calculates the determinant for this transform. This is used 
 * to determine if a transform is invertible and also to invert it.
 * If the determinant is 0 then it is invertible, any other value
 * means this Transform is invertible.
 * 
 * @param t => The transform to calculate the determinant of.
 */
double trans_determinant(Transform* t);

/**
 * Determines whether this transformation is equivalent to 
 * the identity transform (a transform without scaling, 
 * rotation, shearing, or translation).
 * 
 * @param t => The transform to test for identity.
 */
int trans_isIdentity(Transform* t);

#endif /* _TRANSFORM */
