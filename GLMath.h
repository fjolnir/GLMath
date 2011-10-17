// GLMath
//
// A Math utility library intended for use with computer graphics
// Uses vDSP to perform most operations
//
// Copyright (c) 2011, Fjölnir Ásgeirsson
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this list of conditions
// and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice, this list of
// conditions and the following disclaimer in the documentation and/or other materials provided with
// the distribution.
// Neither the name of Fjölnir Ásgeirsson nor the names of its contributors may be
// used to endorse or promote products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE

#ifndef GL_MATH_H
#define GL_MATH_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Types

// Vectors
typedef union {
	float f[2];
	struct { float x; float y; };
	struct { float w; float h; };
} vec2_t;

typedef union {
	float f[3];
	struct { float x; float y; float z; };
	struct { float r; float g; float b; };
} vec3_t;
typedef union {
	float f[4];
	struct { float x; float y; float z; float w; };
	struct { float r; float g; float b; float a; };
} vec4_t;

// Matrices
typedef union {
	float f[16];
	struct {
		float m00; float m01; float m02; float m03;
		float m10; float m11; float m12; float m13;
		float m20; float m21; float m22; float m23;
		float m30; float m31; float m32; float m33;
	};
} mat4_t;

// Quaternions
typedef union {
	float f[4];
	struct { float x; float y; float z; float w; };
} quat_t;


#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#import <Accelerate/Accelerate.h>

#define EPSILON (1.0E-8)

// Zero vectors
extern const vec2_t kVec2_zero;
extern const vec3_t kVec3_zero;
extern const vec4_t kVec4_zero;

extern const mat4_t kMat4_identity;
extern const mat4_t kMat4_zero;

// Implements a stack of float arrays with an arbitrary size (so it can be used to store both matrices&vectors)
typedef struct {
	float **items;
	unsigned int numberOfComponents;
	unsigned int capacity;
	unsigned int numberOfItems;
} float_stack_t;

#pragma mark - Prototypes

static float_stack_t *float_stack_create(unsigned int numberOfComponents, unsigned int initialCapacity);
static void float_stack_destroy(float_stack_t *stack);

// Pushes the passed item on to the top of the stack
static void float_stack_push_item(float_stack_t *stack, float *item);
// Pushes an identical copy of the currently topmost item onto the stack (or a zeroed item if no item currently exists)
static __inline__ void float_stack_push(float_stack_t *stack);
// Pops an item off the stack
static void float_stack_pop(float_stack_t *stack);
// Returns the topmost item in the stack
static __inline__ float *float_stack_current(float_stack_t *stack);

// Vector math functions
static __inline__ vec2_t vec2_add(const vec2_t v1, const vec2_t v2);
static __inline__ vec2_t vec2_sub(const vec2_t v1, const vec2_t v2);
static __inline__ vec2_t vec2_mul(const vec2_t v1, const vec2_t v2);
static __inline__ float vec2_dot(const vec2_t v1, const vec2_t v2);
static __inline__ float vec2_magSquared(const vec2_t v);
static __inline__ float vec2_mag(const vec2_t v);
static __inline__ vec2_t vec2_normalize(const vec2_t v);
static __inline__ float vec2_dist(const vec2_t v1, const vec2_t v2);
static __inline__ vec2_t vec2_scalarMul(const vec2_t v, float s);
static __inline__ vec2_t vec2_scalarDiv(const vec2_t v, float s);

static __inline__ vec3_t vec3_add(const vec3_t v1, const vec3_t v2);
static __inline__ vec3_t vec3_sub(const vec3_t v1, const vec3_t v2);
static __inline__ vec3_t vec3_mul(const vec3_t v1, const vec3_t v2);
static __inline__ float vec3_dot(const vec3_t v1, const vec3_t v2);
static __inline__ float vec3_magSquared(const vec3_t v);
static __inline__ float vec3_mag(const vec3_t v);
static __inline__ vec3_t vec3_normalize(const vec3_t v);
static __inline__ float vec3_dist(const vec3_t v1, const vec3_t v2);
static __inline__ vec3_t vec3_scalarMul(const vec3_t v, float s);
static __inline__ vec3_t vec3_scalarDiv(const vec3_t v, float s);

