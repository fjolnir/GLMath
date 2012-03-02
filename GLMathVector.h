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

#ifndef GL_MATH_VEC_H
#define GL_MATH_VEC_H

#include <GLMath/GLMathTypes.h>
#ifdef USE_ACCELERATE_FRAMEWORK
#include <Accelerate/Accelerate.h>
#endif
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Prototypes

// Vector math functions
static __inline__ vec2_t vec2_create(float x, float y) __asm("__vec2_create");
static __inline__ vec2_t vec2_add(const vec2_t v1, const vec2_t v2) __asm("__vec2_add");
static __inline__ vec2_t vec2_sub(const vec2_t v1, const vec2_t v2) __asm("__vec2_sub");
static __inline__ vec2_t vec2_mul(const vec2_t v1, const vec2_t v2) __asm("__vec2_mul");
static __inline__ vec2_t vec2_div(const vec2_t v1, const vec2_t v2) __asm("__vec2_div");
static __inline__ float vec2_dot(const vec2_t v1, const vec2_t v2) __asm("__vec2_dot");
static __inline__ float vec2_magSquared(const vec2_t v) __asm("__vec2_magSquared");
static __inline__ float vec2_mag(const vec2_t v) __asm("__vec2_mag");
static __inline__ vec2_t vec2_normalize(const vec2_t v) __asm("__vec2_normalize");
static __inline__ float vec2_dist(const vec2_t v1, const vec2_t v2) __asm("__vec2_dist");
static __inline__ vec2_t vec2_scalarMul(const vec2_t v, float s) __asm("__vec2_scalarMul");
static __inline__ vec2_t vec2_scalarDiv(const vec2_t v, float s) __asm("__vec2_scalarDiv");
static __inline__ vec2_t vec2_scalarAdd(const vec2_t v, float s) __asm("__vec2_scalarAdd");
static __inline__ vec2_t vec2_scalarSub(const vec2_t v, float s) __asm("__vec2_scalarSub");
static __inline__ vec2_t vec2_negate(const vec2_t v) __asm("__vec2_negate");
static __inline__ vec2_t vec2_floor(vec2_t v) __asm("__vec2_floor");

static __inline__ vec3_t vec3_create(float x, float y, float z) __asm("__vec3_create");
static __inline__ vec3_t vec3_add(const vec3_t v1, const vec3_t v2) __asm("__vec3_add");
static __inline__ vec3_t vec3_sub(const vec3_t v1, const vec3_t v2) __asm("__vec3_sub");
static __inline__ vec3_t vec3_mul(const vec3_t v1, const vec3_t v2) __asm("__vec3_mul");
static __inline__ vec3_t vec3_div(const vec3_t v1, const vec3_t v2) __asm("__vec3_div");
static __inline__ float vec3_dot(const vec3_t v1, const vec3_t v2) __asm("__vec3_dot");
static __inline__ float vec3_magSquared(const vec3_t v) __asm("__vec3_magSquared");
static __inline__ float vec3_mag(const vec3_t v) __asm("__vec3_mag");
static __inline__ vec3_t vec3_normalize(const vec3_t v) __asm("__vec3_normalize");
static __inline__ float vec3_dist(const vec3_t v1, const vec3_t v2) __asm("__vec3_dist");
static __inline__ vec3_t vec3_scalarMul(const vec3_t v, float s) __asm("__vec3_scalarMul");
static __inline__ vec3_t vec3_scalarDiv(const vec3_t v, float s) __asm("__vec3_scalarDiv");
static __inline__ vec3_t vec3_scalarAdd(const vec3_t v, float s) __asm("__vec3_scalarAdd");
static __inline__ vec3_t vec3_scalarSub(const vec3_t v, float s) __asm("__vec3_scalarSub");
static __inline__ vec3_t vec3_cross(const vec3_t v1, const vec3_t v2) __asm("__vec3_cross");
static __inline__ vec3_t vec3_negate(const vec3_t v) __asm("__vec3_negate");
static __inline__ vec3_t vec3_floor(vec3_t v) __asm("__vec3_floor");

