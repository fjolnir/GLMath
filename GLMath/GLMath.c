//
//  GLMath.c
//  Accelerate framework test
//
//  Created by Fjölnir Ásgeirsson on 6/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GLMath.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#import <Accelerate/Accelerate.h>

#define EPSILON (1.0E-8)

const vec2_t kVec2_zero = { 0.0f, 0.0f };
const vec3_t kVec3_zero = { 0.0f, 0.0f, 0.0f };
const vec4_t kVec4_zero = { 0.0f, 0.0f, 0.0f, 0.0f };

const mat4_t kMat4_identity = MAT4_IDENTITY;
const mat4_t kMat4_zero = { 0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 0.0f };

#pragma mark Stack
float_stack_t *float_stack_create(unsigned int numberOfComponents, unsigned int initialCapacity) {
  float_stack_t *out;
  out = malloc(sizeof(float_stack_t));
  out->numberOfItems = 0;
  out->numberOfComponents = numberOfComponents;
  out->capacity = initialCapacity;
  out->items = malloc(sizeof(float*)*initialCapacity);
  
  return out;
}
void float_stack_destroy(float_stack_t *stack) {
  free(stack->items);
  free(stack);
}


// Pushes the passed item on to the top of the stack
void float_stack_push_item(float_stack_t *stack, float *item) {
  if((stack->numberOfItems + 1) == stack->capacity) {
    // If the stack is full we double it's size
    stack->capacity *= 2;
    stack->items = realloc(stack->items, stack->capacity);
  }
  stack->items[stack->numberOfItems] = calloc(stack->numberOfComponents, sizeof(float));
  if(item != NULL)
    memcpy(stack->items[stack->numberOfItems], item, sizeof(float)*stack->numberOfComponents);
  
  ++stack->numberOfItems;
}

// Pushes an identical copy of the currently topmost item onto the stack (or a zeroed item if no item currently exists)
inline void float_stack_push(float_stack_t *stack) {
  float_stack_push_item(stack, stack->numberOfItems >= 1 ? stack->items[stack->numberOfItems-1] : NULL);
}

// Pops an item off the stack
void float_stack_pop(float_stack_t *stack) {
  --stack->numberOfItems;
  free(stack->items[stack->numberOfItems]);
  // If the stack is far from full free up some memory
  if(stack->capacity > 32 && stack->numberOfItems < stack->capacity/2) {
    stack->capacity /= 2;
    stack->items = realloc(stack->items, stack->capacity);
  }
}
// Returns the topmost item in the stack
inline float *float_stack_current(float_stack_t *stack) {
  assert(stack->numberOfItems > 0);
  return stack->items[stack->numberOfItems-1];
}

#pragma mark -
#pragma mark Vector(2) math
inline vec2_t *vec2_add(const vec2_t *v1, const vec2_t *v2, vec2_t *out) {
  vDSP_vadd(*v1, 1, *v2, 1, *out, 1, 2);
  return out;
}
inline vec2_t *vec2_sub(const vec2_t *v1, const vec2_t *v2, vec2_t *out) {
  vDSP_vsub(*v1, 1, *v2, 1, *out, 1, 2);
  return out;
}
inline vec2_t *vec2_mul(const vec2_t *v1, const vec2_t *v2, vec2_t *out) {
  vDSP_vmul(*v1, 1, *v2, 1, *out, 1, 2);
  return out;
}
inline float vec2_dot(const vec2_t *v1, const vec2_t *v2) {
  float out;
  vDSP_dotpr(*v1, 1, *v2, 1, &out, 2);
  return out;
}
inline float vec2_magSquared(const vec2_t *v) {
  float magnitudes[2];
  vDSP_vsq(*v, 1, magnitudes, 1, 2);
  return magnitudes[0] + magnitudes[1];
}
inline float vec2_mag(const vec2_t *v) {
  return sqrtf(vec2_magSquared(v));
}
inline vec2_t *vec2_normalize(const vec2_t *v, vec2_t *out) {
  vec2_scalarDiv(v, vec2_mag(v), out);
  return out;
}
inline float vec2_dist(const vec2_t *v1, const vec2_t *v2) {
  float magnitudes[2];
  vDSP_vdist((float*)*v1, 1, (float*)*v2, 1, magnitudes, 1, 2);
  return magnitudes[0] + magnitudes[1];
}
inline vec2_t *vec2_scalarMul(const vec2_t *v, float s, vec2_t *out) {
  vDSP_vsmul(*v, 1, &s, *out, 1, 2);
  return out;
}
inline vec2_t *vec2_scalarDiv(const vec2_t *v, float s, vec2_t *out) {
  vDSP_vsdiv((float*)*v, 1, &s, *out, 1, 2);
  return out;
}

