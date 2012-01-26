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

#include <GLMath/GLMath.h>

#if !defined(GLMath_GLMathExports_h) && defined(GLM_EXPORT_SYMBOLS)
#define GLMath_GLMathExports_h

#pragma mark - Vectors

vec2_t _vec2_create(float x, float y) __asm("_vec2_create");
vec2_t _vec2_add(const vec2_t v1, const vec2_t v2) __asm("_vec2_add");
vec2_t _vec2_sub(const vec2_t v1, const vec2_t v2) __asm("_vec2_sub");
vec2_t _vec2_mul(const vec2_t v1, const vec2_t v2) __asm("_vec2_mul");
vec2_t _vec2_div(const vec2_t v1, const vec2_t v2) __asm("_vec2_div");
float _vec2_dot(const vec2_t v1, const vec2_t v2) __asm("_vec2_dot");
float _vec2_magSquared(const vec2_t v) __asm("_vec2_magSquared");
float _vec2_mag(const vec2_t v) __asm("_vec2_mag");
vec2_t _vec2_normalize(const vec2_t v) __asm("_vec2_normalize");
float _vec2_dist(const vec2_t v1, const vec2_t v2) __asm("_vec2_dist");
vec2_t _vec2_scalarMul(const vec2_t v, float s) __asm("_vec2_scalarMul");
vec2_t _vec2_scalarDiv(const vec2_t v, float s) __asm("_vec2_scalarDiv");
vec2_t _vec2_negate(const vec2_t v) __asm("_vec2_negate");
vec2_t _vec2_floor(vec2_t v) __asm("_vec2_floor");

vec3_t _vec3_create(float x, float y, float z) __asm("_vec3_create");
vec3_t _vec3_add(const vec3_t v1, const vec3_t v2) __asm("_vec3_add");
vec3_t _vec3_sub(const vec3_t v1, const vec3_t v2) __asm("_vec3_sub");
vec3_t _vec3_mul(const vec3_t v1, const vec3_t v2) __asm("_vec3_mul");
vec3_t _vec3_div(const vec3_t v1, const vec3_t v2) __asm("_vec3_div");
float _vec3_dot(const vec3_t v1, const vec3_t v2) __asm("_vec3_dot");
float _vec3_magSquared(const vec3_t v) __asm("_vec3_magSquared");
float _vec3_mag(const vec3_t v) __asm("_vec3_mag");
vec3_t _vec3_normalize(const vec3_t v) __asm("_vec3_normalize");
float _vec3_dist(const vec3_t v1, const vec3_t v2) __asm("_vec3_dist");
vec3_t _vec3_scalarMul(const vec3_t v, float s) __asm("_vec3_scalarMul");
vec3_t _vec3_scalarDiv(const vec3_t v, float s) __asm("_vec3_scalarDiv");
vec3_t _vec3_cross(const vec3_t v1, const vec3_t v2) __asm("_vec3_cross");
vec3_t _vec3_negate(const vec3_t v) __asm("_vec3_negate");
vec3_t _vec3_floor(vec3_t v) __asm("_vec3_floor");

vec4_t _vec4_create(float x, float y, float z, float w) __asm("_vec4_create");
vec4_t _vec4_add(const vec4_t v1, const vec4_t v2) __asm("_vec4_add");
vec4_t _vec4_sub(const vec4_t v1, const vec4_t v2) __asm("_vec4_sub");
vec4_t _vec4_mul(const vec4_t v1, const vec4_t v2) __asm("_vec4_mul");
vec4_t _vec4_div(const vec4_t v1, const vec4_t v2) __asm("_vec4_div");
float _vec4_dot(const vec4_t v1, const vec4_t v2) __asm("_vec4_dot");
float _vec4_magSquared(const vec4_t v) __asm("_vec4_magSquared");
float _vec4_mag(const vec4_t v) __asm("_vec4_mag");
float _vec4_dist(const vec4_t v1, const vec4_t v2) __asm("_vec4_dist");
vec4_t _vec4_scalarMul(const vec4_t v, float s) __asm("_vec4_scalarMul");
vec4_t _vec4_scalarDiv(const vec4_t v, float s) __asm("_vec4_scalarDiv");
vec4_t _vec4_cross(const vec4_t v1, const vec4_t v2) __asm("_vec4_cross");
vec4_t _vec4_negate(const vec4_t v) __asm("_vec4_negate");
vec4_t _vec4_floor(vec4_t v) __asm("_vec4_floor");