static __inline__ vec4_t vec4_add(const vec4_t v1, const vec4_t v2);
static __inline__ vec4_t vec4_sub(const vec4_t v1, const vec4_t v2);
static __inline__ vec4_t vec4_mul(const vec4_t v1, const vec4_t v2);
static __inline__ float vec4_dot(const vec4_t v1, const vec4_t v2);
static __inline__ float vec4_magSquared(const vec4_t v);
static __inline__ float vec4_mag(const vec4_t v);
static __inline__ float vec4_dist(const vec4_t v1, const vec4_t v2);
static __inline__ vec4_t vec4_scalarMul(const vec4_t v, float s);
static __inline__ vec4_t vec4_scalarDiv(const vec4_t v, float s);

// Matrix math functions
static __inline__ mat4_t mat4_mul(const mat4_t m1, const mat4_t m2);
static __inline__ vec4_t vec4_mul_mat4(const vec4_t v, const mat4_t m);
static __inline__ mat4_t mat4_inverse(const mat4_t m);
static __inline__ mat4_t mat4_transpose(const mat4_t m);

// Quaternion math functions
static quat_t quat_makef(float x, float y, float z, float angle);
static quat_t quat_makev(vec3_t axis, float angle);
static mat4_t quat_to_mat4(const quat_t q);
static quat_t mat4_to_quat(const mat4_t m);
static mat4_t quat_to_ortho(const quat_t q);
static quat_t ortho_to_quat(const mat4_t m);
static __inline__ float quat_magSquared(const quat_t q);
static __inline__ float quat_mag(const quat_t q);
static quat_t quat_computeW(quat_t q);
static __inline__ quat_t quat_normalize(quat_t q);
static __inline__ quat_t quat_multQuat(const quat_t qA, const quat_t qB);
static __inline__ vec4_t quat_rotatePoint(const quat_t q, const vec4_t v);
static __inline__ quat_t quat_inverse(const quat_t q);
static __inline__ float quat_dotProduct(const quat_t qA, const quat_t qB);
static __inline__ quat_t quat_slerp(const quat_t qA, const quat_t qB, float t);

// Affine transforms
static __inline__ mat4_t mat4_make_translation(float x, float y, float z);
static __inline__ void mat4_translate(mat4_t mat, float x, float y, float z);
static __inline__ mat4_t mat4_make_rotation(float angle, float x, float y, float z);
static __inline__ mat4_t mat4_rotate(mat4_t mat, float angle, float x, float y, float z);
static __inline__ mat4_t mat4_make_scale(float x, float y, float z);
static __inline__ mat4_t mat4_scale(mat4_t mat, float x, float y, float z);

// Utilities
static mat4_t mat4_perspective(float fov_radians, float aspect, float zNear, float zFar);
// Generates an orthogonal viewing matrix
static mat4_t mat4_ortho(float left, float right, float bottom, float top, float near, float far);

static void printVec2(vec2_t vec);
static void printVec3(vec3_t vec);
static void printVec4(vec4_t vec);
static void printMat4(mat4_t mat);
static void printQuat(quat_t quat);

static bool floatArr_equals(const float *a1, const float *a2, unsigned int len);
static bool vec2_equals(const vec2_t v1, const vec2_t v2);
static bool vec3_equals(const vec3_t v1, const vec3_t v2);
static bool vec4_equals(const vec4_t v1, const vec4_t v2);
static bool mat4_equals(const mat4_t m1, const mat4_t m2);
static bool quat_equals(const quat_t q1, const quat_t q2);


#pragma mark Implementations

#pragma mark ~ Stack

static float_stack_t *float_stack_create(unsigned int numberOfComponents, unsigned int initialCapacity) {
	float_stack_t *out;
	out = malloc(sizeof(float_stack_t));
	out->numberOfItems = 0;
	out->numberOfComponents = numberOfComponents;
	out->capacity = initialCapacity;
	out->items = malloc(sizeof(float*)*initialCapacity);

	return out;
}
static void float_stack_destroy(float_stack_t *stack) {
	free(stack->items);
	free(stack);
}