static __inline__ vec4_t vec4_create(float x, float y, float z, float w) __asm("__vec4_create");
static __inline__ vec4_t vec4_add(const vec4_t v1, const vec4_t v2) __asm("__vec4_add");
static __inline__ vec4_t vec4_sub(const vec4_t v1, const vec4_t v2) __asm("__vec4_sub");
static __inline__ vec4_t vec4_mul(const vec4_t v1, const vec4_t v2) __asm("__vec4_mul");
static __inline__ vec4_t vec4_div(const vec4_t v1, const vec4_t v2) __asm("__vec4_div");
static __inline__ float vec4_dot(const vec4_t v1, const vec4_t v2) __asm("__vec4_dot");
static __inline__ float vec4_magSquared(const vec4_t v) __asm("__vec4_magSquared");
static __inline__ float vec4_mag(const vec4_t v) __asm("__vec4_mag");
static __inline__ float vec4_dist(const vec4_t v1, const vec4_t v2) __asm("__vec4_dist");
static __inline__ vec4_t vec4_scalarMul(const vec4_t v, float s) __asm("__vec4_scalarMul");
static __inline__ vec4_t vec4_scalarDiv(const vec4_t v, float s) __asm("__vec4_scalarDiv");
static __inline__ vec4_t vec4_scalarAdd(const vec4_t v, float s) __asm("__vec4_scalarAdd");
static __inline__ vec4_t vec4_scalarSub(const vec4_t v, float s) __asm("__vec4_scalarSub");
static __inline__ vec4_t vec4_cross(const vec4_t v1, const vec4_t v2) __asm("__vec4_cross");
static __inline__ vec4_t vec4_negate(const vec4_t v) __asm("__vec4_negate");
static __inline__ vec4_t vec4_floor(vec4_t v) __asm("__vec4_floor");

#pragma mark Implementations

#pragma mark - ~ Vectors(2)
static __inline__ vec2_t vec2_create(float x, float y) {
	vec2_t out = { x, y };
	return out;
}

static __inline__ vec2_t vec2_add(const vec2_t v1, const vec2_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec2_t out;
	vDSP_vadd(v1.f, 1, v2.f, 1, out.f, 1, 2);
	return out;
#else
	return (vec2_t){ v1.x + v2.x, v1.y + v2.y };
#endif
}

static __inline__ vec2_t vec2_sub(const vec2_t v1, const vec2_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec2_t out;
	vDSP_vsub(v2.f, 1, v1.f, 1, out.f, 1, 2);
	return out;
#else
	return (vec2_t){ v1.x - v2.x, v1.y - v2.y };
#endif
}

static __inline__ vec2_t vec2_mul(const vec2_t v1, const vec2_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec2_t out;
	vDSP_vmul(v1.f, 1, v2.f, 1, out.f, 1, 2);
	return out;
#else
	return (vec2_t){ v1.x * v2.x, v1.y * v2.y };
#endif
}

static __inline__ vec2_t vec2_div(const vec2_t v1, const vec2_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec2_t out;
	vDSP_vdiv((float *)v2.f, 1, (float *)v1.f, 1, out.f, 1, 2);
	return out;
#else
	return (vec2_t){ v1.x / v2.x, v1.y / v2.y };
#endif
}

static __inline__ float vec2_dot(const vec2_t v1, const vec2_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	float out;
	vDSP_dotpr(v1.f, 1, v2.f, 1, &out, 2);
	return out;
#else
	return v1.x * v2.x + v1.y * v2.y;
#endif
}

static __inline__ float vec2_magSquared(const vec2_t v) {
#ifdef USE_ACCELERATE_FRAMEWORK
	float magnitudes[2];
	vDSP_vsq(v.f, 1, magnitudes, 1, 2);
	return magnitudes[0] + magnitudes[1];
#else
	return (v.x * v.x) + (v.y * v.y);
#endif
}

static __inline__ float vec2_mag(const vec2_t v) {
	return sqrtf(vec2_magSquared(v));
}

static __inline__ vec2_t vec2_normalize(const vec2_t v) {
	return vec2_scalarDiv(v, vec2_mag(v));
}

static __inline__ float vec2_dist(const vec2_t v1, const vec2_t v2) {
	return vec2_mag(vec2_sub(v2, v1));
}

static __inline__ vec2_t vec2_scalarMul(const vec2_t v, float s) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec2_t out;
	vDSP_vsmul(v.f, 1, &s, out.f, 1, 2);
	return out;
#else
	return  (vec2_t){ v.x * s, v.y * s };
#endif

}

static __inline__ vec2_t vec2_scalarDiv(const vec2_t v, float s) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec2_t out;
	vDSP_vsdiv((float*)v.f, 1, &s, out.f, 1, 2);
	return out;
