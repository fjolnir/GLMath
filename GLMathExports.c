#include "GLMathExports.h"

#ifdef GLM_EXPORT_SYMBOLS

vec2_t _vec2_create(GLMFloat x, GLMFloat y) { return vec2_create(x, y); }
vec2_t _vec2_add(const vec2_t v1, const vec2_t v2) { return vec2_add(v1, v2); }
vec2_t _vec2_sub(const vec2_t v1, const vec2_t v2) { return vec2_sub(v1, v2); }
vec2_t _vec2_mul(const vec2_t v1, const vec2_t v2) { return vec2_mul(v1, v2); }
vec2_t _vec2_div(const vec2_t v1, const vec2_t v2) { return vec2_div(v1, v2); }
GLMFloat _vec2_dot(const vec2_t v1, const vec2_t v2) { return vec2_dot(v1, v2); }
GLMFloat _vec2_magSquared(const vec2_t v) { return vec2_magSquared(v); }
GLMFloat _vec2_mag(const vec2_t v) { return vec2_mag(v); }
vec2_t _vec2_normalize(const vec2_t v) { return vec2_normalize(v); }
GLMFloat _vec2_dist(const vec2_t v1, const vec2_t v2) { return vec2_dist(v1, v2); }
vec2_t _vec2_scalarMul(const vec2_t v, GLMFloat s) { return vec2_scalarMul(v,s); }
vec2_t _vec2_scalarDiv(const vec2_t v, GLMFloat s) { return vec2_scalarDiv(v, s); }
vec2_t _vec2_scalarAdd(const vec2_t v, GLMFloat s) { return vec2_scalarAdd(v, s); }
vec2_t _vec2_scalarSub(const vec2_t v, GLMFloat s) { return vec2_scalarSub(v, s); }
vec2_t _vec2_negate(const vec2_t v) { return vec2_negate(v); }
vec2_t _vec2_floor(vec2_t v) { return vec2_floor(v); }

vec3_t _vec3_create(GLMFloat x, GLMFloat y, GLMFloat z) { return vec3_create(x, y, z); }
vec3_t _vec3_add(const vec3_t v1, const vec3_t v2) { return vec3_add(v1, v2); }
vec3_t _vec3_sub(const vec3_t v1, const vec3_t v2) { return vec3_sub(v1, v2); }
vec3_t _vec3_mul(const vec3_t v1, const vec3_t v2) { return vec3_mul(v1, v2); }
vec3_t _vec3_div(const vec3_t v1, const vec3_t v2) { return vec3_div(v1, v2); }
GLMFloat _vec3_dot(const vec3_t v1, const vec3_t v2) { return vec3_dot(v1, v2); }
GLMFloat _vec3_magSquared(const vec3_t v) { return vec3_magSquared(v); }
GLMFloat _vec3_mag(const vec3_t v) { return vec3_mag(v); }
vec3_t _vec3_normalize(const vec3_t v) { return vec3_normalize(v); }
GLMFloat _vec3_dist(const vec3_t v1, const vec3_t v2) { return vec3_dist(v1, v2); }
vec3_t _vec3_scalarMul(const vec3_t v, GLMFloat s) { return vec3_scalarMul(v, s); }
vec3_t _vec3_scalarDiv(const vec3_t v, GLMFloat s) { return vec3_scalarDiv(v, s); }
vec3_t _vec3_scalarAdd(const vec3_t v, GLMFloat s) { return vec3_scalarAdd(v, s); }
vec3_t _vec3_scalarSub(const vec3_t v, GLMFloat s) { return vec3_scalarSub(v, s); }
vec3_t _vec3_cross(const vec3_t v1, const vec3_t v2) { return vec3_cross(v1, v2); }
vec3_t _vec3_negate(const vec3_t v) { return vec3_negate(v); }
vec3_t _vec3_floor(vec3_t v) { return vec3_floor(v); }

vec4_t _vec4_create(GLMFloat x, GLMFloat y, GLMFloat z, GLMFloat w) { return vec4_create(x, y, z, w); }
vec4_t _vec4_add(const vec4_t v1, const vec4_t v2) { return vec4_add(v1, v2); }
vec4_t _vec4_sub(const vec4_t v1, const vec4_t v2) { return vec4_sub(v1, v2); }
vec4_t _vec4_mul(const vec4_t v1, const vec4_t v2) { return vec4_mul(v1, v2); }
vec4_t _vec4_div(const vec4_t v1, const vec4_t v2) { return vec4_div(v1, v2); }
GLMFloat _vec4_dot(const vec4_t v1, const vec4_t v2) { return vec4_dot(v1, v2); }
GLMFloat _vec4_magSquared(const vec4_t v) { return vec4_magSquared(v); }
GLMFloat _vec4_mag(const vec4_t v) { return vec4_mag(v); }
GLMFloat _vec4_dist(const vec4_t v1, const vec4_t v2) { return vec4_dist(v1, v2); }
vec4_t _vec4_scalarMul(const vec4_t v, GLMFloat s) { return vec4_scalarMul(v, s); }
vec4_t _vec4_scalarDiv(const vec4_t v, GLMFloat s) { return vec4_scalarDiv(v, s); }
vec4_t _vec4_scalarAdd(const vec4_t v, GLMFloat s) { return vec4_scalarAdd(v, s); }
vec4_t _vec4_scalarSub(const vec4_t v, GLMFloat s) { return vec4_scalarSub(v, s); }
vec4_t _vec4_cross(const vec4_t v1, const vec4_t v2) { return vec4_cross(v1, v2); }
vec4_t _vec4_negate(const vec4_t v) { return vec4_negate(v); }
vec4_t _vec4_floor(vec4_t v) { return vec4_floor(v); }


