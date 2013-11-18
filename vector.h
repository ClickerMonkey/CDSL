/*****************************************************************************\
                  Copyright (C) 2009 Philip Diffenderfer

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Library General Public License as published by the Free
 Software Foundation; either version 2 of the License, or any later version.

\*****************************************************************************/

#ifndef _VECTOR
#define _VECTOR

/**
 *
 * @author Philip Diffenderfer
 */
typedef struct
{
	// The x component of this vector.	
	double x;
	// The y component of this vector.
	double y;

} Vector;

/**
 * Initializes a new vector at the origin (0,0).
 */
Vector* emptyVector();

/**
 * Initializes a new vector at (1, 1).
 */
Vector* scaleVector();

/**
 * Initializes a new vector at an x and y.
 */
Vector* newVector(double x, double y);


/**
 * Sets the given vector based on x and y components.
 */
void vec_set(Vector* v, double x, double y);

/**
 * Sets the given vector based on another vector.
 */
void vec_setv(Vector* v, Vector* w);


/**
 * Adds the vector w to the vector v.
 */
void vec_addi(Vector* v, Vector* w);

/** 
 * Adds the vector w multiplied by scale to vector v.
 */
void vec_addis(Vector* v, Vector* w, double scale);

/** 
 * Adds the x and y components to the vector v. 
 */
void vec_addiv(Vector* v, double x, double y);

/** 
 * Adds v and w and returns the result.
 */
Vector* vec_add(Vector* v, Vector* w);


/** 
 * Subtracts the vector w from the vector v.
 */
void vec_subi(Vector* v, Vector* w);

/** 
 * Subtracts w from v and returns the result.
 */
Vector* vec_sub(Vector* v, Vector* w);


/** 
 * Multiplies the vector v by vector w.
 */
void vec_muli(Vector* v, Vector* w);

/** 
 * Multiplies the vector v by some scale.
 */
void vec_mulis(Vector* v, float scale);

/** 
 * Multiplies the vector v by x and y components.
 */
void vec_muliv(Vector* v, double x, double y);

/** 
 * Multiplies v and w and return the result.
 */
Vector* vec_mul(Vector* v, Vector* w);


/** 
 * Divides v by w. If a component of w is zero this is ignored.
 */
void vec_divi(Vector* v, Vector* w);

/** 
 * Divides v by some scale.
 */
void vec_divis(Vector* v, float scale);

/**
 * Divides v by an x and y.
 */
void vec_diviv(Vector* v, double x, double y);

/**
 * Divides v by w and returns the result.
 */
Vector* vec_div(Vector* v, Vector* w);


/**
 * Negates this vector's values. (Positive value becomes
 * negative, negative becomes positive)
 */
void vec_neg(Vector* v);


/** 
 * Sets v as the tangent of itself.
 */
void vec_tan(Vector* v);


/** 
 * Normalizes vector v, making its length to 1 but maintaining
 * the same direction.
 */
void vec_normalize(Vector* v);

/** 
 * Returns the normalized form of the vector v.
 */
Vector* vec_normal(Vector* v);


/** 
 * Rotates vector v by the normalized vector n.
 */
void vec_rotate(Vector* v, Vector* n);

/** 
 * Rotates vector v by the normalized vector components x and y.
 */
void vec_rotatev(Vector* v, double x, double y);


/** 
 * Given a surface normal this will reflect vector v across the normal.
 */
void vec_reflecti(Vector* v, Vector* n);

/** 
 * Given a surface normal's components this will reflect vector v along the normal.
 */
void vec_reflectiv(Vector* v, double x, double y);

/** 
 * Given a surface normal this will reflect vector v along the normal and return the result.
 */
Vector* vec_reflect(Vector* v, Vector* n);


/**
 * This will return a projected y value given a x value. The
 * given x value is an imaginary x component to a point along
 * this vectors direction and this function returns the y that
 * completes the point along this vector with the given x.
 * If this vector has a zero x component this will throw an
 * error since there can be no projected y.
 */
double vec_projectX(Vector* v, double x);

/**
 * This will return a projected x value given a y value. The
 * given y value is an imaginary y component to a point along
 * this vectors direction and this function returns the x that
 * completes the point along this vector with the given y.
 * If this vector has a zero y component this will throw an
 * error since there can be no projected x.
 */
double vec_projectY(Vector* v, double y);

/**
 * Mirrors this vector across the x-axis negating 
 * the y component.
 */
void vec_mirrorX(Vector* v);

/**
 * Mirrors this vector across the y-axis negating 
 * the x component.
 */
void vec_mirrorY(Vector* v);

/**
 * Reflects this vector into the second quadrant of a graph
 * so the coordinates are both positive.
 */
void vec_abs(Vector* v);

/**
* Returns the 'sign' of one vector compared to this one. This
* will return -1 if the given vector is on the right side of this
* vector and it will return 1 if the given vector is on the left
* side of this vector.
*/
int vec_sign(Vector* v, Vector* w);

/**
 * Returns the angle in radians of the vector from the origin.
 */
double vec_angle(Vector* v);


/**
 * Returns the dot product of this vector and another.
 */
double vec_dot(Vector* v, Vector* w);

/**
 * Returns the dot product of this vector and an x and y.
 */
double vec_dotv(Vector* v, double x, double y);

/**
 * Returns the cross product of this vector and another.
 */
double vec_cross(Vector* v, Vector* w);

/**
 * Returns the cross product of this vector and an x and y.
 */
double vec_crossv(Vector* v, double x, double y);

/**
 * Returns true if the length of this vector is exactly 1.
 */
int vec_isNormal(Vector* v);


/**
 * Returns the distance v is from the origin.
 */
double vec_magnitude(Vector* v);

/**
 * Returns the distance squared v is from the origin.
 */
double vec_magnitudeSq(Vector* v);

/**
 * Returns the distance squared between v and w.
 */
double vec_distSq(Vector* v, Vector* w);

/**
 * Returns the distance squared between v and an x and y.
 */
double vec_distSqv(Vector* v, double x, double y);

/**
 * Returns the distance between v and w.
 */
double vec_dist(Vector* v, Vector* w);

/**
 * Returns the distance between v and and an x and y.
 */
double vec_distv(Vector* v, double x, double y);

/**
 * Clips the length of the vector v between min and max.
 */
double vec_clipLength(Vector* v, double min, double max);

/**
 * Given a start and ending vector of a line or plane this returns
 * the signed distance v is from the line.
 */
double vec_distSigned(Vector* v, Vector* start, Vector* end);


/**
 * Returns true if v is equal to w.
 */
int vec_isEqual(Vector* v, Vector* w);

/**
 * Returns true if v is NOT equal to w.
 */
int vec_isNotEqual(Vector* v, Vector* w);

#endif /* _VECTOR */