#else
	return (vec2_t){ v.x / s, v.y / s };
#endif
}

static __inline__ vec2_t vec2_negate(const vec2_t v) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec2_t out;
	vDSP_vneg ((float*)v.f, 1, out.f, 1, 2);
	return out;
#else
	return vec2_scalarMul(v, -1.0f);
#endif
}

static __inline__ vec2_t vec2_scalarAdd(const vec2_t v, float s)
{
    return vec2_create(v.x+s, v.y+s);
}

static __inline__ vec2_t vec2_scalarSub(const vec2_t v, float s)
{
    return vec2_create(v.x-s, v.y-s);
}

static __inline__ vec2_t vec2_floor(vec2_t v)
{
	vec2_t out = { floorf(v.x), floorf(v.y) };
	return out;
}


#pragma mark - ~ Vectors(3)
static __inline__ vec3_t vec3_create(float x, float y, float z) {
	vec3_t out = { x, y, z };
	return out;
}

static __inline__ vec3_t vec3_add(const vec3_t v1, const vec3_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec3_t out;
	vDSP_vadd(v1.f, 1, v2.f, 1, out.f, 1, 3);
	return out;
#else
	return (vec3_t){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
#endif
}

static __inline__ vec3_t vec3_sub(const vec3_t v1, const vec3_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec3_t out;
	vDSP_vsub(v2.f, 1, v1.f, 1, out.f, 1, 3);
	return out;
#else
	return (vec3_t){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
#endif
}

static __inline__ vec3_t vec3_mul(const vec3_t v1, const vec3_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec3_t out;
	vDSP_vmul(v1.f, 1, v2.f, 1, out.f, 1, 3);
	return out;
#else
	return (vec3_t){ v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
#endif
}

static __inline__ vec3_t vec3_div(const vec3_t v1, const vec3_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec3_t out;
	vDSP_vdiv((float *)v2.f, 1, (float *)v1.f, 1, out.f, 1, 3);
	return out;
#else
	return (vec3_t){ v1.x / v2.x, v1.y / v2.y, v1.z / v2.z };
#endif
}

static __inline__ float vec3_dot(const vec3_t v1, const vec3_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	float out;
	vDSP_dotpr(v1.f, 1, v2.f, 1, &out, 3);
	return out;
#else
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
#endif
}

static __inline__ float vec3_magSquared(const vec3_t v) {
#ifdef USE_ACCELERATE_FRAMEWORK
	float magnitudes[3];
	vDSP_vsq(v.f, 1, magnitudes, 1, 3);
	return magnitudes[0] + magnitudes[1] + magnitudes[2];
#else
	return v.x * v.x + v.y * v.y + v.z * v.z;
#endif
}

static __inline__ float vec3_mag(const vec3_t v) {
	return sqrtf(vec3_magSquared(v));
}

static __inline__ vec3_t vec3_normalize(const vec3_t v) {
	return vec3_scalarDiv(v, vec3_mag(v));
}

static __inline__ float vec3_dist(const vec3_t v1, const vec3_t v2) {
	return vec3_mag(vec3_sub(v2, v1));
}

static __inline__ vec3_t vec3_scalarMul(const vec3_t v, float s) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec3_t out;
	vDSP_vsmul(v.f, 1, &s, out.f, 1, 3);
	return out;
#else
	return (vec3_t){ v.x * s, v.y * s, v.z * s };
#endif
}

static __inline__ vec3_t vec3_scalarDiv(const vec3_t v, float s) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec3_t out;
	vDSP_vsdiv((float*)v.f, 1, &s, out.f, 1, 3);
	return out;
#else
	return (vec3_t){ v.x / s, v.y / s, v.z / s };
#endif
}

static __inline__ vec3_t vec3_scalarAdd(const vec3_t v, float s)
{
    return vec3_create(v.x+s, v.y+s, v.z+s);
}

static __inline__ vec3_t vec3_scalarSub(const vec3_t v, float s)
{
    return vec3_create(v.x-s, v.y-s, v.z-s);
}

static __inline__ vec3_t vec3_cross(const vec3_t v1, const vec3_t v2) {
	return (vec3_t){ v1.y * v2.z - v1.z * v2.y,
	                 v1.z * v2.x - v1.x * v2.z,
	                 v1.x * v2.y - v1.y * v2.x };
}

static __inline__ vec3_t vec3_negate(const vec3_t v) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec3_t out;
	vDSP_vneg ((float*)v.f, 1, out.f, 1, 3);
	return out;
#else
	return vec3_scalarMul(v, -1.0f);
#endif
}

