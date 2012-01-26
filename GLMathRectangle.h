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

#ifndef GL_MATH_RECT_H
#define GL_MATH_RECT_H

#include <GLMath/GLMathTypes.h>
#include <GLMath/GLMathVector.h>
#ifdef USE_ACCELERATE_FRAMEWORK
#include <Accelerate/Accelerate.h>
#endif
#include <math.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GLM_MAX(x,y) ( ((x)>(y)) ? (x) : (y) )
#define GLM_MIN(x,y) ( ((x)<(y)) ? (x) : (y) )

#pragma mark - Prototypes

static __inline__ rect_t rect_createWithSize(vec2_t origin, vec2_t size) __asm("__rect_createWithSize");
static __inline__ rect_t rect_createWithCorners(float left, float bottom, float right, float top) __asm("__rect_createWithCorners");
static __inline__ float rect_maxX(const rect_t rect) __asm("__rect_maxX");
static __inline__ float rect_minX(const rect_t rect) __asm("__rect_minX");
static __inline__ float rect_maxY(const rect_t rect) __asm("__rect_maxY");
static __inline__ float rect_minY(const rect_t rect) __asm("__rect_minY");
// True if r1&2 intersect
static __inline__ bool rect_intersects(const rect_t r1, const rect_t r2) __asm("__rect_intersects");
// True if r1 contains r2
static __inline__ bool rect_containsRect(const rect_t r1, const rect_t r2) __asm("__rect_containsRect");
// True if rect contains point
static __inline__ bool rect_containsPoint(const rect_t rect, const vec2_t point) __asm("__rect_containsPoint");
// Returns a rectangle containing both rectangles
static __inline__ rect_t rect_merge(const rect_t r1, const rect_t r2) __asm("__rect_merge");
// Scales the rectangle, maintaining the center point
static __inline__ rect_t rect_scale(const rect_t rect, const vec2_t scale) __asm("__rect_scale");
// Returns the area of rect
static __inline__ float rect_area(const rect_t rect) __asm("__rect_area");
// True if rect intersects with the line segment between a&b
static __inline__ bool rect_intersectsLineSeg(const rect_t rect, const vec2_t a, const vec2_t b) __asm("__rect_intersectsLineSeg");
// Translates rect by the given vector
static __inline__ rect_t rect_translate(const rect_t aRect, const vec2_t aTranslationVector) __asm("__rect_translate");

#pragma mark Implementations
static __inline__ rect_t rect_createWithSize(vec2_t origin, vec2_t size)
{
	rect_t out = { origin.x, origin.y, size.w, size.h };
	return out;
}

static __inline__ rect_t rect_createWithCorners(float left, float bottom, float right, float top)
{
	rect_t out = { left, bottom, right-left, top-bottom };
	return out;
}

static __inline__ float rect_maxX(const rect_t rect)
{
	return rect.origin.x + rect.size.w;
}

static __inline__ float rect_minX(const rect_t rect)
{
	return rect.origin.x;
}

static __inline__ float rect_maxY(const rect_t rect)
{
	return rect.origin.y + rect.size.h;
}

static __inline__ float rect_minY(const rect_t rect)
{
	return rect.origin.y;
}

static __inline__ bool rect_intersects(const rect_t r1, const rect_t r2)
{
	return (rect_minX(r1) <= rect_maxX(r2)
	        && rect_minX(r2) <= rect_maxX(r1)
	        && rect_minY(r1) <= rect_maxY(r2)
	        && rect_minY(r2) <= rect_maxY(r1));
}

static __inline__ bool rect_containsRect(const rect_t r1, const rect_t r2)
{
	return (rect_minX(r1) <= rect_minX(r2)
	        && rect_maxX(r1) >= rect_maxX(r2)
	        && rect_minY(r1) <= rect_minY(r2)
	        && rect_maxY(r1) >= rect_maxY(r2));
}

static __inline__ bool rect_containsPoint(const rect_t rect, const vec2_t point)
{
	return (rect_minX(rect) <= point.x
			&& rect_maxX(rect) >= point.x
			&& rect_minY(rect) <= point.y
			&& rect_maxY(rect) >= point.y);
}

static __inline__ rect_t rect_merge(const rect_t r1, const rect_t r2)
{
	return rect_createWithCorners(
			GLM_MIN(rect_minX(r1), rect_minX(r2)),
			GLM_MIN(rect_minY(r1), rect_minY(r2)),
			GLM_MAX(rect_maxX(r1), rect_maxX(r2)),
			GLM_MAX(rect_maxY(r1), rect_maxY(r2)));
}

static __inline__ rect_t rect_scale(const rect_t rect, const vec2_t scale)
{
	vec2_t newSize = vec2_mul(rect.size, scale);
	vec2_t originOffset = vec2_scalarDiv(vec2_sub(rect.size, newSize), 2.0f);
	vec2_t newOrigin = vec2_add(rect.origin, originOffset);

	rect_t out;
	out.o = newOrigin;
	out.s = newSize;
	return out;
}

static __inline__ float rect_area(const rect_t rect)
{
	return rect.size.w * rect.size.h;
}

static __inline__ bool rect_intersectsLineSeg(const rect_t rect, const vec2_t a, const vec2_t b) {
	rect_t lineSegRect = rect_createWithCorners(GLM_MIN(a.x, b.x), GLM_MIN(a.y, b.y), GLM_MAX(a.x, b.x), GLM_MAX(a.y, b.y));
	if(rect_intersects(rect, lineSegRect)) {
		vec2_t axis = vec2_create(b.y - a.y, b.x - a.x);
		vec2_t offset = vec2_add(a, vec2_add(b, rect.size));

		return fabsf(vec2_dot(axis, offset)) < fabsf(axis.x*rect.size.w) + fabsf(axis.y*rect.size.h);
	}
	return false;
}

static __inline__ rect_t rect_translate(const rect_t aRect, const vec2_t aTranslationVector)
{
	rect_t out = { aRect.o.x + aTranslationVector.x, aRect.o.y + aTranslationVector.y, aRect.s.w, aRect.s.h };
	return out;
}

#ifdef __cplusplus
}
#endif
#endif
