#ifndef GL_MATH_QUAT_H
#define GL_MATH_QUAT_H

#include "GLMathTypes.h"
#import <Accelerate/Accelerate.h>
#include <assert.h>

#define GLM_EPSILON (1.0E-8)

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Prototypes

// Quaternion math functions
static quat_t quat_makef(float x, float y, float z, float angle);
static quat_t quat_makev(vec3_t axis, float angle);
static mat4_t quat_to_mat4(const quat_t q);
static quat_t mat4_to_quat(const mat4_t m);
static mat4_t quat_to_ortho(const quat_t q);
static quat_t ortho_to_quat(const mat4_t m);
static __inline__ float quat_magSquared(const quat_t q);
static __inline__ float quat_mag(const quat_t q);
static quat_t quat_computeW(quat_t q);
static __inline__ quat_t quat_normalize(quat_t q);
static __inline__ quat_t quat_multQuat(const quat_t qA, const quat_t qB);
static __inline__ vec4_t quat_rotatePoint(const quat_t q, const vec4_t v);
static __inline__ quat_t quat_inverse(const quat_t q);
static __inline__ float quat_dotProduct(const quat_t qA, const quat_t qB);
static __inline__ quat_t quat_slerp(const quat_t qA, const quat_t qB, float t);

#pragma mark Implementations

// Generates a unit quaternion
static quat_t quat_makef(float x, float y, float z, float angle) {
	vec3_t vec = { x, y, z };
	return quat_makev(vec, angle);
}
static quat_t quat_makev(vec3_t axis, float angle) {
	quat_t out;
	vec3_t normalized;
	normalized = vec3_normalize(axis);

	float sin = sinf(angle/2.0f);
	out.x = normalized.x*sin;
	out.y = normalized.y*sin;
	out.z = normalized.z*sin;
	out.w = cosf(angle/2.0f);

	return out;
}
// Generates the standard matrix representation of a quaternion
static mat4_t quat_to_mat4(const quat_t q) {
	mat4_t out;
	// Matrix representation of a quaternion:
	// q = [a, b, c, w]
	//       [1 0 0 0]     [ 0 1 0  0]     [ 0  0 1 0]     [ 0 0  0 1]
	// q = a*[0 1 0 0] + b*[-1 0 0  0] + c*[ 0  0 0 1] + w*[ 0 0 -1 0]
	//       [0 0 1 0]     [ 0 0 0 -1]     [-1  0 0 0]     [ 0 1  0 0]
	//       [0 0 0 1]     [ 0 0 1  0]     [ 0 -1 0 0]     [-1 0  0 0]
	out.f[0] = out.f[5] = out.f[10] = out.f[15] = q.f[0]; // a
	out.f[1] = out.f[14]                          = q.f[1]; // b
	out.f[4] = out.f[11]                          = -1.0f*q.f[1]; // b
	out.f[2] = out.f[7]                           = q.f[2]; // c
	out.f[8] = out.f[13]                          = -1.0f*q.f[2]; // c
	out.f[3] = out.f[9]                           = q.f[3];
	out.f[6] = out.f[12] = -1.0f*q.f[3];

	out.m13 = out.m23 = 0.0f;
	out.m30 = out.m31 = out.m32 = 0.0f;
	return out;
}
// Converts the standard matrix representation of a quaternion back to it's source
static quat_t mat4_to_quat(const mat4_t m) {
	// To convert back to a quat we just need to copy the first 3 items
	quat_t out = {0.0f};
	memcpy(out.f, m.f, sizeof(quat_t));
	return out;
}

// Generates the orthogonal matrix representation(rotation matrix) of a quaternion
static mat4_t quat_to_ortho(const quat_t q) {
	float xx = q.f[0]*q.f[0];
	float xy = q.f[0]*q.f[1];
	float xz = q.f[0]*q.f[2];
	float xw = q.f[0]*q.f[3];
	float yy = q.f[1]*q.f[1];
	float yz = q.f[1]*q.f[2];
	float yw = q.f[1]*q.f[3];
	float zz = q.f[2]*q.f[2];
	float zw = q.f[2]*q.f[3];

	mat4_t out;
	out.f[0]  = 1.0f - 2.0f*( yy + zz );
	out.f[4]  = 2.0f * ( xy - zw );
	out.f[8]  = 2.0f * ( xz + yw );
	out.f[1]  = 2.0f * ( xy + zw );
	out.f[5]  = 1 - 2.0f * ( xx + zz );
	out.f[9]  = 2.0f * ( yz - xw );
	out.f[2]  = 2.0f * ( xz - yw );
	out.f[6]  = 2.0f * ( yz + xw );
	out.f[10] = 1.0f - 2.0f*( xx + yy );

	out.f[3] = out.f[7] = out.f[11] = out.f[12] = out.f[13] = out.f[14] = 0.0f;
	out.f[15] = 1.0f;

	return out;
}