#pragma mark - Matrices

mat3_t _mat3_mul(const mat3_t m1, const mat3_t m2) { return mat3_mul(m1, m2); }
vec3_t _vec3_mul_mat3(const vec3_t v, const mat3_t m) { return vec3_mul_mat3(v, m); }
mat3_t _mat3_inverse(const mat3_t m, bool *success_out) { return mat3_inverse(m, success_out); }
mat3_t _mat3_transpose(const mat3_t m) { return mat3_transpose(m); }
GLMFloat _mat3_det(const mat3_t m) { return mat3_det(m); }

mat4_t _mat4_mul(const mat4_t m1, const mat4_t m2) { return mat4_mul(m1, m2); }
vec3_t _vec3_mul_mat4(const vec3_t v, const mat4_t m, bool isPoint) { return vec3_mul_mat4(v, m, isPoint); }
vec4_t _vec4_mul_mat4(const vec4_t v, const mat4_t m) { return vec4_mul_mat4(v, m); }
mat4_t _mat4_inverse(const mat4_t m, bool *success_out) { return mat4_inverse(m, success_out); }
mat4_t _mat4_transpose(const mat4_t m) { return mat4_transpose(m); }
mat3_t _mat4_extract_mat3(const mat4_t m) { return mat4_extract_mat3(m); }
GLMFloat _mat4_det(mat4_t m) { return mat4_det(m); }

#pragma mark - Quaternions

quat_t _quat_createf(GLMFloat x, GLMFloat y, GLMFloat z, GLMFloat angle) { return quat_createf(x, y, z, angle); }
quat_t _quat_createv(vec3_t axis, GLMFloat angle) { return quat_createv(axis, angle); }
mat4_t _quat_to_mat4(const quat_t q) { return quat_to_mat4(q); }
quat_t _mat4_to_quat(const mat4_t m) { return mat4_to_quat(m); }
mat4_t _quat_to_ortho(const quat_t q) { return quat_to_ortho(q); }
quat_t _ortho_to_quat(const mat4_t m) { return ortho_to_quat(m); }
GLMFloat _quat_magSquared(const quat_t q) { return quat_magSquared(q); }
GLMFloat _quat_mag(const quat_t q) { return quat_mag(q); }
quat_t _quat_computeW(quat_t q) { return quat_computeW(q); }
quat_t _quat_normalize(quat_t q) { return quat_normalize(q); }
quat_t _quat_multQuat(const quat_t qA, const quat_t qB) { return quat_multQuat(qA, qB); }
vec4_t _quat_rotatePoint(const quat_t q, const vec4_t v) { return quat_rotatePoint(q, v); }
quat_t _quat_inverse(const quat_t q) { return quat_inverse(q); }
GLMFloat _quat_dotProduct(const quat_t qA, const quat_t qB) { return quat_dotProduct(qA, qB); }
quat_t _quat_slerp(const quat_t qA, const quat_t qB, GLMFloat t) { return quat_slerp(qA, qB, t); }


#pragma mark - Bezier curves

bezier_t _bezier_create(vec3_t c1, vec3_t c2, vec3_t c3, vec3_t c4) { return bezier_create(c1, c2, c3, c4); }
vec3_t _bezier_getPoint(bezier_t curve, GLMFloat t) { return bezier_getPoint(curve, t); }
GLMFloat _bezier_getCoordForAxis(bezier_t curve, GLMFloat t, bezierAxis_t axis) { return bezier_getCoordForAxis(curve, t, axis); }
vec3_t _bezier_firstDerivative(bezier_t curve, GLMFloat t) { return bezier_firstDerivative(curve, t); }
vec2_t _bezier_firstDerivativeRoots(bezier_t curve, bezierAxis_t axis) { return bezier_firstDerivativeRoots(curve, axis); }
void _bezier_extremes(bezier_t curve, vec3_t *outMinimums, vec3_t *outMaximums) { bezier_extremes(curve, outMinimums, outMaximums); }
vec3_t _bezier_getPointWithOffset(bezier_t curve, GLMFloat t, vec3_t offset) { return bezier_getPointWithOffset(curve, t, offset); }
void _bezier_getLineSegments(bezier_t curve, int count, vec3_t *outPoints, GLMFloat *outLengths, GLMFloat *outDeltas, GLMFloat *outTotalLength) { bezier_getLineSegments(curve, count, outPoints, outLengths, outDeltas, outTotalLength); }
vec3_t _bezier_getPointUsingLineSegments(GLMFloat t, int count, vec3_t *points, GLMFloat *lengths, GLMFloat *deltas, GLMFloat totalLength) { return bezier_getPointUsingLineSegments(t, count, points, lengths, deltas, totalLength); }

