#ifndef GL_MATH_UTILS_H
#define GL_MATH_UTILS_H

#include "GLMathTypes.h"
#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Prototypes

// Utilities
static mat4_t mat4_perspective(float fov_radians, float aspect, float zNear, float zFar);
// Generates an orthogonal viewing matrix
static mat4_t mat4_ortho(float left, float right, float bottom, float top, float near, float far);
// Generates a lookat camera viewing matrix
static __inline__ mat4_t mat4_lookat(float eyeX, float eyeY, float eyeZ,
                                     float centerX, float centerY, float centerZ,
                                     float upX, float upY, float upZ);
static void printVec2(vec2_t vec);
static void printVec3(vec3_t vec);
static void printVec4(vec4_t vec);
static void printMat3(mat3_t mat);
static void printMat4(mat4_t mat);
static void printQuat(quat_t quat);

static bool floatArr_equals(const float *a1, const float *a2, unsigned int len);
static bool vec2_equals(const vec2_t v1, const vec2_t v2);
static bool vec3_equals(const vec3_t v1, const vec3_t v2);
static bool vec4_equals(const vec4_t v1, const vec4_t v2);
static bool mat4_equals(const mat4_t m1, const mat4_t m2);
static bool quat_equals(const quat_t q1, const quat_t q2);

#pragma mark Implementations

// Generates a perspective viewing matrix
static mat4_t mat4_perspective(float fovy, float aspect, float zNear, float zFar)
{
	mat4_t out;
	float cotan = 1.0f / tanf(fovy/2.0f);

	return (mat4_t){ cotan/aspect, 0.0f,  0.0f,                               0.0f,
	                 0.0f,         cotan, 0.0f,                               0.0f,
	                 0.0f,         0.0f,  (zFar+zNear) / (zNear-zFar),       -1.0f,
	                 0.0f,         0.0f,  2.0f * zFar * zNear / (zNear-zFar), 0.0f };

	return out;
}

// Generates an orthogonal viewing matrix
static mat4_t mat4_ortho(float left, float right, float bottom, float top, float near, float far)
{
	float ral = right + left;
	float rsl = right - left;
	float tsb = top - bottom;
	float tab = top + bottom;
	float fan = far + near;
	float fsn = far - near;

	return (mat4_t) { 2.0f / rsl, 0.0f,       0.0f,        0.0f,
                     0.0f,        2.0f / tsb, 0.0f,        0.0f,
                     0.0f,        0.0f,       -2.0f / fsn, 0.0f,
                     -ral / rsl,  -tab / tsb, -fan / fsn,  1.0f };
}

// Generates lookat viewing matrix
static __inline__ mat4_t mat4_lookat(float eyeX, float eyeY, float eyeZ,
                                     float centerX, float centerY, float centerZ,
                                     float upX, float upY, float upZ)
{
	vec3_t ev = { eyeX, eyeY, eyeZ };
	vec3_t cv = { centerX, centerY, centerZ };
	vec3_t uv = { upX, upY, upZ };
	vec3_t n = vec3_normalize(vec3_add(ev, vec3_negate(cv)));
	vec3_t u = vec3_normalize(vec3_cross(uv, n));
	vec3_t v = vec3_cross(n, u);

	return (mat4_t){ u.f[0], v.f[0], n.f[0], 0.0f,
	                 u.f[1], v.f[1], n.f[1], 0.0f,
	                 u.f[2], v.f[2], n.f[2], 0.0f,
	                 vec3_dot(vec3_negate(u), ev),
	                 vec3_dot(vec3_negate(v), ev),
	                 vec3_dot(vec3_negate(n), ev),
	                 1.0f };
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
static void printMat3(mat3_t mat) {
	printf("Mat3: [%.2f, %.2f, %.2f]\n", mat.m00, mat.m01, mat.m02);
	printf("      [%.2f, %.2f, %.2f]\n", mat.m10, mat.m11, mat.m12);
	printf("      [%.2f, %.2f, %.2f]\n", mat.m20, mat.m21, mat.m22);
}
static void printMat4(mat4_t mat) {
	printf("Mat4: [%.2f, %.2f, %.2f, %.2f]\n", mat.m00, mat.m01, mat.m02, mat.m03);
	printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat.m10, mat.m11, mat.m12, mat.m13);
	printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat.m20, mat.m21, mat.m22, mat.m23);
	printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat.m30, mat.m31, mat.m32, mat.m33);
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
