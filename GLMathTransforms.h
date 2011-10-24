#ifndef GL_MATH_TRANSFORMS_H_
#define GL_MATH_TRANSFORMS_H_

#include "GLMathTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Prototypes

static __inline__ mat4_t mat4_make_translation(float x, float y, float z);
static __inline__ mat4_t mat4_translate(mat4_t mat, float x, float y, float z);
static __inline__ mat4_t mat4_make_rotation(float angle, float x, float y, float z);
static __inline__ mat4_t mat4_rotate(mat4_t mat, float angle, float x, float y, float z);
static __inline__ mat4_t mat4_make_scale(float x, float y, float z);
static __inline__ mat4_t mat4_scale(mat4_t mat, float x, float y, float z);

#pragma mark - Implementations

static mat4_t mat4_make_translation(float x, float y, float z) {
	mat4_t out = kMat4_identity;
	out.m30 = x;
	out.m31 = y;
	out.m32 = z;

	return out;
}

static __inline__ mat4_t mat4_translate(mat4_t mat, float x, float y, float z) {
	return mat4_mul(mat, mat4_make_translation(x, y, z));
}

static mat4_t mat4_make_rotation(float angle, float x, float y, float z) {
	return quat_to_ortho(quat_makef(x, y, z, angle));
}

static mat4_t mat4_rotate(mat4_t mat, float angle, float x, float y, float z) {
	return mat4_mul(mat, mat4_make_rotation(angle, x, y, z));
}

static mat4_t mat4_make_scale(float x, float y, float z) {
	mat4_t out = kMat4_identity;
	out.m00 = x;
	out.m11 = y;
	out.m22 = z;

	return out;
}
static __inline__ mat4_t mat4_scale(mat4_t mat, float x, float y, float z) {
	return mat4_mul(mat, mat4_make_scale(x, y, z));
}

#ifdef __cplusplus
}
#endif
#endif