#pragma mark -
#pragma mark Vector(3) math
inline vec3_t *vec3_add(const vec3_t *v1, const vec3_t *v2, vec3_t *out) {
  vDSP_vadd(*v1, 1, *v2, 1, *out, 1, 3);
  return out;
}
inline vec3_t *vec3_sub(const vec3_t *v1, const vec3_t *v2, vec3_t *out) {
  vDSP_vsub(*v1, 1, *v2, 1, *out, 1, 3);
  return out;
}
inline vec3_t *vec3_mul(const vec3_t *v1, const vec3_t *v2, vec3_t *out) {
  vDSP_vmul(*v1, 1, *v2, 1, *out, 1, 3);
  return out;
}
inline float vec3_dot(const vec3_t *v1, const vec3_t *v2) {
  float out;
  vDSP_dotpr(*v1, 1, *v2, 1, &out, 3);
  return out;
}
inline float vec3_magSquared(const vec3_t *v) {
  float magnitudes[3];
  vDSP_vsq(*v, 1, magnitudes, 1, 3);
  return magnitudes[0] + magnitudes[1] + magnitudes[2];
}
inline float vec3_mag(const vec3_t *v) {
  return sqrtf(vec3_magSquared(v));
}
inline vec3_t *vec3_normalize(const vec3_t *v, vec3_t *out) {
  vec3_scalarDiv(v, vec3_mag(v), out);
  return out;
}
inline float vec3_dist(const vec3_t *v1, const vec3_t *v2) {
  float magnitudes[3];
  vDSP_vdist((float*)*v1, 1, (float*)*v2, 1, magnitudes, 1, 3);
  return magnitudes[0] + magnitudes[1] + magnitudes[2];
}
inline vec3_t *vec3_scalarMul(const vec3_t *v, float s, vec3_t *out) {
  vDSP_vsmul(*v, 1, &s, *out, 1, 3);
  return out;
}
inline vec3_t *vec3_scalarDiv(const vec3_t *v, float s, vec3_t *out) {
  vDSP_vsdiv((float*)*v, 1, &s, *out, 1, 3);
  return out;
}

#pragma mark -
#pragma mark Vector(4) math
inline vec4_t *vec4_add(const vec4_t *v1, const vec4_t *v2, vec4_t *out) {
  vDSP_vadd(*v1, 1, *v2, 1, *out, 1, 4);
  return out;
}
inline vec4_t *vec4_sub(const vec4_t *v1, const vec4_t *v2, vec4_t *out) {
  vDSP_vsub(*v1, 1, *v2, 1, *out, 1, 4);
  return out;
}
inline vec4_t *vec4_mul(const vec4_t *v1, const vec4_t *v2, vec4_t *out) {
  vDSP_vmul(*v1, 1, *v2, 1, *out, 1, 4);
  return out;
}
inline float vec4_dot(const vec4_t *v1, const vec4_t *v2) {
  float out;
  vDSP_dotpr(*v1, 1, *v2, 1, &out, 4);
  return out;
}
inline float vec4_magSquared(const vec4_t *v) {
  float magnitudes[4];
  vDSP_vsq(*v, 1, magnitudes, 1, 4);
  return magnitudes[0] + magnitudes[1] + magnitudes[2] + magnitudes[3];
}
inline float vec4_mag(const vec4_t *v) {
  return sqrtf(vec4_magSquared(v));
}
inline vec4_t *vec4_normalize(const vec4_t *v, vec4_t *out) {
  vec4_scalarDiv(v, vec4_mag(v), out);
  return out;
}
inline float vec4_dist(const vec4_t *v1, const vec4_t *v2) {
  float magnitudes[4];
  vDSP_vdist((float*)*v1, 1, (float*)*v2, 1, magnitudes, 1, 4);
  return magnitudes[0] + magnitudes[1] + magnitudes[2] + magnitudes[3];
}
inline vec4_t *vec4_scalarMul(const vec4_t *v, float s, vec4_t *out) {
  vDSP_vsmul(*v, 1, &s, *out, 1, 4);
  return out;
}
inline vec4_t *vec4_scalarDiv(const vec4_t *v, float s, vec4_t *out) {
  vDSP_vsdiv((float*)*v, 1, &s, *out, 1, 4);
  return out;
}

