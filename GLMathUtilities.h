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

#ifndef GL_MATH_UTILS_H
#define GL_MATH_UTILS_H

#include <GLMath/GLMathTypes.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#define GLM_MAX(x,y) ( ((x)>(y)) ? (x) : (y) )
#define GLM_MIN(x,y) ( ((x)<(y)) ? (x) : (y) )
#define GLM_CLAMP(x, min, max) GLM_MAX(min, GLM_MIN(x, max));

#pragma mark - Prototypes

// Utilities
static __inline__ GLMFloat degToRad(GLMFloat degrees) __asm("__degToRad");
static __inline__ GLMFloat radToDeg(GLMFloat radians) __asm("__radToDeg");
    
static __inline__ GLMFloat fastPow(GLMFloat x,GLMFloat y) __asm("__fastPow");


mat4_t mat4_perspective(GLMFloat fov_radians, GLMFloat aspect, GLMFloat zNear, GLMFloat zFar);
mat4_t mat4_frustum(GLMFloat left, GLMFloat right, GLMFloat bottom, GLMFloat top, GLMFloat near, GLMFloat far);
// Generates an orthogonal viewing matrix
mat4_t mat4_ortho(GLMFloat left, GLMFloat right, GLMFloat bottom, GLMFloat top, GLMFloat near, GLMFloat far);
// Generates a lookat camera viewing matrix
mat4_t mat4_lookat(GLMFloat eyeX, GLMFloat eyeY, GLMFloat eyeZ,
                   GLMFloat centerX, GLMFloat centerY, GLMFloat centerZ,
                   GLMFloat upX, GLMFloat upY, GLMFloat upZ);

void printVec2(vec2_t vec);
void printVec3(vec3_t vec);
void printVec4(vec4_t vec);
void printMat3(mat3_t mat);
void printMat4(mat4_t mat);
void printQuat(quat_t quat);

static __inline__ bool GLMFloatArr_equals(const GLMFloat *a1, const GLMFloat *a2, unsigned int len) __asm("__GLMFloatArr_equals");
static __inline__ bool vec2_equals(const vec2_t v1, const vec2_t v2) __asm("__vec2_equals");
static __inline__ bool vec3_equals(const vec3_t v1, const vec3_t v2) __asm("__vec3_equals");
static __inline__ bool vec4_equals(const vec4_t v1, const vec4_t v2) __asm("__vec4_equals");
static __inline__ bool mat4_equals(const mat4_t m1, const mat4_t m2) __asm("__mat4_equals");
static __inline__ bool quat_equals(const quat_t q1, const quat_t q2) __asm("__quat_equals");


#pragma mark Implementations

static __inline__ GLMFloat degToRad(GLMFloat degrees) { return degrees * (M_PI / 180.0); }
static __inline__ GLMFloat radToDeg(GLMFloat radians) { return radians * (180.0 / M_PI); }

static __inline__ GLMFloat fastPow(GLMFloat x,GLMFloat y)
{
#ifdef GLM_USE_DOUBLE
    return exp2(y*log2(x));
#else
    return exp2f(y*log2f(x));
#endif
}

#ifdef ANDROID
static __inline__ GLMFloat log2f(GLMFloat f)
{
	return logf(f) * (GLMFloat) (1.0 / M_LN2);
}
#endif

static __inline__ bool GLMFloatArr_equals(const GLMFloat *a1, const GLMFloat *a2, unsigned int len) {
	for(int i = 0; i < len; ++i) {
		if(a1[i] != a2[i])
			return false;
	}
	return true;
}
static __inline__ bool vec2_equals(const vec2_t v1, const vec2_t v2) {
	return GLMFloatArr_equals(GLM_FCAST(v1), GLM_FCAST(v2), 2);
}
static __inline__ bool vec3_equals(const vec3_t v1, const vec3_t v2) {
	return GLMFloatArr_equals(GLM_FCAST(v1), GLM_FCAST(v2), 3);
}
static __inline__ bool vec4_equals(const vec4_t v1, const vec4_t v2) {
	return GLMFloatArr_equals(GLM_FCAST(v1), GLM_FCAST(v2), 4);
}
static __inline__ bool mat4_equals(const mat4_t m1, const mat4_t m2) {
	return GLMFloatArr_equals(GLM_FCAST(m1), GLM_FCAST(m2), 16);
}
static __inline__ bool quat_equals(const quat_t q1, const quat_t q2) {
	return GLMFloatArr_equals(GLM_FCAST(q1), GLM_FCAST(q2), 4);
}

#ifdef __cplusplus
}
#endif
#endif
