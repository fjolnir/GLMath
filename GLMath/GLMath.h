// A GL Math utility library
// Uses vDSP to perform most operations
#ifndef GL_MATH_H
#define GL_MATH_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
  
// Vectors
typedef float vec2_t[2];
typedef float vec3_t[3];
typedef float vec4_t[4];
// Matrices
typedef float mat4_t[16];
// Quaternions
typedef float quat_t[4];

// Zero vectors
const vec2_t kVec2_zero;
const vec3_t kVec3_zero;
const vec4_t kVec4_zero;

#define MAT4_IDENTITY { 1.0, 0.0, 0.0, 0.0,\
                        0.0, 1.0, 0.0, 0.0,\
                        0.0, 0.0, 1.0, 0.0,\
                        0.0, 0.0, 0.0, 1.0 }

const mat4_t kMat4_identity;
const mat4_t kMat4_zero;

// Implements a stack of float arrays with an arbitrary size (so it can be used to store both matrices&vectors)
typedef struct {
  float **items;
  unsigned int numberOfComponents;
  unsigned int capacity;
  unsigned int numberOfItems;
} float_stack_t;

extern float_stack_t *float_stack_create(unsigned int numberOfComponents, unsigned int initialCapacity);
extern void float_stack_destroy(float_stack_t *stack);

// Pushes the passed item on to the top of the stack
extern void float_stack_push_item(float_stack_t *stack, float *item);
// Pushes an identical copy of the currently topmost item onto the stack (or a zeroed item if no item currently exists)
extern inline void float_stack_push(float_stack_t *stack);
// Pops an item off the stack
extern void float_stack_pop(float_stack_t *stack);
// Returns the topmost item in the stack
extern inline float *float_stack_current(float_stack_t *stack);
  
// Vector math functions
extern inline vec2_t *vec2_add(const vec2_t *v1, const vec2_t *v2, vec2_t *out);
extern inline vec2_t *vec2_sub(const vec2_t *v1, const vec2_t *v2, vec2_t *out);
extern inline vec2_t *vec2_mul(const vec2_t *v1, const vec2_t *v2, vec2_t *out);
extern inline float vec2_dot(const vec2_t *v1, const vec2_t *v2);
extern inline float vec2_magSquared(const vec2_t *v);
extern inline float vec2_mag(const vec2_t *v);
extern inline vec2_t *vec2_normalize(const vec2_t *v, vec2_t *out);
extern inline float vec2_dist(const vec2_t *v1, const vec2_t *v2);
extern inline vec2_t *vec2_scalarMul(const vec2_t *v, float s, vec2_t *out);
extern inline vec2_t *vec2_scalarDiv(const vec2_t *v, float s, vec2_t *out);

extern inline vec3_t *vec3_add(const vec3_t *v1, const vec3_t *v2, vec3_t *out);
extern inline vec3_t *vec3_sub(const vec3_t *v1, const vec3_t *v2, vec3_t *out);
extern inline vec3_t *vec3_mul(const vec3_t *v1, const vec3_t *v2, vec3_t *out);
extern inline float vec3_dot(const vec3_t *v1, const vec3_t *v2);
extern inline float vec3_magSquared(const vec3_t *v);
extern inline float vec3_mag(const vec3_t *v);
extern inline vec3_t *vec3_normalize(const vec3_t *v, vec3_t *out);
extern inline float vec3_dist(const vec3_t *v1, const vec3_t *v2);
extern inline vec3_t *vec3_scalarMul(const vec3_t *v, float s, vec3_t *out);
extern inline vec3_t *vec3_scalarDiv(const vec3_t *v, float s, vec3_t *out);

