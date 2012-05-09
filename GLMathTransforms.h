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

#ifndef GL_MATH_TRANSFORMS_H_
#define GL_MATH_TRANSFORMS_H_

#include <GLMath/GLMathTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Prototypes

static __inline__ mat4_t mat4_create_translation(GLMFloat x, GLMFloat y, GLMFloat z);
static __inline__ mat4_t mat4_translate(mat4_t mat, GLMFloat x, GLMFloat y, GLMFloat z);
static __inline__ mat4_t mat4_create_rotation(GLMFloat angle, GLMFloat x, GLMFloat y, GLMFloat z);
static __inline__ mat4_t mat4_rotate(mat4_t mat, GLMFloat angle, GLMFloat x, GLMFloat y, GLMFloat z);
static __inline__ mat4_t mat4_create_scale(GLMFloat x, GLMFloat y, GLMFloat z);
static __inline__ mat4_t mat4_scale(mat4_t mat, GLMFloat x, GLMFloat y, GLMFloat z);

#pragma mark - Implementations

static __inline__ mat4_t mat4_create_translation(GLMFloat x, GLMFloat y, GLMFloat z) {
	mat4_t out = GLMMat4_identity;
	out.m30 = x;
	out.m31 = y;
	out.m32 = z;

	return out;
}

static __inline__ mat4_t mat4_translate(mat4_t mat, GLMFloat x, GLMFloat y, GLMFloat z) {
	return mat4_mul(mat, mat4_create_translation(x, y, z));
}

static __inline__ mat4_t mat4_create_rotation(GLMFloat angle, GLMFloat x, GLMFloat y, GLMFloat z) {
	return quat_to_ortho(quat_createf(x, y, z, angle));
}

static __inline__ mat4_t mat4_rotate(mat4_t mat, GLMFloat angle, GLMFloat x, GLMFloat y, GLMFloat z) {
	return mat4_mul(mat, mat4_create_rotation(angle, x, y, z));
}

static __inline__ mat4_t mat4_create_scale(GLMFloat x, GLMFloat y, GLMFloat z) {
	mat4_t out = GLMMat4_identity;
	out.m00 = x;
	out.m11 = y;
	out.m22 = z;

	return out;
}

static __inline__ mat4_t mat4_scale(mat4_t mat, GLMFloat x, GLMFloat y, GLMFloat z) {
	return mat4_mul(mat, mat4_create_scale(x, y, z));
}

#ifdef __cplusplus
}
#endif
#endif