#pragma mark -
#pragma mark Matrix math
inline mat4_t *mat4_mul(const mat4_t *m1, const mat4_t *m2, mat4_t *out) {
  vDSP_mmul((float*)*m1, 1, (float*)*m2, 1, *out, 1, 4, 4, 4);
  return out;
}
inline vec4_t *vec4_mul_mat4(const vec4_t *v, const mat4_t *m, vec4_t *out) {
  vDSP_mmul((float*)*v, 1, (float*)*m, 1, *out, 1, 1, 4, 4);
  return out;
}

#pragma mark -
#pragma mark Quaternion math
// Generates a unit quaternion
quat_t *quat_makef(float x, float y, float z, float angle, quat_t *out) {
  vec3_t vec = { x, y, z };
  return quat_makev(&vec, angle, out);
}
quat_t *quat_makev(vec3_t *axis, float angle, quat_t *out) {
  vec3_t normalized;
  vec3_normalize((const vec3_t*)axis, &normalized);

  float sin = sinf(angle/2.0f);
  (*out)[0] = normalized[0]*sin;
  (*out)[1] = normalized[1]*sin;
  (*out)[2] = normalized[2]*sin;
  (*out)[3] = cosf(angle/2.0f);
  
  return out;
}
// Generates the standard matrix representation of a quaternion
mat4_t *quat_to_mat4(const quat_t *q, mat4_t *out) {
  // Matrix representation of a quaternion:
  // q = [a, b, c, w]
  //       [1 0 0 0]     [ 0 1 0  0]     [ 0  0 1 0]     [ 0 0  0 1]
  // q = a*[0 1 0 0] + b*[-1 0 0  0] + c*[ 0  0 0 1] + w*[ 0 0 -1 0]
  //       [0 0 1 0]     [ 0 0 0 -1]     [-1  0 0 0]     [ 0 1  0 0]
  //       [0 0 0 1]     [ 0 0 1  0]     [0  -1 0 0]     [-1 0  0 0]
  (*out)[0] = (*out)[5] = (*out)[10] = (*out)[15] = (*q)[0]; // a
  (*out)[1] = (*out)[14] = (*q)[1]; // b
  (*out)[4] = (*out)[11] = -1.0f*(*q)[1]; // b
  (*out)[2] = (*out)[7] = (*q)[2]; // c
  (*out)[8] = (*out)[13] = -1.0f*(*q)[2]; // c
  (*out)[3] = (*out)[9] = (*q)[3];
  (*out)[6] = (*out)[12] = -1.0f*(*q)[3];
  
  return out;
}
// Converts the standard matrix representation of a quaternion back to it's source
quat_t *mat4_to_quat(const mat4_t *m, quat_t *out) {
  // To convert back to a quat we just need to copy the first 3 items
  memcpy(*out, *m, sizeof(quat_t));
  return out;
}

