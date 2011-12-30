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

#include "GLMathTypes.h"
#include "GLMathVector.h"
#include "GLMathMatrix.h"
#include "GLMathTransforms.h"

#ifdef __cplusplus
extern "C" {
#endif


#pragma mark - Prototypes

static __inline__ bezier_t bezier_create(vec3_t c1, vec3_t c2, vec3_t c3, vec3_t c4);
static __inline__ vec3_t bezier_getPoint(bezier_t curve, float t);
static __inline__ float bezier_getCoordForAxis(bezier_t curve, float t, bezierAxis_t axis);
static __inline__ vec3_t bezier_firstDerivative(bezier_t curve, float t);
static vec2_t bezier_firstDerivativeRoots(bezier_t curve, bezierAxis_t axis);
static void bezier_extremes(bezier_t curve, vec3_t *outMinimums, vec3_t *outMaximums);
static __inline__ vec3_t bezier_getPointWithOffset(bezier_t curve, float t, vec3_t offset);

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

#ifdef __cplusplus
}
#endif
#endif