extern inline vec4_t *vec4_add(const vec4_t *v1, const vec4_t *v2, vec4_t *out);
extern inline vec4_t *vec4_sub(const vec4_t *v1, const vec4_t *v2, vec4_t *out);
extern inline vec4_t *vec4_mul(const vec4_t *v1, const vec4_t *v2, vec4_t *out);
extern inline float vec4_dot(const vec4_t *v1, const vec4_t *v2);
extern inline float vec4_magSquared(const vec4_t *v);
extern inline float vec4_mag(const vec4_t *v);
extern inline float vec4_dist(const vec4_t *v1, const vec4_t *v2);
extern inline vec4_t *vec4_scalarMul(const vec4_t *v, float s, vec4_t *out);
extern inline vec4_t *vec4_scalarDiv(const vec4_t *v, float s, vec4_t *out);

// Matrix math functions
extern inline mat4_t *mat4_mul(const mat4_t *m1, const mat4_t *m2, mat4_t *out);
extern inline vec4_t *vec4_mul_mat4(const vec4_t *v, const mat4_t *m, vec4_t *out);
extern inline mat4_t *mat4_inverse(const mat4_t *m, mat4_t *out);
extern inline mat4_t *mat4_transpose(const mat4_t *m, mat4_t *out);

// Quaternion math functions
extern quat_t *quat_makef(float x, float y, float z, float angle, quat_t *out);
extern quat_t *quat_makev(vec3_t *axis, float angle, quat_t *out);
extern mat4_t *quat_to_mat4(const quat_t *q, mat4_t *out);
extern quat_t *mat4_to_quat(const mat4_t *m, quat_t *out);
extern mat4_t *quat_to_ortho(const quat_t *q, mat4_t *out);
extern quat_t *ortho_to_quat(const mat4_t *m, quat_t *out);
extern inline float quat_magSquared(const quat_t *q);
extern inline float quat_mag(const quat_t *q);
extern quat_t *quat_computeW(quat_t *q);
extern inline quat_t *quat_normalize(quat_t *q);
extern inline quat_t *quat_multQuat(const quat_t *qA, const quat_t *qB, quat_t *out);
extern inline vec4_t *quat_rotatePoint(const quat_t *q, const vec4_t *v, vec4_t *out);
extern inline quat_t *quat_inverse(const quat_t *q, quat_t *out);
extern inline float quat_dotProduct(const quat_t *qA, const quat_t *qB);
extern inline quat_t *quat_slerp(const quat_t *qA, const quat_t *qB, float t, quat_t *out);

// Affine transforms
extern inline mat4_t *mat4_make_translation(float x, float y, float z, mat4_t *out);
extern inline void mat4_translate(mat4_t *mat, float x, float y, float z);
extern inline mat4_t *mat4_make_rotation(float angle, float x, float y, float z, mat4_t *out);
extern inline void mat4_rotate(mat4_t *mat, float angle, float x, float y, float z);
extern inline mat4_t *mat4_make_scale(float x, float y, float z, mat4_t *out);
extern inline void mat4_scale(mat4_t *mat, float x, float y, float z);

// Utilities
extern mat4_t *mat4_perspective(float fov_radians, float aspect, float zNear, float zFar, mat4_t *out);
// Generates an orthogonal viewing matrix
extern mat4_t *mat4_ortho(float left, float right, float bottom, float top, float near, float far, mat4_t *out);

extern void printVec2(vec2_t vec);
extern void printVec3(vec3_t vec);
extern void printVec4(vec4_t vec);
extern void printMat4(mat4_t mat);
extern void printQuat(quat_t quat);

extern bool floatArr_equals(const float *a1, const float *a2, unsigned int len);
extern bool vec2_equals(const vec2_t *v1, const vec2_t *v2);
extern bool vec3_equals(const vec3_t *v1, const vec3_t *v2);
extern bool vec4_equals(const vec4_t *v1, const vec4_t *v2);
extern bool mat4_equals(const mat4_t *m1, const mat4_t *m2);
extern bool quat_equals(const quat_t *q1, const quat_t *q2);
#ifdef __cplusplus
}
#endif
#endif