// Generates the orthogonal matrix representation(rotation matrix) of a quaternion
mat4_t *quat_to_ortho(const quat_t *q, mat4_t *out) {
//      ¦        2     2                                      ¦
//      ¦ 1 - (2Y  + 2Z )   2XY + 2ZW         2XZ - 2YW       ¦
//      ¦                                                     ¦
//      ¦                          2     2                    ¦
//  M = ¦ 2XY - 2ZW         1 - (2X  + 2Z )   2YZ + 2XW       ¦ (Transposed)
//      ¦                                                     ¦
//      ¦                                            2     2  ¦
//      ¦ 2XZ + 2YW         2YZ - 2XW         1 - (2X  + 2Y ) ¦
//      ¦                                                     ¦
  float xx = (*q)[0]*(*q)[0];
  float xy = (*q)[0]*(*q)[1];
  float xz = (*q)[0]*(*q)[2];
  float xw = (*q)[0]*(*q)[3];
  float yy = (*q)[1]*(*q)[1];
  float yz = (*q)[1]*(*q)[2];
  float yw = (*q)[1]*(*q)[3];
  float zz = (*q)[2]*(*q)[2];
  float zw = (*q)[2]*(*q)[3];
  
  (*out)[0]  = 1.0f - 2.0f*( yy + zz ); 
  (*out)[4]  =     2.0f*( xy - zw ); 
  (*out)[8]  =     2.0f*( xz + yw ); 
  (*out)[1]  =     2.0f*( xy + zw );
  (*out)[5]  = 1 - 2.0f*( xx + zz );
  (*out)[9]  =     2.0f*( yz - xw );
  (*out)[2]  =     2.0f*( xz - yw );
  (*out)[6]  =     2.0f*( yz + xw );
  (*out)[10] = 1.0f - 2.0f*( xx + yy );
  
  (*out)[3] = (*out)[7] = (*out)[11] = (*out)[12] = (*out)[13] = (*out)[14] = 0.0f;
  (*out)[15] = 1.0f;
  
  return out;
}

quat_t *ortho_to_quat(const mat4_t *m, quat_t *out) {
  float trace = 1 + (*m)[0] + (*m)[5] + (*m)[10];
  float s;
  // If the trace is too close to 0 we'll get serious distortion
  if(trace > 0.000001) {
    s = sqrtf(trace)*2.0f;
    (*out)[0] = ((*m)[9] - (*m)[6]) / s;
    (*out)[1] = ((*m)[2] - (*m)[8]) / s;
    (*out)[2] = ((*m)[4] - (*m)[1]) / s;
    (*out)[3] = s / 4.0f;
  }
  // If the trace is 0 then find which diagonal element has the greatest value
  else if((*m)[0] > (*m)[5] && (*m)[0] > (*m)[10]) { // Col 0
    s = sqrtf(1.0f + (*m)[0] - (*m)[5] - (*m)[10])*2.0f;
    (*out)[0] = s / 4.0f;
    (*out)[1] = ((*m)[4] - (*m)[1]) / s;
    (*out)[2] = ((*m)[2] - (*m)[8]) / s;
    (*out)[3] = ((*m)[9] - (*m)[6]) / s;
  } else if((*m)[5] > (*m)[10]) { // Col 1
    s = sqrtf(1.0f + (*m)[5] - (*m)[0] - (*m)[10])*2.0f;
    (*out)[0] = ((*m)[4] - (*m)[1]) / s;
    (*out)[1] = s / 4.0f;
    (*out)[2] = ((*m)[9] - (*m)[6]) / s;
    (*out)[3] = ((*m)[2] - (*m)[8]) / s;
  } else { // Col 2
    s = sqrtf(1.0f + (*m)[10] - (*m)[0] - (*m)[5])*2.0f;
    (*out)[0] = ((*m)[2] - (*m)[8]) / s;
    (*out)[1] = ((*m)[9] - (*m)[6]) / s;
    (*out)[2] = s / 4.0f;
    (*out)[3] = ((*m)[4] - (*m)[1]) / s;
  }
  
  return out;
}