#pragma mark - Rectangles

rect_t _rect_createWithSize(vec2_t origin, vec2_t size) { return rect_createWithSize(origin, size); }
rect_t _rect_createWithCorners(GLMFloat left, GLMFloat bottom, GLMFloat right, GLMFloat top) { return rect_createWithCorners(left, bottom, right, top); }
GLMFloat _rect_maxX(const rect_t rect) { return rect_maxX(rect); }
GLMFloat _rect_minX(const rect_t rect) { return rect_minX(rect); }
GLMFloat _rect_maxY(const rect_t rect) { return rect_maxY(rect); }
GLMFloat _rect_minY(const rect_t rect) { return rect_minY(rect); }
bool _rect_intersects(const rect_t r1, const rect_t r2) { return rect_intersects(r1, r2); }
bool _rect_containsRect(const rect_t r1, const rect_t r2) { return rect_containsRect(r1, r2); }
bool _rect_containsPoint(const rect_t rect, const vec2_t point) { return rect_containsPoint(rect, point); }
rect_t _rect_merge(const rect_t r1, const rect_t r2) { return rect_merge(r1, r2); }
rect_t _rect_scale(const rect_t rect, const vec2_t scale) { return rect_scale(rect, scale); }
GLMFloat _rect_area(const rect_t rect) { return rect_area(rect); }
bool _rect_intersectsLineSeg(const rect_t rect, const vec2_t a, const vec2_t b) { return rect_intersectsLineSeg(rect, a, b); }
rect_t _rect_translate(const rect_t aRect, const vec2_t aTranslationVector) { return rect_translate(aRect, aTranslationVector); }

#pragma mark - Transforms

mat4_t _mat4_create_translation(GLMFloat x, GLMFloat y, GLMFloat z) { return mat4_create_translation(x, y, z); }
mat4_t _mat4_translate(mat4_t mat, GLMFloat x, GLMFloat y, GLMFloat z) { return mat4_translate(mat, x, y, z); }
mat4_t _mat4_create_rotation(GLMFloat angle, GLMFloat x, GLMFloat y, GLMFloat z) { return mat4_create_rotation(angle, x, y, z); }
mat4_t _mat4_rotate(mat4_t mat, GLMFloat angle, GLMFloat x, GLMFloat y, GLMFloat z) { return mat4_rotate(mat, angle, x, y, z); }
mat4_t _mat4_create_scale(GLMFloat x, GLMFloat y, GLMFloat z) { return mat4_create_scale(x, y, z); }
mat4_t _mat4_scale(mat4_t mat, GLMFloat x, GLMFloat y, GLMFloat z) { return mat4_scale(mat, x, y, z); }

#pragma mark - Matrix stack

matrix_stack_t *_matrix_stack_create(unsigned int initialCapacity) { return matrix_stack_create(initialCapacity); }
void _matrix_stack_destroy(matrix_stack_t *stack) { matrix_stack_destroy(stack); }
void _matrix_stack_push_item(matrix_stack_t *stack, mat4_t item) { matrix_stack_push_item(stack, item); }
void _matrix_stack_push(matrix_stack_t *stack) { matrix_stack_push(stack); }
void _matrix_stack_pop(matrix_stack_t *stack) { matrix_stack_pop(stack); }
mat4_t _matrix_stack_get_mat4(matrix_stack_t *stack) { return matrix_stack_get_mat4(stack); }
mat3_t _matrix_stack_get_mat3(matrix_stack_t *stack) { return matrix_stack_get_mat3(stack); }
void _matrix_stack_translate(matrix_stack_t *stack, GLMFloat x, GLMFloat y, GLMFloat z) { matrix_stack_translate(stack, x, y, z); }
void _matrix_stack_rotate(matrix_stack_t *stack, GLMFloat angle, GLMFloat x, GLMFloat y, GLMFloat z) { matrix_stack_rotate(stack, angle, x, y, z); }
void _matrix_stack_scale(matrix_stack_t *stack, GLMFloat x, GLMFloat y, GLMFloat z) { matrix_stack_scale(stack, x, y, z); }

#pragma mark - Utilities

bool _vec2_equals(const vec2_t v1, const vec2_t v2) { return vec2_equals(v1, v2); }
bool _vec3_equals(const vec3_t v1, const vec3_t v2) { return vec3_equals(v1, v2); }
bool _vec4_equals(const vec4_t v1, const vec4_t v2) { return vec4_equals(v1, v2); }
bool _mat4_equals(const mat4_t m1, const mat4_t m2) { return mat4_equals(m1, m2); }
bool _quat_equals(const quat_t q1, const quat_t q2) { return quat_equals(q1, q2); }
#endif