#pragma mark - Matrices

mat3_t _mat3_mul(const mat3_t m1, const mat3_t m2) __asm("_mat3_mul");
vec3_t _vec3_mul_mat3(const vec3_t v, const mat3_t m) __asm("_vec3_mul_mat3");
mat3_t _mat3_inverse(const mat3_t m, bool *success_out) __asm("_mat3_inverse");
mat3_t _mat3_transpose(const mat3_t m) __asm("_mat3_transpose");
float _mat3_det(const mat3_t m) __asm("_mat3_det");

mat4_t _mat4_mul(const mat4_t m1, const mat4_t m2) __asm("_mat4_mul");
vec3_t _vec3_mul_mat4(const vec3_t v, const mat4_t m, bool isPoint) __asm("_vec3_mul_mat4");
vec4_t _vec4_mul_mat4(const vec4_t v, const mat4_t m) __asm("_vec4_mul_mat4");
mat4_t _mat4_inverse(const mat4_t m, bool *success_out) __asm("_mat4_inverse");
mat4_t _mat4_transpose(const mat4_t m) __asm("_mat4_transpose");
mat3_t _mat4_extract_mat3(const mat4_t m) __asm("_mat4_extract_mat3");
float _mat4_det(mat4_t m) __asm("_mat4_det");

#pragma mark - Quaternions

quat_t _quat_createf(float x, float y, float z, float angle) __asm("_quat_createf");
quat_t _quat_createv(vec3_t axis, float angle) __asm("_quat_createv");
mat4_t _quat_to_mat4(const quat_t q) __asm("_quat_to_mat4");
quat_t _mat4_to_quat(const mat4_t m) __asm("_mat4_to_quat");
mat4_t _quat_to_ortho(const quat_t q) __asm("_quat_to_ortho");
quat_t _ortho_to_quat(const mat4_t m) __asm("_ortho_to_quat");
float _quat_magSquared(const quat_t q) __asm("_quat_magSquared");
float _quat_mag(const quat_t q) __asm("_quat_mag");
quat_t _quat_computeW(quat_t q) __asm("_quat_computeW");
quat_t _quat_normalize(quat_t q) __asm("_quat_normalize");
quat_t _quat_multQuat(const quat_t qA, const quat_t qB) __asm("_quat_multQuat");
vec4_t _quat_rotatePoint(const quat_t q, const vec4_t v) __asm("_quat_rotatePoint");
quat_t _quat_inverse(const quat_t q) __asm("_quat_inverse");
float _quat_dotProduct(const quat_t qA, const quat_t qB) __asm("_quat_dotProduct");
quat_t _quat_slerp(const quat_t qA, const quat_t qB, float t) __asm("_quat_slerp");


#pragma mark - Bezier curves

bezier_t _bezier_create(vec3_t c1, vec3_t c2, vec3_t c3, vec3_t c4) __asm("_bezier_create");
vec3_t _bezier_getPoint(bezier_t curve, float t) __asm("_bezier_getPoint");
float _bezier_getCoordForAxis(bezier_t curve, float t, bezierAxis_t axis) __asm("_bezier_getCoordForAxis");
vec3_t _bezier_firstDerivative(bezier_t curve, float t) __asm("_bezier_firstDerivative");
vec2_t _bezier_firstDerivativeRoots(bezier_t curve, bezierAxis_t axis) __asm("_bezier_firstDerivativeRoots");
void _bezier_extremes(bezier_t curve, vec3_t *outMinimums, vec3_t *outMaximums) __asm("_bezier_extremes");
vec3_t _bezier_getPointWithOffset(bezier_t curve, float t, vec3_t offset) __asm("_bezier_getPointWithOffset");
void _bezier_getLineSegments(bezier_t curve, int count, vec3_t *outPoints, float *outLengths, float *outDeltas, float *outTotalLength) __asm("_bezier_getLineSegments");
vec3_t _bezier_getPointUsingLineSegments(float t, int count, vec3_t *points, float *lengths, float *deltas, float totalLength) __asm("_bezier_getPointUsingLineSegments");

