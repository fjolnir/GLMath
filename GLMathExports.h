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

// This file simply wraps the static function myFunc as _myFunc so that GLMath can be used
// with things like FFI.
// This file is only used if you define GLM_EXPORT_SYMBOLS

#include "GLMath.h"

#if !defined(GLMath_GLMathExports_h) && defined(GLM_EXPORT_SYMBOLS)
#define GLMath_GLMathExports_h

#pragma mark - Vectors

vec2_t _vec2_create(float x, float y);
vec2_t _vec2_add(const vec2_t v1, const vec2_t v2);
vec2_t _vec2_sub(const vec2_t v1, const vec2_t v2);
vec2_t _vec2_mul(const vec2_t v1, const vec2_t v2);
vec2_t _vec2_div(const vec2_t v1, const vec2_t v2);
float _vec2_dot(const vec2_t v1, const vec2_t v2);
float _vec2_magSquared(const vec2_t v);
float _vec2_mag(const vec2_t v);
vec2_t _vec2_normalize(const vec2_t v);
float _vec2_dist(const vec2_t v1, const vec2_t v2);
vec2_t _vec2_scalarMul(const vec2_t v, float s);
vec2_t _vec2_scalarDiv(const vec2_t v, float s);
vec2_t _vec2_negate(const vec2_t v);
vec2_t _vec2_floor(vec2_t v);

vec3_t _vec3_create(float x, float y, float z);
vec3_t _vec3_add(const vec3_t v1, const vec3_t v2);
vec3_t _vec3_sub(const vec3_t v1, const vec3_t v2);
vec3_t _vec3_mul(const vec3_t v1, const vec3_t v2);
vec3_t _vec3_div(const vec3_t v1, const vec3_t v2);
float _vec3_dot(const vec3_t v1, const vec3_t v2);
float _vec3_magSquared(const vec3_t v);
float _vec3_mag(const vec3_t v);
vec3_t _vec3_normalize(const vec3_t v);
float _vec3_dist(const vec3_t v1, const vec3_t v2);
vec3_t _vec3_scalarMul(const vec3_t v, float s);
vec3_t _vec3_scalarDiv(const vec3_t v, float s);
vec3_t _vec3_cross(const vec3_t v1, const vec3_t v2);
vec3_t _vec3_negate(const vec3_t v);
vec3_t _vec3_floor(vec3_t v);

vec4_t _vec4_create(float x, float y, float z, float w);
vec4_t _vec4_add(const vec4_t v1, const vec4_t v2);
vec4_t _vec4_sub(const vec4_t v1, const vec4_t v2);
vec4_t _vec4_mul(const vec4_t v1, const vec4_t v2);
vec4_t _vec4_div(const vec4_t v1, const vec4_t v2);
float _vec4_dot(const vec4_t v1, const vec4_t v2);
float _vec4_magSquared(const vec4_t v);
float _vec4_mag(const vec4_t v);
float _vec4_dist(const vec4_t v1, const vec4_t v2);
vec4_t _vec4_scalarMul(const vec4_t v, float s);
vec4_t _vec4_scalarDiv(const vec4_t v, float s);
vec4_t _vec4_cross(const vec4_t v1, const vec4_t v2);
vec4_t _vec4_negate(const vec4_t v);
vec4_t _vec4_floor(vec4_t v);


#pragma mark - Matrices

mat3_t _mat3_mul(const mat3_t m1, const mat3_t m2);
vec3_t _vec3_mul_mat3(const vec3_t v, const mat3_t m);
mat3_t _mat3_inverse(const mat3_t m, bool *success_out);
mat3_t _mat3_transpose(const mat3_t m);
float _mat3_det(const mat3_t m);

mat4_t _mat4_mul(const mat4_t m1, const mat4_t m2);
vec3_t _vec3_mul_mat4(const vec3_t v, const mat4_t m, bool isPoint);
vec4_t _vec4_mul_mat4(const vec4_t v, const mat4_t m);
mat4_t _mat4_inverse(const mat4_t m, bool *success_out);
mat4_t _mat4_transpose(const mat4_t m);
mat3_t _mat4_extract_mat3(const mat4_t m);
float _mat4_det(mat4_t m);

#pragma mark - Quaternions