inline float quat_magSquared(const quat_t *q) {
  return vec4_magSquared(q);
}
inline float quat_mag(const quat_t *q) {
  return vec4_mag(q);
}
quat_t *quat_computeW(quat_t *q) {
  float t = 1.0f - quat_magSquared((const quat_t*)q);
  
 if (t < 0.0f)
    (*q)[3] = 0.0f;
  else
    (*q)[3] = -1*sqrtf(t);
  
  return q;
}
inline quat_t *quat_normalize(quat_t *q) {
  float mag = quat_mag((const quat_t*)q);
  // Normalize if the magnitude is > 0
  if (mag <= 0.0f)
    return q;
  float normalizedMag = 1.0f / mag;
  return vec4_scalarMul((const vec4_t*)q, normalizedMag, q);
}
inline quat_t *quat_multQuat(const quat_t *q1, const quat_t *q2, quat_t *out) {
  mat4_t q1m, q2m, temp;
  quat_to_mat4(q1, &q1m);
  quat_to_mat4(q2, &q2m);
  mat4_mul((const mat4_t*)&q1m, (const mat4_t*)&q2m, &temp);
  
  return mat4_to_quat((const mat4_t*)&temp, out);
}
inline vec4_t *quat_rotatePoint(const quat_t *q, const vec4_t *v, vec4_t *out) {
  mat4_t rotationMatrix;
  quat_to_ortho(q, &rotationMatrix);
  printMat4(rotationMatrix);
  return vec4_mul_mat4(v, (const mat4_t*)&rotationMatrix, out);
}
inline float quat_dotProduct(const quat_t *q1, const quat_t *q2) {
  return vec4_dot((const vec4_t*)q1, (const vec4_t*)q2);
}
inline quat_t *quat_inverse(const quat_t *q, quat_t *out) {
  // Multiply the vector by -1 and leave the angle alone
  vec3_scalarMul((const vec3_t*)q, -1.0f, (vec3_t*)*out);
  (*out)[3] = (*q)[3];
  return out;
}