// Pushes the passed item on to the top of the stack
static void float_stack_push_item(float_stack_t *stack, float *item) {
	if((stack->numberOfItems + 1) == stack->capacity) {
		// If the stack is full we double it's size
		stack->capacity *= 2;
		stack->items = realloc(stack->items, stack->capacity);
	}
	stack->items[stack->numberOfItems] = calloc(stack->numberOfComponents, sizeof(float));
	if(item != NULL)
		memcpy(stack->items[stack->numberOfItems], item, sizeof(float)*stack->numberOfComponents);

	++stack->numberOfItems;
}

// Pushes an identical copy of the currently topmost item onto the stack (or a zeroed item if no item currently exists)
static __inline__ void float_stack_push(float_stack_t *stack) {
	float_stack_push_item(stack, stack->numberOfItems >= 1 ? stack->items[stack->numberOfItems-1] : NULL);
}

// Pops an item off the stack
static void float_stack_pop(float_stack_t *stack) {
	if(stack->numberOfItems <= 1)
		return;
	--stack->numberOfItems;
	free(stack->items[stack->numberOfItems]);
	// If the stack is far from full free up some memory
	if(stack->capacity > 32 && stack->numberOfItems < stack->capacity/2) {
		stack->capacity /= 2;
		stack->items = realloc(stack->items, stack->capacity);
	}
}
// Returns the topmost item in the stack
static __inline__ float *float_stack_current(float_stack_t *stack) {
	assert(stack->numberOfItems > 0);
	return stack->items[stack->numberOfItems-1];
}

#pragma mark - ~ Vectors(2)
static __inline__ vec2_t vec2_add(const vec2_t v1, const vec2_t v2) {
	vec2_t out;
	vDSP_vadd(v1.f, 1, v2.f, 1, out.f, 1, 2);
	return out;
}
static __inline__ vec2_t vec2_sub(const vec2_t v1, const vec2_t v2) {
	vec2_t out;
	vDSP_vsub(v1.f, 1, v2.f, 1, out.f, 1, 2);
	return out;
}
static __inline__ vec2_t vec2_mul(const vec2_t v1, const vec2_t v2) {
	vec2_t out;
	vDSP_vmul(v1.f, 1, v2.f, 1, out.f, 1, 2);
	return out;
}
static __inline__ float vec2_dot(const vec2_t v1, const vec2_t v2) {
	float out;
	vDSP_dotpr(v1.f, 1, v2.f, 1, &out, 2);
	return out;
}
static __inline__ float vec2_magSquared(const vec2_t v) {
	float magnitudes[2];
	vDSP_vsq(v.f, 1, magnitudes, 1, 2);
	return magnitudes[0] + magnitudes[1];
}
static __inline__ float vec2_mag(const vec2_t v) {
	return sqrtf(vec2_magSquared(v));
}
static __inline__ vec2_t vec2_normalize(const vec2_t v) {
	return vec2_scalarDiv(v, vec2_mag(v));
}
static __inline__ float vec2_dist(const vec2_t v1, const vec2_t v2) {
	float magnitudes[2];
	vDSP_vdist((float*)v1.f, 1, (float*)v2.f, 1, magnitudes, 1, 2);
	return magnitudes[0] + magnitudes[1];
}
static __inline__ vec2_t vec2_scalarMul(const vec2_t v, float s) {
	vec2_t out;
	vDSP_vsmul(v.f, 1, &s, out.f, 1, 2);
	return out;
}
static __inline__ vec2_t vec2_scalarDiv(const vec2_t v, float s) {
	vec2_t out;
	vDSP_vsdiv((float*)v.f, 1, &s, out.f, 1, 2);
	return out;
}