#pragma mark - Rectangles

rect_t _rect_createWithSize(vec2_t origin, vec2_t size) __asm("_rect_createWithSize");
rect_t _rect_createWithCorners(float left, float bottom, float right, float top) __asm("_rect_createWithCorners");
float _rect_maxX(const rect_t rect) __asm("_rect_maxX");
float _rect_minX(const rect_t rect) __asm("_rect_minX");
float _rect_maxY(const rect_t rect) __asm("_rect_maxY");
float _rect_minY(const rect_t rect) __asm("_rect_minY");
bool _rect_intersects(const rect_t r1, const rect_t r2) __asm("_rect_intersects");
bool _rect_containsRect(const rect_t r1, const rect_t r2) __asm("_rect_containsRect");
bool _rect_containsPoint(const rect_t rect, const vec2_t point) __asm("_rect_containsPoint");
rect_t _rect_merge(const rect_t r1, const rect_t r2) __asm("_rect_merge");
rect_t _rect_scale(const rect_t rect, const vec2_t scale) __asm("_rect_scale");
float _rect_area(const rect_t rect) __asm("_rect_area");
bool _rect_intersectsLineSeg(const rect_t rect, const vec2_t a, const vec2_t b) __asm("_rect_intersectsLineSeg");
rect_t _rect_translate(const rect_t aRect, const vec2_t aTranslationVector) __asm("_rect_translate");

#pragma mark - Transforms

mat4_t _mat4_create_translation(float x, float y, float z) __asm("_mat4_create_translation");
mat4_t _mat4_translate(mat4_t mat, float x, float y, float z) __asm("_mat4_translate");
mat4_t _mat4_create_rotation(float angle, float x, float y, float z) __asm("_mat4_create_rotation");
mat4_t _mat4_rotate(mat4_t mat, float angle, float x, float y, float z) __asm("_mat4_rotate");
mat4_t _mat4_create_scale(float x, float y, float z) __asm("_mat4_create_scale");
mat4_t _mat4_scale(mat4_t mat, float x, float y, float z) __asm("_mat4_scale");

#pragma mark - Matrix stack

matrix_stack_t *_matrix_stack_create(unsigned int initialCapacity) __asm("_matrix_stack_create");
void _matrix_stack_destroy(matrix_stack_t *stack) __asm("_matrix_stack_destroy");
void _matrix_stack_push_item(matrix_stack_t *stack, mat4_t item) __asm("_matrix_stack_push_item");
void _matrix_stack_push(matrix_stack_t *stack) __asm("_matrix_stack_push");
void _matrix_stack_pop(matrix_stack_t *stack) __asm("_matrix_stack_pop");
mat4_t _matrix_stack_get_mat4(matrix_stack_t *stack) __asm("_matrix_stack_get_mat4");
mat3_t _matrix_stack_get_mat3(matrix_stack_t *stack) __asm("_matrix_stack_get_mat3");
void _matrix_stack_translate(matrix_stack_t *stack, float x, float y, float z) __asm("_matrix_stack_translate");
void _matrix_stack_rotate(matrix_stack_t *stack, float angle, float x, float y, float z) __asm("_matrix_stack_rotate");
void _matrix_stack_scale(matrix_stack_t *stack, float x, float y, float z) __asm("_matrix_stack_scale");

#pragma mark - Utilities

bool _vec2_equals(const vec2_t v1, const vec2_t v2) __asm("_vec2_equals");
bool _vec3_equals(const vec3_t v1, const vec3_t v2) __asm("_vec3_equals");
bool _vec4_equals(const vec4_t v1, const vec4_t v2) __asm("_vec4_equals");
bool _mat4_equals(const mat4_t m1, const mat4_t m2) __asm("_mat4_equals");
bool _quat_equals(const quat_t q1, const quat_t q2) __asm("_quat_equals");

#endif