inline quat_t *quat_slerp(const quat_t *q1, const quat_t *q2, float t, quat_t *out) {
  // Return edge points without interpolating if the value is out of range
  if (t <= 0.0) {
    memcpy(*out, *q1, sizeof(quat_t));
    return out;
  } else if (t >= 1.0) {
    memcpy(*out, *q2, sizeof(quat_t));
    return out;
  }
  // Compute the cosine of the angle between the quaternions
  float cosOmega = quat_dotProduct(q1, q2);
  // If the dot product is <0 then we use -q2 otherwise q2
  quat_t *q2Prepared;
  if(cosOmega < 0.0f) {
    q2Prepared = malloc(sizeof(quat_t));
    vec4_scalarMul(q2, -1.0f, q2Prepared);
    cosOmega *= -1.0f;
  } else {
    q2Prepared = (quat_t*)q2;
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
  (*out)[0] = (k1 * (*q1)[0]) + (k2 * (*q2Prepared)[0]);
  (*out)[1] = (k1 * (*q1)[1]) + (k2 * (*q2Prepared)[1]);
  (*out)[2] = (k1 * (*q1)[2]) + (k2 * (*q2Prepared)[2]);
  (*out)[3] = (k1 * (*q1)[3]) + (k2 * (*q2Prepared)[3]);
  free(q2Prepared);
  
  return out;
}


#pragma mark -
#pragma mark Affine transformations
mat4_t *mat4_make_translation(float x, float y, float z, mat4_t *out) {
  memcpy(*out, kMat4_identity, sizeof(mat4_t));
  (*out)[3]  = x;
  (*out)[7]  = y;
  (*out)[11] = z;
  
  return out;
}

inline void mat4_translate(mat4_t *mat, float x, float y, float z) {
  (*mat)[3]  += x;
  (*mat)[7]  += y;
  (*mat)[11] += z;
}

mat4_t *mat4_make_rotation(float angle, float x, float y, float z, mat4_t *out) {
  /*
   |  cycz + sxsysz   czsxsy - cysz   cxsy  0 |
   M = |  cxsz            cxcz           -sx    0 |
   |  cysxsz - czsy   cyczsx + sysz   cxcy  0 |
   |  0               0               0     1 |
	 
   where cA = cos(A), sA = sin(A) for A = x,y,z
   */
  float xSin = sinf(x*angle);
  float xCos = cosf(x*angle);
  float ySin = sinf(y*angle);
  float yCos = cosf(y*angle);
  float zSin = sinf(z*angle);
  float zCos = cosf(z*angle);
  
  memcpy(*out, kMat4_identity, sizeof(mat4_t));
  (*out)[0] = (yCos*zCos) + (xSin*ySin*zSin);
  (*out)[1] = (zCos*xSin*ySin) - (yCos*zSin);
  (*out)[2] = (xCos*ySin);
  
  (*out)[4] = (xCos*zSin);
  (*out)[5] = (xCos*zCos);
  (*out)[6] = (-1.0f*xSin);
  
  (*out)[8] = (yCos*xSin*zSin) - (zCos*ySin);
  (*out)[9] = (yCos*zCos*xSin) + (ySin*zSin);
  (*out)[10] = (xCos*yCos);
  
  return out;
}

void mat4_rotate(mat4_t *mat, float angle, float x, float y, float z) {
  mat4_t rotation;
  mat4_mul((const mat4_t*)mat4_make_rotation(angle, x, y, z, &rotation), (const mat4_t*)mat, mat);
}

mat4_t *mat4_make_scale(float x, float y, float z, mat4_t *out) {
  memcpy(*out, kMat4_identity, sizeof(mat4_t));
  (*out)[0]  = x;
  (*out)[5]  = y;
  (*out)[10] = z;
  
  return out;
}
inline void mat4_scale(mat4_t *mat, float x, float y, float z) {
  vec3_t scaleVec = { x, y, z };
  // Treat the matrix XYZ diagonal as a 3 item vector and multiply it by the scale
  vDSP_vmul(scaleVec, 1, *mat, 5, *mat, 5, 3);
}

#pragma mark -
#pragma mark Utilities
void printVec2(vec2_t vec) {
  printf("Vec2: [%.2f, %.2f]\n", vec[0], vec[1]);
}
void printVec3(vec3_t vec) {
  printf("Vec3: [%.2f, %.2f, %.2f]\n", vec[0], vec[1], vec[2]);
}
void printVec4(vec4_t vec) {
  printf("Vec4: [%.2f, %.2f, %.2f, %.2f]\n", vec[0], vec[1], vec[2], vec[3]);
}
void printMat4(mat4_t mat) {
  printf("Mat4: [%.2f, %.2f, %.2f, %.2f]\n", mat[0], mat[1], mat[2], mat[3]);
  printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat[4], mat[5], mat[6], mat[7]);
  printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat[8], mat[9], mat[10], mat[11]);
  printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat[12], mat[13], mat[14], mat[15]);
}
void printQuat(quat_t quat) {
  printf("Quat: [%.2f, %.2f, %.2f, %.2f]\n", quat[0], quat[1], quat[2], quat[3]);
}

bool floatArr_equals(const float *a1, const float *a2, unsigned int len) {
  for(int i = 0; i < len; ++i) {
    if(a1[i] != a2[i])
      return false;
  }
  return true;
}
bool vec2_equals(const vec2_t *v1, const vec2_t *v2) {
  return floatArr_equals(*v1, *v2, 2);
}
bool vec3_equals(const vec3_t *v1, const vec3_t *v2) {
  return floatArr_equals(*v1, *v2, 3);
}
bool vec4_equals(const vec4_t *v1, const vec4_t *v2) {
  return floatArr_equals(*v1, *v2, 4);
}
bool mat4_equals(const mat4_t *m1, const mat4_t *m2) {
  return floatArr_equals(*m1, *m2, 16);
}
bool quat_equals(const quat_t *q1, const quat_t *q2) {
  return floatArr_equals(*q1, *q2, 4);
}