#pragma mark - ~ Vectors(3)
static __inline__ vec3_t vec3_add(const vec3_t v1, const vec3_t v2) {
	vec3_t out;
	vDSP_vadd(v1.f, 1, v2.f, 1, out.f, 1, 3);
	return out;
}
static __inline__ vec3_t vec3_sub(const vec3_t v1, const vec3_t v2) {
	vec3_t out;
	vDSP_vsub(v1.f, 1, v2.f, 1, out.f, 1, 3);
	return out;
}
static __inline__ vec3_t vec3_mul(const vec3_t v1, const vec3_t v2) {
	vec3_t out;
	vDSP_vmul(v1.f, 1, v2.f, 1, out.f, 1, 3);
	return out;
}
static __inline__ float vec3_dot(const vec3_t v1, const vec3_t v2) {
	float out;
	vDSP_dotpr(v1.f, 1, v2.f, 1, &out, 3);
	return out;
}
static __inline__ float vec3_magSquared(const vec3_t v) {
	float magnitudes[3];
	vDSP_vsq(v.f, 1, magnitudes, 1, 3);
	return magnitudes[0] + magnitudes[1] + magnitudes[2];
}
static __inline__ float vec3_mag(const vec3_t v) {
	return sqrtf(vec3_magSquared(v));
}
static __inline__ vec3_t vec3_normalize(const vec3_t v) {
	return vec3_scalarDiv(v, vec3_mag(v));
}
static __inline__ float vec3_dist(const vec3_t v1, const vec3_t v2) {
	float magnitudes[3];
	vDSP_vdist((float*)v1.f, 1, (float*)v2.f, 1, magnitudes, 1, 3);
	return magnitudes[0] + magnitudes[1] + magnitudes[2];
}
static __inline__ vec3_t vec3_scalarMul(const vec3_t v, float s) {
	vec3_t out;
	vDSP_vsmul(v.f, 1, &s, out.f, 1, 3);
	return out;
}
static __inline__ vec3_t vec3_scalarDiv(const vec3_t v, float s) {
	vec3_t out;
	vDSP_vsdiv((float*)v.f, 1, &s, out.f, 1, 3);
	return out;
}

#pragma mark - ~ Vectors(4)
static __inline__ vec4_t vec4_add(const vec4_t v1, const vec4_t v2) {
	vec4_t out;
	vDSP_vadd(v1.f, 1, v2.f, 1, out.f, 1, 4);
	return out;
}
static __inline__ vec4_t vec4_sub(const vec4_t v1, const vec4_t v2) {
	vec4_t out;
	vDSP_vsub(v1.f, 1, v2.f, 1, out.f, 1, 4);
	return out;
}
static __inline__ vec4_t vec4_mul(const vec4_t v1, const vec4_t v2) {
	vec4_t out;
	vDSP_vmul(v1.f, 1, v2.f, 1, out.f, 1, 4);
	return out;
}
static __inline__ float vec4_dot(const vec4_t v1, const vec4_t v2) {
	float out;
	vDSP_dotpr(v1.f, 1, v2.f, 1, &out, 4);
	return out;
}
static __inline__ float vec4_magSquared(const vec4_t v) {
	float magnitudes[4];
	vDSP_vsq(v.f, 1, magnitudes, 1, 4);
	return magnitudes[0] + magnitudes[1] + magnitudes[2] + magnitudes[3];
}
static __inline__ float vec4_mag(const vec4_t v) {
	return sqrtf(vec4_magSquared(v));
}
static __inline__ vec4_t vec4_normalize(const vec4_t v) {
	return vec4_scalarDiv(v, vec4_mag(v));
}
static __inline__ float vec4_dist(const vec4_t v1, const vec4_t v2) {
	float magnitudes[4];
	vDSP_vdist((float*)v1.f, 1, (float*)v2.f, 1, magnitudes, 1, 4);
	return magnitudes[0] + magnitudes[1] + magnitudes[2] + magnitudes[3];
}
static __inline__ vec4_t vec4_scalarMul(const vec4_t v, float s) {
	vec4_t out;
	vDSP_vsmul((float*)v.f, 1, &s, out.f, 1, 4);
	return out;
}
static __inline__ vec4_t vec4_scalarDiv(const vec4_t v, float s) {
	vec4_t out;
	vDSP_vsdiv((float*)v.f, 1, &s, out.f, 1, 4);
	return out;
}