quat_t _quat_createf(float x, float y, float z, float angle);
quat_t _quat_createv(vec3_t axis, float angle);
mat4_t _quat_to_mat4(const quat_t q);
quat_t _mat4_to_quat(const mat4_t m);
mat4_t _quat_to_ortho(const quat_t q);
quat_t _ortho_to_quat(const mat4_t m);
float _quat_magSquared(const quat_t q);
float _quat_mag(const quat_t q);
quat_t _quat_computeW(quat_t q);
quat_t _quat_normalize(quat_t q);
quat_t _quat_multQuat(const quat_t qA, const quat_t qB);
vec4_t _quat_rotatePoint(const quat_t q, const vec4_t v);
quat_t _quat_inverse(const quat_t q);
float _quat_dotProduct(const quat_t qA, const quat_t qB);
quat_t _quat_slerp(const quat_t qA, const quat_t qB, float t);


#pragma mark - Bezier curves

bezier_t _bezier_create(vec3_t c1, vec3_t c2, vec3_t c3, vec3_t c4);
vec3_t _bezier_getPoint(bezier_t curve, float t);
float _bezier_getCoordForAxis(bezier_t curve, float t, bezierAxis_t axis);
vec3_t _bezier_firstDerivative(bezier_t curve, float t);
vec2_t _bezier_firstDerivativeRoots(bezier_t curve, bezierAxis_t axis);
void _bezier_extremes(bezier_t curve, vec3_t *outMinimums, vec3_t *outMaximums);
vec3_t _bezier_getPointWithOffset(bezier_t curve, float t, vec3_t offset);
void _bezier_getLineSegments(bezier_t curve, int count, vec3_t *outPoints, float *outLengths, float *outDeltas, float *outTotalLength);
vec3_t _bezier_getPointUsingLineSegments(float t, int count, vec3_t *points, float *lengths, float *deltas, float totalLength);

#pragma mark - Rectangles

rect_t _rect_createWithSize(vec2_t origin, vec2_t size);
rect_t _rect_createWithCorners(float left, float bottom, float right, float top);
float _rect_maxX(const rect_t rect);
float _rect_minX(const rect_t rect);
float _rect_maxY(const rect_t rect);
float _rect_minY(const rect_t rect);
bool _rect_intersects(const rect_t r1, const rect_t r2);
bool _rect_containsRect(const rect_t r1, const rect_t r2);
bool _rect_containsPoint(const rect_t rect, const vec2_t point);
rect_t _rect_merge(const rect_t r1, const rect_t r2);
rect_t _rect_scale(const rect_t rect, const vec2_t scale);
float _rect_area(const rect_t rect);
bool _rect_intersectsLineSeg(const rect_t rect, const vec2_t a, const vec2_t b);
rect_t _rect_translate(const rect_t aRect, const vec2_t aTranslationVector);

#pragma mark - Transforms

mat4_t _mat4_create_translation(float x, float y, float z);
mat4_t _mat4_translate(mat4_t mat, float x, float y, float z);
mat4_t _mat4_create_rotation(float angle, float x, float y, float z);
mat4_t _mat4_rotate(mat4_t mat, float angle, float x, float y, float z);
mat4_t _mat4_create_scale(float x, float y, float z);
mat4_t _mat4_scale(mat4_t mat, float x, float y, float z);

#pragma mark - Matrix stack

matrix_stack_t *_matrix_stack_create(unsigned int initialCapacity);
void _matrix_stack_destroy(matrix_stack_t *stack);
void _matrix_stack_push_item(matrix_stack_t *stack, mat4_t item);
void _matrix_stack_push(matrix_stack_t *stack);
void _matrix_stack_pop(matrix_stack_t *stack);
mat4_t _matrix_stack_get_mat4(matrix_stack_t *stack);
mat3_t _matrix_stack_get_mat3(matrix_stack_t *stack);
void _matrix_stack_translate(matrix_stack_t *stack, float x, float y, float z);
void _matrix_stack_rotate(matrix_stack_t *stack, float angle, float x, float y, float z);
void _matrix_stack_scale(matrix_stack_t *stack, float x, float y, float z);

#pragma mark - Utilities

bool _vec2_equals(const vec2_t v1, const vec2_t v2);
bool _vec3_equals(const vec3_t v1, const vec3_t v2);
bool _vec4_equals(const vec4_t v1, const vec4_t v2);
bool _mat4_equals(const mat4_t m1, const mat4_t m2);
bool _quat_equals(const quat_t q1, const quat_t q2);
#endif
