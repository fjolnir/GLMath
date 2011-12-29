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

#include "GLMathTypes.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Prototypes

// Utilities
static __inline__ float degToRad(float degrees);
static __inline__ float radToDeg(float radians);

mat4_t mat4_perspective(float fov_radians, float aspect, float zNear, float zFar);
// Generates an orthogonal viewing matrix
mat4_t mat4_ortho(float left, float right, float bottom, float top, float near, float far);
// Generates a lookat camera viewing matrix
mat4_t mat4_lookat(float eyeX, float eyeY, float eyeZ,
                   float centerX, float centerY, float centerZ,
                   float upX, float upY, float upZ);

void printVec2(vec2_t vec);
void printVec3(vec3_t vec);
void printVec4(vec4_t vec);
void printMat3(mat3_t mat);
void printMat4(mat4_t mat);
void printQuat(quat_t quat);

static __inline__ bool floatArr_equals(const float *a1, const float *a2, unsigned int len);
static __inline__ bool vec2_equals(const vec2_t v1, const vec2_t v2);
static __inline__ bool vec3_equals(const vec3_t v1, const vec3_t v2);
static __inline__ bool vec4_equals(const vec4_t v1, const vec4_t v2);
static __inline__ bool mat4_equals(const mat4_t m1, const mat4_t m2);
static __inline__ bool quat_equals(const quat_t q1, const quat_t q2);


#pragma mark Implementations

static __inline__ float degToRad(float degrees) { return degrees * (M_PI / 180.0f); };
static __inline__ float radToDeg(float radians) { return radians * (180.0f / M_PI); };

static __inline__ bool floatArr_equals(const float *a1, const float *a2, unsigned int len) {
	for(int i = 0; i < len; ++i) {
		if(a1[i] != a2[i])
			return false;
	}
	return true;
}
static __inline__ bool vec2_equals(const vec2_t v1, const vec2_t v2) {
	return floatArr_equals(v1.f, v2.f, 2);
}
static __inline__ bool vec3_equals(const vec3_t v1, const vec3_t v2) {
	return floatArr_equals(v1.f, v2.f, 3);
}
static __inline__ bool vec4_equals(const vec4_t v1, const vec4_t v2) {
	return floatArr_equals(v1.f, v2.f, 4);
}
static __inline__ bool mat4_equals(const mat4_t m1, const mat4_t m2) {
	return floatArr_equals(m1.f, m2.f, 16);
}
static __inline__ bool quat_equals(const quat_t q1, const quat_t q2) {
	return floatArr_equals(q1.f, q2.f, 4);
}

#ifdef __cplusplus
}
#endif
#endif
