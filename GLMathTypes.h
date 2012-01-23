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

#ifndef GL_MATH_TYPES_H
#define GL_MATH_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Types

// Vectors
union _vec2_t {
	float f[2];
	struct { float x; float y; };
	struct { float w; float h; };
	struct { float u; float v; };

};
typedef union _vec2_t vec2_t;

union _vec3_t {
	float f[3];
	struct { float x; float y; float z; };
	struct { float r; float g; float b; };
	struct { vec2_t xy; float andY; };
};
typedef union _vec3_t vec3_t;

union _vec4_t {
	float f[4];
	struct { float x; float y; float z; float w; };
	struct { float r; float g; float b; float a; };
	struct { vec3_t xyz; float andW; };
};
typedef union _vec4_t vec4_t;

// Matrices
union _mat3_t {
	float f[9];
	struct {
		float m00, m01, m02;
		float m10, m11, m12;
		float m20, m21, m22;
	};
};
typedef union _mat3_t mat3_t;

union _mat4_t {
	float f[16];
	struct {
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;
	};
};
typedef union _mat4_t mat4_t;

// Quaternions
union _quat_t {
	float f[4];
	struct { float x; float y; float z; float w; };
	struct { vec3_t vec; float scalar; };
};
typedef union _quat_t quat_t;

// Rectangles (Origin: bottom left)
union _rect_t {
	float f[4];
	struct { vec2_t o; vec2_t s; };
	struct { vec2_t origin; vec2_t size; };
	struct { float x; float y; float w; float h; };
};
typedef union _rect_t rect_t;

// Matrix stacks
struct _matrix_stack_t {
	mat4_t *items;
	unsigned int capacity;
	unsigned int count;
};
typedef struct _matrix_stack_t matrix_stack_t;

// Bezier curves
union _bezier_t {
	float f[12];
	vec3_t controlPoints[4];
	vec3_t cp[4];
};
typedef union _bezier_t bezier_t;

enum _bezierAxis {
	kBezierAxisX = 0,
	kBezierAxisY,
	kBezierAxisZ
};
typedef enum _bezierAxis bezierAxis_t;

#pragma mark - Constants

// Zero vectors
extern const vec2_t kVec2_zero;
extern const vec3_t kVec3_zero;
extern const vec4_t kVec4_zero;

extern const mat3_t kMat3_identity;
extern const mat3_t kMat3_zero;
extern const mat4_t kMat4_identity;
extern const mat4_t kMat4_zero;

#ifdef __cplusplus
}
#endif
#endif