#pragma mark - ~ Matrices
static __inline__ mat4_t mat4_mul(const mat4_t m1, const mat4_t m2) {
	mat4_t out;
	vDSP_mmul((float*)m1.f, 1, (float*)m2.f, 1, out.f, 1, 4, 4, 4);
	return out;
}
static __inline__ vec4_t vec4_mul_mat4(const vec4_t v, const mat4_t m) {
	vec4_t out;
	vDSP_mmul((float*)v.f, 1, (float*)m.f, 1, out.f, 1, 1, 4, 4);
	return out;
}
static __inline__ mat4_t mat4_inverse(const mat4_t m) {
	mat4_t out;
	__CLPK_integer colsA, rowsA, colsB, rowsB, status;
	colsA = rowsA = colsB = rowsB = 4;
	__CLPK_integer pivotIndices[colsA];
	memcpy(out.f, kMat4_identity.f, sizeof(mat4_t));
	sgesv_(&colsA, &colsB, (float*)m.f, &rowsA, pivotIndices, out.f, &rowsB, &status);
	if(status != 0) {
		printf("Could not invert 4x4 matrix!");
		printMat4(m);
		out = kMat4_zero;
	}
	return out;
}
static __inline__ mat4_t mat4_transpose(const mat4_t m) {
	mat4_t out;
	vDSP_mtrans((float*)m.f, 1, out.f, 1, 4, 4);
	return out;
}

#pragma mark - ~ Quaternions
// Generates a unit quaternion
static quat_t quat_makef(float x, float y, float z, float angle) {
	vec3_t vec = { x, y, z };
	return quat_makev(vec, angle);
}
static quat_t quat_makev(vec3_t axis, float angle) {
	quat_t out;
	vec3_t normalized;
	normalized = vec3_normalize(axis);

	float sin = sinf(angle/2.0f);
	out.x = normalized.x*sin;
	out.y = normalized.y*sin;
	out.z = normalized.z*sin;
	out.w = cosf(angle/2.0f);

	return out;
}
// Generates the standard matrix representation of a quaternion
static mat4_t quat_to_mat4(const quat_t q) {
	mat4_t out;
	// Matrix representation of a quaternion:
	// q = [a, b, c, w]
	//       [1 0 0 0]     [ 0 1 0  0]     [ 0  0 1 0]     [ 0 0  0 1]
	// q = a*[0 1 0 0] + b*[-1 0 0  0] + c*[ 0  0 0 1] + w*[ 0 0 -1 0]
	//       [0 0 1 0]     [ 0 0 0 -1]     [-1  0 0 0]     [ 0 1  0 0]
	//       [0 0 0 1]     [ 0 0 1  0]     [ 0 -1 0 0]    [-1 0  0 0]
	out.f[0] = out.f[5] = out.f[10] = out.f[15] = q.f[0]; // a
	out.f[1] = out.f[14]                          = q.f[1]; // b
	out.f[4] = out.f[11]                          = -1.0f*q.f[1]; // b
	out.f[2] = out.f[7]                           = q.f[2]; // c
	out.f[8] = out.f[13]                          = -1.0f*q.f[2]; // c
	out.f[3] = out.f[9]                           = q.f[3];
	out.f[6] = out.f[12] = -1.0f*q.f[3];

	out.m13 = out.m23 = 0.0f;
	out.m30 = out.m31 = out.m32 = 0.0f;
	return out;
}
// Converts the standard matrix representation of a quaternion back to it's source
static quat_t mat4_to_quat(const mat4_t m) {
	// To convert back to a quat we just need to copy the first 3 items
	quat_t out = {0.0f};
	memcpy(out.f, m.f, sizeof(quat_t));
	return out;
}

// Generates the orthogonal matrix representation(rotation matrix) of a quaternion
static mat4_t quat_to_ortho(const quat_t q) {
//			¦				2		 2																			¦
//			¦ 1 - (2Y	+ 2Z )	 2XY + 2ZW				 2XZ - 2YW			 ¦
//			¦																										 ¦
//			¦													2		 2										¦
//	M = ¦ 2XY - 2ZW				 1 - (2X	+ 2Z )	 2YZ + 2XW			 ¦ (Transposed)
//			¦																										 ¦
//			¦																						2		 2	¦
//			¦ 2XZ + 2YW				 2YZ - 2XW				 1 - (2X	+ 2Y ) ¦
//			¦																										 ¦
	float xx = q.f[0]*q.f[0];
	float xy = q.f[0]*q.f[1];
	float xz = q.f[0]*q.f[2];
	float xw = q.f[0]*q.f[3];
	float yy = q.f[1]*q.f[1];
	float yz = q.f[1]*q.f[2];
	float yw = q.f[1]*q.f[3];
	float zz = q.f[2]*q.f[2];
	float zw = q.f[2]*q.f[3];

	mat4_t out;
	out.f[0]	= 1.0f - 2.0f*( yy + zz );
	out.f[4]	=		 2.0f*( xy - zw );
	out.f[8]	=		 2.0f*( xz + yw );
	out.f[1]	=		 2.0f*( xy + zw );
	out.f[5]	= 1 - 2.0f*( xx + zz );
	out.f[9]	=		 2.0f*( yz - xw );
	out.f[2]	=		 2.0f*( xz - yw );
	out.f[6]	=		 2.0f*( yz + xw );
	out.f[10] = 1.0f - 2.0f*( xx + yy );

	out.f[3] = out.f[7] = out.f[11] = out.f[12] = out.f[13] = out.f[14] = 0.0f;
	out.f[15] = 1.0f;

	return out;
}

