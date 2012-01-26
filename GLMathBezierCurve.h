// Copyright (c) 2011, Fjölnir Ásgeirsson
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#ifndef GL_MATH_BEZIER_H
#define GL_MATH_BEZIER_H

#include <GLMath/GLMathTypes.h>
#include <GLMath/GLMathVector.h>
#include <GLMath/GLMathMatrix.h>
#include <GLMath/GLMathTransforms.h>

#ifdef __cplusplus
extern "C" {
#endif


#pragma mark - Prototypes

static __inline__ bezier_t bezier_create(vec3_t c1, vec3_t c2, vec3_t c3, vec3_t c4) __asm("__bezier_create");
static __inline__ vec3_t bezier_getPoint(bezier_t curve, float t) __asm("__bezier_getPoint");
static __inline__ float bezier_getCoordForAxis(bezier_t curve, float t, bezierAxis_t axis) __asm("__bezier_getCoordForAxis");
static __inline__ vec3_t bezier_firstDerivative(bezier_t curve, float t) __asm("__bezier_firstDerivative");
static vec2_t bezier_firstDerivativeRoots(bezier_t curve, bezierAxis_t axis) __asm("__bezier_firstDerivativeRoots");
static void bezier_extremes(bezier_t curve, vec3_t *outMinimums, vec3_t *outMaximums) __asm("__bezier_extremes");
static __inline__ vec3_t bezier_getPointWithOffset(bezier_t curve, float t, vec3_t offset) __asm("__bezier_getPointWithOffset");
static void bezier_getLineSegments(bezier_t curve, int count, vec3_t *outPoints, float *outLengths, float *outDeltas, float *outTotalLength) __asm("__bezier_getLineSegments");
static vec3_t bezier_getPointUsingLineSegments(float t, int count, vec3_t *points, float *lengths, float *deltas, float totalLength) __asm("__bezier_getPointUsingLineSegments");

#pragma mark - Implementations

static __inline__ bezier_t bezier_create(vec3_t c1, vec3_t c2, vec3_t c3, vec3_t c4)
{
	bezier_t out = { .controlPoints={c1, c2, c3, c4} };
	return out;
}

static __inline__ vec3_t bezier_getPoint(bezier_t curve, float t)
{
	vec3_t out;
	// Evaluate the bezier curve equation
	float mt = 1.0f - t;
	float coef0 = powf(mt, 3.0f);
	float coef1 = 3.0f * powf(mt, 2.0f) * t;
	float coef2 = 3.0f * mt * powf(t, 2.0f);
	float coef3 = powf(t, 3.0f);

	vec3_t p0 = vec3_scalarMul(curve.controlPoints[0], coef0);
	vec3_t p1 = vec3_scalarMul(curve.controlPoints[1], coef1);
	vec3_t p2 = vec3_scalarMul(curve.controlPoints[2], coef2);
	vec3_t p3 = vec3_scalarMul(curve.controlPoints[3], coef3);

	out = vec3_add(p0, vec3_add(p1, vec3_add(p2, p3)));

	return out;
}

// Calculates only a single component(for the given axis) of a point on the curve
static __inline__ float bezier_getCoordForAxis(bezier_t curve, float t, bezierAxis_t axis)
{
	// Evaluate the bezier curve equation
	float mt = 1.0f - t;
	float p0 = curve.controlPoints[0].f[axis] * powf(mt, 3.0f);
	float p1 = curve.controlPoints[1].f[axis] * (3.0f * powf(mt, 2.0f) * t);
	float p2 = curve.controlPoints[2].f[axis] * (3.0f * mt * powf(t, 2.0f));
	float p3 = curve.controlPoints[3].f[axis] * powf(t, 3.0f);
	return p0 + p1 + p2 + p3;
}


static __inline__ vec3_t bezier_firstDerivative(bezier_t curve, float t)
{
	vec3_t out;
	// Create the derivative curve
	vec3_t derivControlPoints[3];
	derivControlPoints[0] = vec3_sub(curve.controlPoints[1], curve.controlPoints[0]);
	derivControlPoints[1] = vec3_sub(curve.controlPoints[2], curve.controlPoints[1]);
	derivControlPoints[2] = vec3_sub(curve.controlPoints[3], curve.controlPoints[2]);
	// Evaluate the point on the derivative
	float mt = 1.0f - t;
	float coef0 = powf(mt, 2.0f);
	float coef1 = 2.0f * mt * t;
	float coef2 = powf(t, 2.0f);
	vec3_t p0 = vec3_scalarMul(derivControlPoints[0], coef0);
	vec3_t p1 = vec3_scalarMul(derivControlPoints[1], coef1);
	vec3_t p2 = vec3_scalarMul(derivControlPoints[2], coef2);
	out = vec3_add(p0, vec3_add(p1, p2));
	return out;
}
static vec2_t bezier_firstDerivativeRoots(bezier_t curve, bezierAxis_t axis)
{
	vec2_t out = { -1.0f , -1.0f };
	float a = curve.controlPoints[0].f[axis];
	float b = curve.controlPoints[1].f[axis];
	float c = curve.controlPoints[2].f[axis];
	float d = curve.controlPoints[3].f[axis];
	float tl = -a + 2.0f*b - c;
	float tr = -sqrtf(-a*(c-d) + b*b - b*(c+d) + c*c);
	float denom = -a + 3.0f*b - 3.0f*c + d;

	if(denom != 0.0f) {
		out.f[0] = (tl+tr) / denom;
		out.f[1] = (tl-tr) / denom;
	}
	return out;
}

// Returns the extremes for a curve (minX, minY, minZ) & (maxX, maxY, maxZ)
static void bezier_extremes(bezier_t curve, vec3_t *outMinimums, vec3_t *outMaximums)
{
	vec3_t start = bezier_getPoint(curve, 0.0f);
	vec3_t end   = bezier_getPoint(curve, 1.0f);
	vec3_t min, max;
	min.x = GLM_MIN(start.x, end.x);
	min.y = GLM_MIN(start.y, end.y);
	min.z = GLM_MIN(start.z, end.z);
	max.x = GLM_MAX(start.x, end.x);
	max.y = GLM_MAX(start.y, end.y);
	max.z = GLM_MAX(start.z, end.z);
	vec3_t temp;
	for(int axis = 0; axis < 3; ++axis) {
		vec2_t roots = bezier_firstDerivativeRoots(curve, axis);
		for(int i = 0; i < 2; ++i) {
			if(roots.f[i] > 0.0f && roots.f[i] < 1.0f) {
				temp = bezier_getPoint(curve, roots.f[i]);
				min.f[axis] = GLM_MIN(min.f[axis], temp.f[axis]);
				max.f[axis] = GLM_MAX(max.f[axis], temp.f[axis]);
			}
		}
	}
	if(outMinimums) *outMinimums = min;
	if(outMaximums) *outMaximums = max;
}
static __inline__ vec3_t bezier_getPointWithOffset(bezier_t curve, float t, vec3_t offset)
{
	vec3_t tangent = bezier_firstDerivative(curve, t);
	vec3_t normal = { -tangent.y, tangent.x, tangent.z };
	return vec3_add(bezier_getPoint(curve, t), vec3_mul(vec3_normalize(normal), offset));
}

// Computes 'count' many points along with their deltas & the distances between them with an even t interval
static void bezier_getLineSegments(bezier_t curve, int count,
                                   vec3_t *outPoints, float *outLengths, float *outDeltas, float *outTotalLength)
{	float t = 0.0f;
	float interval = 1.0f/(float)(count-1);
	for(int i = 0; i < count; ++i) {
		outPoints[i] = bezier_getPoint(curve, t);
		outDeltas[i] = t;
		if(i > 0) {
			outLengths[i-1] = vec3_dist(outPoints[i], outPoints[i-1]);
			*outTotalLength += outLengths[i-1];
		}
		t += interval;
	}
	outLengths[count-1] = 0.0f;
}

// Computes a point corresponding to the delta 't' using a list of line segments by interpolating the points
// in the list. This is useful for evaluating a curve at a constant rate when animating (Usually an even delta interval
// on a curve does not produce an even distance)
static vec3_t bezier_getPointUsingLineSegments(float t, int count, vec3_t *points,
                                               float *lengths, float *deltas, float totalLength)
{
	float desiredDistance = t * totalLength;
	assert(desiredDistance >= 0.0f && desiredDistance <= totalLength);
	float distanceTravelled = 0.0f;
	for(int i = 0; i < count - 1; ++i) {
		float nextDistanceTravelled = distanceTravelled + lengths[i];
		if(desiredDistance < nextDistanceTravelled) {
			float interpolation = (desiredDistance - distanceTravelled) / lengths[i];
			vec3_t p1 = points[i];
			vec3_t p2 = points[i+1];
			vec3_t movementVector = vec3_scalarMul(vec3_sub(p2, p1), interpolation);
			return vec3_add(p1, movementVector);
		}
		distanceTravelled = nextDistanceTravelled;
	}
	return points[count-1];
}

#ifdef __cplusplus
}
#endif
#endif