static quat_t ortho_to_quat(const mat4_t m) {
	quat_t out;
	float trace = 1 + m.f[0] + m.f[5] + m.f[10];
	float s;
	// If the trace is too close to 0 we'll get serious distortion
	if(trace > 0.000001) {
		s = sqrtf(trace)*2.0f;
		out.f[0] = (m.f[9] - m.f[6]) / s;
		out.f[1] = (m.f[2] - m.f[8]) / s;
		out.f[2] = (m.f[4] - m.f[1]) / s;
		out.f[3] = s / 4.0f;
	}
	// If the trace is 0 then find which diagonal element has the greatest value
	else if(m.f[0] > m.f[5] && m.f[0] > m.f[10]) { // Col 0
		s = sqrtf(1.0f + m.f[0] - m.f[5] - m.f[10])*2.0f;
		out.f[0] = s / 4.0f;
		out.f[1] = (m.f[4] - m.f[1]) / s;
		out.f[2] = (m.f[2] - m.f[8]) / s;
		out.f[3] = (m.f[9] - m.f[6]) / s;
	} else if(m.f[5] > m.f[10]) { // Col 1
		s = sqrtf(1.0f + m.f[5] - m.f[0] - m.f[10])*2.0f;
		out.f[0] = (m.f[4] - m.f[1]) / s;
		out.f[1] = s / 4.0f;
		out.f[2] = (m.f[9] - m.f[6]) / s;
		out.f[3] = (m.f[2] - m.f[8]) / s;
	} else { // Col 2
		s = sqrtf(1.0f + m.f[10] - m.f[0] - m.f[5])*2.0f;
		out.f[0] = (m.f[2] - m.f[8]) / s;
		out.f[1] = (m.f[9] - m.f[6]) / s;
		out.f[2] = s / 4.0f;
		out.f[3] = (m.f[4] - m.f[1]) / s;
	}

	return out;
}

static __inline__ float quat_magSquared(const quat_t q) {
	return vec4_magSquared(*(const vec4_t *)&q);
}
static __inline__ float quat_mag(const quat_t q) {
	return vec4_mag(*(const vec4_t *)&q);
}
static quat_t quat_computeW(quat_t q) {
	quat_t out;
	memcpy(out.f, q.f, sizeof(quat_t));

	float t = 1.0f - quat_magSquared(*(const quat_t*)&out);

	if(t < 0.0f)
		out.f[3] = 0.0f;
	else
		out.f[3] = -1*sqrtf(t);

	return out;
}
static __inline__ quat_t quat_normalize(quat_t q) {
	vec4_t out;
	memcpy(out.f, q.f, sizeof(quat_t));

	float mag = quat_mag(*(const quat_t*)&out);
	// Normalize if the magnitude is > 0
	if (mag <= 0.0f)
		return *(quat_t *)&out;
	float normalizedMag = 1.0f / mag;
	out = vec4_scalarMul(out, normalizedMag);
	return *(quat_t *)&out;
}
static __inline__ quat_t quat_multQuat(const quat_t q1, const quat_t q2) {
	mat4_t q1m, q2m, temp;
	q1m = quat_to_mat4(q1);
	q2m = quat_to_mat4(q2);
	temp = mat4_mul(q1m, q2m);

	return mat4_to_quat(temp);
}
static __inline__ vec4_t quat_rotatePoint(const quat_t q, const vec4_t v) {
	mat4_t rotationMatrix;
	rotationMatrix = quat_to_ortho(q);
	return vec4_mul_mat4(v, rotationMatrix);
}
static __inline__ float quat_dotProduct(const quat_t q1, const quat_t q2) {
	return vec4_dot(*(const vec4_t*)&q1, *(const vec4_t*)&q2);
}
static __inline__ quat_t quat_inverse(const quat_t q) {
	// Multiply the vector by -1 and leave the angle alone
	vec4_t out;
	out = vec4_scalarMul(*(vec4_t *)&q, -1.0f);
	out.f[3] = q.f[3];
	return *(quat_t *)&out;
}

static __inline__ quat_t quat_slerp(const quat_t q1, const quat_t q2, float t) {
	quat_t out;
	// Return edge points without interpolating if the value is out of range
	if (t <= 0.0) {
		memcpy(out.f, q1.f, sizeof(quat_t));
		return out;
	} else if (t >= 1.0) {
		memcpy(out.f, q2.f, sizeof(quat_t));
		return out;
	}
	// Compute the cosine of the angle between the quaternions
	float cosOmega = quat_dotProduct(q1, q2);
	// If the dot product is <0 then we use -q2 otherwise q2
	quat_t q2Prepared;
	if(cosOmega < 0.0f) {
		vec4_t multiplied = vec4_scalarMul(*(vec4_t *)&q2, -1.0f);
		q2Prepared = *(quat_t *)&multiplied;
		cosOmega *= -1.0f;
	} else {
		q2Prepared = q2;
	}
	// Verify that the quaternions are in fact unit quaternions
	assert(cosOmega <= 1.0f+GLM_EPSILON);

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
	out.f[0] = (k1 * q1.f[0]) + (k2 * q2Prepared.x);
	out.f[1] = (k1 * q1.f[1]) + (k2 * q2Prepared.y);
	out.f[2] = (k1 * q1.f[2]) + (k2 * q2Prepared.z);
	out.f[3] = (k1 * q1.f[3]) + (k2 * q2Prepared.w);

	return out;
}

#ifdef __cplusplus
}
#endif
#endif