static __inline__ vec3_t vec3_floor(vec3_t v)
{
	vec3_t out = { floorf(v.x), floorf(v.y), floorf(v.z) };
	return out;
}


#pragma mark - ~ Vectors(4)
static __inline__ vec4_t vec4_create(float x, float y, float z, float w) {
	vec4_t out = { x, y, z, w };
	return out;
}

static __inline__ vec4_t vec4_add(const vec4_t v1, const vec4_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec4_t out;
	vDSP_vadd(v1.f, 1, v2.f, 1, out.f, 1, 4);
	return out;
#else
	return (vec4_t){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
#endif
}

static __inline__ vec4_t vec4_sub(const vec4_t v1, const vec4_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec4_t out;
	vDSP_vsub(v2.f, 1, v1.f, 1, out.f, 1, 4);
	return out;
#else
	return (vec4_t){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
#endif
}

static __inline__ vec4_t vec4_mul(const vec4_t v1, const vec4_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec4_t out;
	vDSP_vmul(v1.f, 1, v2.f, 1, out.f, 1, 4);
	return out;
#else
	return (vec4_t){ v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w };
#endif
}

static __inline__ vec4_t vec4_div(const vec4_t v1, const vec4_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec4_t out;
	vDSP_vdiv((float *)v2.f, 1, (float *)v1.f, 1, out.f, 1, 4);
	return out;
#else
	return (vec4_t){ v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w };
#endif
}

static __inline__ float vec4_dot(const vec4_t v1, const vec4_t v2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	float out;
	vDSP_dotpr(v1.f, 1, v2.f, 1, &out, 4);
	return out;
#else
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
#endif
}

static __inline__ float vec4_magSquared(const vec4_t v) {
#ifdef USE_ACCELERATE_FRAMEWORK
	float magnitudes[4];
	vDSP_vsq(v.f, 1, magnitudes, 1, 4);
	return magnitudes[0] + magnitudes[1] + magnitudes[2] + magnitudes[3];
#else
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w);
#endif
}

static __inline__ float vec4_mag(const vec4_t v) {
	return sqrtf(vec4_magSquared(v));
}

static __inline__ vec4_t vec4_normalize(const vec4_t v) {
	return vec4_scalarDiv(v, vec4_mag(v));
}

static __inline__ float vec4_dist(const vec4_t v1, const vec4_t v2) {
	return vec4_mag(vec4_sub(v2, v1));
}

static __inline__ vec4_t vec4_scalarMul(const vec4_t v, float s) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec4_t out;
	vDSP_vsmul((float*)v.f, 1, &s, out.f, 1, 4);
	return out;
#else
	return (vec4_t){ v.x * s, v.y * s, v.z * s, v.w * s };
#endif
}

static __inline__ vec4_t vec4_scalarDiv(const vec4_t v, float s) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec4_t out;
	vDSP_vsdiv((float*)v.f, 1, &s, out.f, 1, 4);
	return out;
#else
	return (vec4_t){ v.x / s, v.y / s, v.z / s, v.w / s };
#endif
}

static __inline__ vec4_t vec4_scalarAdd(const vec4_t v, float s)
{
    return vec4_create(v.x+s, v.y+s, v.z+s, v.w+s);
}

static __inline__ vec4_t vec4_scalarSub(const vec4_t v, float s)
{
    return vec4_create(v.x-s, v.y-s, v.z-s, v.w-s);
}

static __inline__ vec4_t vec4_cross(const vec4_t v1, const vec4_t v2) {
	return (vec4_t){ v1.y * v2.z - v1.z * v2.y,
	                 v1.z * v2.x - v1.x * v2.z,
	                 v1.x * v2.y - v1.y * v2.x,
	                 0.0 };
}

static __inline__ vec4_t vec4_negate(const vec4_t v) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec4_t out;
	vDSP_vneg ((float*)v.f, 1, out.f, 1, 4);
	return out;
#else
	return vec4_scalarMul(v, -1.0f);
#endif
}

static __inline__ vec4_t vec4_floor(vec4_t v)
{
	vec4_t out = { floorf(v.x), floorf(v.y), floorf(v.z), floorf(v.w) };
	return out;
}

#ifdef __cplusplus
}
#endif
#endif