static quat_t ortho_to_quat(const mat4_t m) {
	quat_t out;
	float trace = 1 + m.f[0] + m.f[5] + m.f[10];
	float s;
	// If the trace is too close to 0 we'll get serious distortion
	if(trace > 0.000001) {
		s = sqrtf(trace)*2.0f;
		out.f[0] = (m.f[9] - m.f[6]) / s;
		out.f[1] = (m.f[2] - m.f[8]) / s;
		out.f[2] = (m.f[4] - m.f[1]) / s;
		out.f[3] = s / 4.0f;
	}
	// If the trace is 0 then find which diagonal element has the greatest value
	else if(m.f[0] > m.f[5] && m.f[0] > m.f[10]) { // Col 0
		s = sqrtf(1.0f + m.f[0] - m.f[5] - m.f[10])*2.0f;
		out.f[0] = s / 4.0f;
		out.f[1] = (m.f[4] - m.f[1]) / s;
		out.f[2] = (m.f[2] - m.f[8]) / s;
		out.f[3] = (m.f[9] - m.f[6]) / s;
	} else if(m.f[5] > m.f[10]) { // Col 1
		s = sqrtf(1.0f + m.f[5] - m.f[0] - m.f[10])*2.0f;
		out.f[0] = (m.f[4] - m.f[1]) / s;
		out.f[1] = s / 4.0f;
		out.f[2] = (m.f[9] - m.f[6]) / s;
		out.f[3] = (m.f[2] - m.f[8]) / s;
	} else { // Col 2
		s = sqrtf(1.0f + m.f[10] - m.f[0] - m.f[5])*2.0f;
		out.f[0] = (m.f[2] - m.f[8]) / s;
		out.f[1] = (m.f[9] - m.f[6]) / s;
		out.f[2] = s / 4.0f;
		out.f[3] = (m.f[4] - m.f[1]) / s;
	}

	return out;
}

static __inline__ float quat_magSquared(const quat_t q) {
	return vec4_magSquared(*(const vec4_t *)&q);
}
static __inline__ float quat_mag(const quat_t q) {
	return vec4_mag(*(const vec4_t *)&q);
}
static quat_t quat_computeW(quat_t q) {
	quat_t out;
	memcpy(out.f, q.f, sizeof(quat_t));

	float t = 1.0f - quat_magSquared(*(const quat_t*)&out);

	if(t < 0.0f)
		out.f[3] = 0.0f;
	else
		out.f[3] = -1*sqrtf(t);

	return out;
}
static __inline__ quat_t quat_normalize(quat_t q) {
	vec4_t out;
	memcpy(out.f, q.f, sizeof(quat_t));

	float mag = quat_mag(*(const quat_t*)&out);
	// Normalize if the magnitude is > 0
	if (mag <= 0.0f)
		return *(quat_t *)&out;
	float normalizedMag = 1.0f / mag;
	out = vec4_scalarMul(out, normalizedMag);
	return *(quat_t *)&out;
}
static __inline__ quat_t quat_multQuat(const quat_t q1, const quat_t q2) {
	mat4_t q1m, q2m, temp;
	q1m = quat_to_mat4(q1);
	q2m = quat_to_mat4(q2);
	temp = mat4_mul(q1m, q2m);

	return mat4_to_quat(temp);
}
static __inline__ vec4_t quat_rotatePoint(const quat_t q, const vec4_t v) {
	mat4_t rotationMatrix;
	rotationMatrix = quat_to_ortho(q);
	return vec4_mul_mat4(v, rotationMatrix);
}
static __inline__ float quat_dotProduct(const quat_t q1, const quat_t q2) {
	return vec4_dot(*(const vec4_t*)&q1, *(const vec4_t*)&q2);
}
static __inline__ quat_t quat_inverse(const quat_t q) {
	// Multiply the vector by -1 and leave the angle alone
	vec4_t out;
	out = vec4_scalarMul(*(vec4_t *)&q, -1.0f);
	out.f[3] = q.f[3];
	return *(quat_t *)&out;
}

