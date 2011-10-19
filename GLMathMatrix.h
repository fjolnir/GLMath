#ifndef GL_MATH_MATRIX_H
#define GL_MATH_MATRIX_H

#include "GLMathTypes.h"
#import <Accelerate/Accelerate.h>
#import <string.h>
#import <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Prototypes

// Matrix math functions
static __inline__ mat3_t mat3_mul(const mat3_t m1, const mat3_t m2);
static __inline__ vec3_t vec3_mul_m(const vec3_t v, const mat3_t m);
static __inline__ mat3_t mat3_inverse(const mat3_t m);
static __inline__ mat3_t mat3_transpose(const mat3_t m);

static __inline__ mat4_t mat4_mul(const mat4_t m1, const mat4_t m2);
static __inline__ vec4_t vec4_mul_mat4(const vec4_t v, const mat4_t m);
static __inline__ mat4_t mat4_inverse(const mat4_t m);
static __inline__ mat4_t mat4_transpose(const mat4_t m);
static __inline__ mat3_t mat4_extract_mat3(const mat4_t m);

#pragma mark Implementations

static __inline__ mat3_t mat3_mul(const mat3_t m1, const mat3_t m2) {
	mat3_t out;
	vDSP_mmul((float*)m1.f, 1, (float*)m2.f, 1, out.f, 1, 3, 3, 3);
	return out;
}
static __inline__ vec3_t vec3_mul_mat3(const vec3_t v, const mat3_t m) {
	vec3_t out;
	vDSP_mmul((float*)v.f, 1, (float*)m.f, 1, out.f, 1, 1, 3, 3);
	return out;
}
static __inline__ mat3_t mat3_inverse(const mat3_t m) {
	mat3_t out;
	__CLPK_integer colsA, rowsA, colsB, rowsB, status;
	colsA = rowsA = colsB = rowsB = 3;
	__CLPK_integer pivotIndices[colsA];
	memcpy(out.f, kMat3_identity.f, sizeof(mat3_t));
	sgesv_(&colsA, &colsB, (float*)m.f, &rowsA, pivotIndices, out.f, &rowsB, &status);
	if(status != 0) {
		printf("Could not invert 3x3 matrix!\n");
		out = kMat3_zero;
	}
	return out;
}
static __inline__ mat3_t mat3_transpose(const mat3_t m) {
	mat3_t out;
	vDSP_mtrans((float*)m.f, 1, out.f, 1, 3, 3);
	return out;
}

static __inline__ mat3_t mat4_extract_mat3(const mat4_t m) {
	mat3_t out = { m.m00, m.m01, m.m02,
	               m.m10, m.m11, m.m12,
	               m.m20, m.m21, m.m22 };
	return out;
}

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
		printf("Could not invert 4x4 matrix!\n");
		out = kMat4_zero;
	}
	return out;
}
static __inline__ mat4_t mat4_transpose(const mat4_t m) {
	mat4_t out;
	vDSP_mtrans((float*)m.f, 1, out.f, 1, 4, 4);
	return out;
}

#ifdef __cplusplus
}
#endif
#endif
