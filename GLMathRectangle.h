#ifndef GL_MATH_RECT_H
#define GL_MATH_RECT_H

#include "GLMathTypes.h"
#include "GLMathVector.h"
#ifdef USE_ACCELERATE_FRAMEWORK
#import <Accelerate/Accelerate.h>
#endif
#include <math.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GLM_MAX(x,y) ( ((x)>(y)) ? (x) : (y) )
#define GLM_MIN(x,y) ( ((x)<(y)) ? (x) : (y) )

#pragma mark - Prototypes

static __inline__ rect_t rect_create(float left, float bottom, float right, float top);
static __inline__ float rect_maxX(const rect_t rect);
static __inline__ float rect_minX(const rect_t rect);
static __inline__ float rect_maxY(const rect_t rect);
static __inline__ float rect_minY(const rect_t rect);
// True if r1&2 intersect
static __inline__ bool rect_intersects(const rect_t r1, const rect_t r2);
// True if r1 contains r2
static __inline__ bool rect_contains(const rect_t r1, const rect_t r2);
// Returns a rectangle containing both rectangles
static __inline__ rect_t rect_merge(const rect_t r1, const rect_t r2);
// Returns the area of rect
static __inline__ float rect_area(const rect_t rect);
// True if rect intersects with the line segment between a&b
static __inline__ bool rect_intersectsLineSeg(const rect_t rect, const vec2_t a, const vec2_t b);
// Translates rect by the given vector
static __inline__ rect_t rect_translate(const rect_t aRect, const vec2_t aTranslationVector);

#pragma mark Implementations
static __inline__ rect_t rect_create(float left, float bottom, float right, float top)
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
static __inline__ bool rect_contains(const rect_t r1, const rect_t r2)
{
	return (rect_minX(r1) <= rect_minX(r2)
	        && rect_maxX(r2) >= rect_maxX(r1)
	        && rect_minY(r1) <= rect_minY(r2)
	        && rect_maxY(r2) >= rect_maxY(r1));
}
static __inline__ rect_t rect_merge(const rect_t r1, const rect_t r2)
{
	return rect_create(
			GLM_MIN(rect_minX(r1),          rect_minX(r2)),
			GLM_MIN(rect_minY(r1),          rect_minY(r2)),
			GLM_MAX(rect_maxX(r1) - r1.o.x, rect_maxX(r2) - r2.o.x),
			GLM_MAX(rect_maxY(r1) - r1.o.y, rect_maxY(r2) - r2.o.y));
}
static __inline__ float rect_area(const rect_t rect)
{
	return rect.size.w * rect.size.h;
}
static __inline__ bool rect_intersectsLineSeg(const rect_t rect, const vec2_t a, const vec2_t b) {
	rect_t lineSegRect = rect_create(GLM_MIN(a.x, b.x), GLM_MIN(a.y, b.y), GLM_MAX(a.x, b.x), GLM_MAX(a.y, b.y));
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