static __inline__ quat_t quat_slerp(const quat_t q1, const quat_t q2, float t) {
	quat_t out;
	// Return edge points without interpolating if the value is out of range
	if (t <= 0.0) {
		memcpy(out.f, q1.f, sizeof(quat_t));
		return out;
	} else if (t >= 1.0) {
		memcpy(out.f, q2.f, sizeof(quat_t));
		return out;
	}
	// Compute the cosine of the angle between the quaternions
	float cosOmega = quat_dotProduct(q1, q2);
	// If the dot product is <0 then we use -q2 otherwise q2
	quat_t q2Prepared;
	if(cosOmega < 0.0f) {
		vec4_t multiplied = vec4_scalarMul(*(vec4_t *)&q2, -1.0f);
		q2Prepared = *(quat_t *)&multiplied;
		cosOmega *= -1.0f;
	} else {
		q2Prepared = q2;
	}
	// Verify that the quaternions are in fact unit quaternions
	assert(cosOmega <= 1.0f+EPSILON);

	float k1, k2;
	// If the angle is tiny enough just use linear interpolation
	if(cosOmega > 0.9999f) {
		k1 = 1.0f - t;
		k2 = t;
	} else {
		float sinOmega = sqrtf(1.0f - powf(cosOmega, 2));
		// Calculate the actual angle
		float omega = atan2f(cosOmega, sinOmega);

		float sinOmegaInverse = 1.0f / sinOmega;
		k1 = sin((1.0f - t) * omega) * sinOmegaInverse;
		k2 = sin(t * omega) * sinOmegaInverse;
	}
	out.f[0] = (k1 * q1.f[0]) + (k2 * q2Prepared.x);
	out.f[1] = (k1 * q1.f[1]) + (k2 * q2Prepared.y);
	out.f[2] = (k1 * q1.f[2]) + (k2 * q2Prepared.z);
	out.f[3] = (k1 * q1.f[3]) + (k2 * q2Prepared.w);

	return out;
}


#pragma mark - ~ Affine transformations
static mat4_t mat4_make_translation(float x, float y, float z) {
	mat4_t out;
	memcpy(out.f, kMat4_identity.f, sizeof(mat4_t));
	out.f[12] = x;
	out.f[13] = y;
	out.f[14] = z;

	return out;
}

static __inline__ void mat4_translate(mat4_t mat, float x, float y, float z) {
	mat4_t translation, temp;
	memcpy(temp.f, mat.f, sizeof(mat4_t));
	translation = mat4_make_translation(x, y, z);
	temp = mat4_mul(translation, mat);
	mat.f[12] += x;
	mat.f[13] += y;
	mat.f[14] += z;
}

static mat4_t mat4_make_rotation(float angle, float x, float y, float z) {
	return quat_to_ortho(quat_makef(x, y, z, angle));
}

static mat4_t mat4_rotate(mat4_t mat, float angle, float x, float y, float z) {
	mat4_t rotation, temp;
	memcpy(temp.f, mat.f, sizeof(mat4_t));
	rotation = mat4_make_rotation(angle, x, y, z);
	return mat4_mul(rotation, temp);
}

static mat4_t mat4_make_scale(float x, float y, float z) {
	mat4_t out;
	memcpy(out.f, kMat4_identity.f, sizeof(mat4_t));
	out.f[0]  = x;
	out.f[5]  = y;
	out.f[10] = z;

	return out;
}
static __inline__ mat4_t mat4_scale(mat4_t mat, float x, float y, float z) {
	mat4_t temp, scale;
	memcpy(temp.f, mat.f, sizeof(mat4_t));
	scale = mat4_make_scale(x, y, z);
	return mat4_mul(scale, temp);
}

#pragma mark - ~ Utilities
// Generates a perspective viewing matrix
static mat4_t mat4_perspective(float fovy, float aspect, float zNear, float zFar)
{
	mat4_t out;
	float f = 1.0f / tanf(fovy/2.0f);

	out.f[0] = f / aspect;
	out.f[1] = 0.0f;
	out.f[2] = 0.0f;
	out.f[3] = 0.0f;

	out.f[4] = 0.0f;
	out.f[5] = f;
	out.f[6] = 0.0f;
	out.f[7] = 0.0f;

	out.f[8] = 0.0f;
	out.f[9] = 0.0f;
	out.f[10] = (zFar+zNear) / (zNear-zFar);
	out.f[11] = -1.0f;

	out.f[12] = 0.0f;
	out.f[13] = 0.0f;
	out.f[14] = 2.0f * zFar * zNear /	(zNear-zFar);
	out.f[15] = 0.0f;

	return out;
}

// Generates an orthogonal viewing matrix
static mat4_t mat4_ortho(float left, float right, float bottom, float top, float near, float far)
{
	mat4_t out;

	float r_l = right - left;
	float t_b = top - bottom;
	float f_n = far - near;
	float tx = - (right + left) / (right - left);
	float ty = - (top + bottom) / (top - bottom);
	float tz = - (far + near) / (far - near);

	out.f[0] = 2.0f / r_l;
	out.f[1] = 0.0f;
	out.f[2] = 0.0f;
	out.f[3] = 0.0f;

	out.f[4] = 0.0f;
	out.f[5] = 2.0f / t_b;
	out.f[6] = 0.0f;
	out.f[7] = 0.0f;

	out.f[8] = 0.0f;
	out.f[9] = 0.0f;
	out.f[10] = -2.0f / f_n;
	out.f[11] = 0.0f;

	out.f[12] = tx;
	out.f[13] = ty;
	out.f[14] = tz;
	out.f[15] = 1.0f;

	return out;
}


static void printVec2(vec2_t vec) {
	printf("Vec2: [%.2f, %.2f]\n", vec.f[0], vec.f[1]);
}
static void printVec3(vec3_t vec) {
	printf("Vec3: [%.2f, %.2f, %.2f]\n", vec.f[0], vec.f[1], vec.f[2]);
}
static void printVec4(vec4_t vec) {
	printf("Vec4: [%.2f, %.2f, %.2f, %.2f]\n", vec.f[0], vec.f[1], vec.f[2], vec.f[3]);
}
static void printMat4(mat4_t mat) {
	printf("Mat4: [%.2f, %.2f, %.2f, %.2f]\n", mat.f[0], mat.f[1], mat.f[2], mat.f[3]);
	printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat.f[4], mat.f[5], mat.f[6], mat.f[7]);
	printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat.f[8], mat.f[9], mat.f[10], mat.f[11]);
	printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat.f[12], mat.f[13], mat.f[14], mat.f[15]);
}
static void printQuat(quat_t quat) {
	printf("Quat: [%.2f, %.2f, %.2f, %.2f]\n", quat.f[0], quat.f[1], quat.f[2], quat.f[3]);
}

static bool floatArr_equals(const float *a1, const float *a2, unsigned int len) {
	for(int i = 0; i < len; ++i) {
		if(a1[i] != a2[i])
			return false;
	}
	return true;
}
static bool vec2_equals(const vec2_t v1, const vec2_t v2) {
	return floatArr_equals(v1.f, v2.f, 2);
}
static bool vec3_equals(const vec3_t v1, const vec3_t v2) {
	return floatArr_equals(v1.f, v2.f, 3);
}
static bool vec4_equals(const vec4_t v1, const vec4_t v2) {
	return floatArr_equals(v1.f, v2.f, 4);
}
static bool mat4_equals(const mat4_t m1, const mat4_t m2) {
	return floatArr_equals(m1.f, m2.f, 16);
}
static bool quat_equals(const quat_t q1, const quat_t q2) {
	return floatArr_equals(q1.f, q2.f, 4);
}

#ifdef __cplusplus
}
#endif
#endif
