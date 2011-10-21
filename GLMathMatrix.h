#ifndef GL_MATH_MATRIX_H
#define GL_MATH_MATRIX_H

#include "GLMathTypes.h"
#ifdef USE_ACCELERATE_FRAMEWORK
#import <Accelerate/Accelerate.h>
#endif
#import <string.h>
#import <stdio.h>
#import <stdlib.h>
#import <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Prototypes

// Matrix math functions
static __inline__ mat3_t mat3_mul(const mat3_t m1, const mat3_t m2);
static __inline__ vec3_t vec3_mul_m(const vec3_t v, const mat3_t m);
static __inline__ mat3_t mat3_inverse(const mat3_t m);
static __inline__ mat3_t mat3_transpose(const mat3_t m);
static __inline__ float mat3_det(const mat3_t m);

static __inline__ mat4_t mat4_mul(const mat4_t m1, const mat4_t m2);
static __inline__ vec4_t vec4_mul_mat4(const vec4_t v, const mat4_t m);
static __inline__ mat4_t mat4_inverse(const mat4_t m);
static __inline__ mat4_t mat4_transpose(const mat4_t m);
static __inline__ mat3_t mat4_extract_mat3(const mat4_t m);
static __inline__ float mat4_det(mat4_t m);

// Functions used for inverting matrices when vDSP is unavailable
static mat3_t _calc_mat3_inverse(mat3_t m, bool *success_out); 
static mat3_t _mat4_sub_mat3(mat4_t m, int i, int j);
static mat4_t _calc_mat4_inverse(mat4_t m, bool *success_out);


#pragma mark Implementations

static __inline__ mat3_t mat3_mul(const mat3_t m1, const mat3_t m2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	mat3_t out;
	vDSP_mmul((float*)m1.f, 1, (float*)m2.f, 1, out.f, 1, 3, 3, 3);
	return out;
#else
	mat3_t out;
	out.f[0] = m1.f[0] * m2.f[0] + m1.f[3] * m2.f[1] + m1.f[6] * m2.f[2];
    out.f[3] = m1.f[0] * m2.f[3] + m1.f[3] * m2.f[4] + m1.f[6] * m2.f[5];
    out.f[6] = m1.f[0] * m2.f[6] + m1.f[3] * m2.f[7] + m1.f[6] * m2.f[8];
    
    out.f[1] = m1.f[1] * m2.f[0] + m1.f[4] * m2.f[1] + m1.f[7] * m2.f[2];
    out.f[4] = m1.f[1] * m2.f[3] + m1.f[4] * m2.f[4] + m1.f[7] * m2.f[5];
    out.f[7] = m1.f[1] * m2.f[6] + m1.f[4] * m2.f[7] + m1.f[7] * m2.f[8];
    
    out.f[2] = m1.f[2] * m2.f[0] + m1.f[5] * m2.f[1] + m1.f[8] * m2.f[2];
    out.f[5] = m1.f[2] * m2.f[3] + m1.f[5] * m2.f[4] + m1.f[8] * m2.f[5];
    out.f[8] = m1.f[2] * m2.f[6] + m1.f[5] * m2.f[7] + m1.f[8] * m2.f[8];
	return out;
#endif
}
static __inline__ vec3_t vec3_mul_mat3(const vec3_t v, const mat3_t m) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec3_t out;
	vDSP_mmul((float*)v.f, 1, (float*)m.f, 1, out.f, 1, 1, 3, 3);
	return out;
#else
	return (vec3_t){
		m.f[0] * v.f[0] + m.f[3] * v.f[1] + m.f[6] * v.f[2],
		m.f[1] * v.f[0] + m.f[4] * v.f[1] + m.f[7] * v.f[2],
		m.f[2] * v.f[0] + m.f[5] * v.f[1] + m.f[8] * v.f[2] };
#endif
}
static __inline__ mat3_t mat3_inverse(const mat3_t m) {
#ifdef USE_ACCELERATE_FRAMEWORK
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
#else
	bool status;
	mat3_t out = _calc_mat3_inverse(m, &status);
	if(!status) {
		printf("Could not invert 3x3 matrix!\n");
		out = kMat3_zero;
	}
	return out;
#endif
}
static __inline__ mat3_t mat3_transpose(const mat3_t m) {
#ifdef USE_ACCELERATE_FRAMEWORK
	mat3_t out;
	vDSP_mtrans((float*)m.f, 1, out.f, 1, 3, 3);
	return out;
#else
	return (mat3_t) { m.f[0], m.f[3], m.f[6],
	                  m.f[1], m.f[4], m.f[7],
	                  m.f[2], m.f[5], m.f[8] };
#endif
}

static __inline__ mat3_t mat4_extract_mat3(const mat4_t m) {
	mat3_t out = { m.m00, m.m01, m.m02,
	               m.m10, m.m11, m.m12,
	               m.m20, m.m21, m.m22 };
	return out;
}

static __inline__ float mat3_det(const mat3_t m) {
	return m.f[0]   * ( m.f[4]*m.f[8] - m.f[7]*m.f[5] )
           - m.f[1] * ( m.f[3]*m.f[8] - m.f[6]*m.f[5] )
           + m.f[2] * ( m.f[3]*m.f[7] - m.f[6]*m.f[4] );
}

#pragma mark - 4x4

static __inline__ mat4_t mat4_mul(mat4_t m1, mat4_t m2) {
#ifdef USE_ACCELERATE_FRAMEWORK
	mat4_t out;
	vDSP_mmul((float*)m1.f, 1, (float*)m2.f, 1, out.f, 1, 4, 4, 4);
	return out;
#else
	// TODO: actually write a flipped multiplication routine
	mat4_t m;
	m = m1;
	m1 = m2;
	m2 = m;
    m.f[0]  = m1.f[0] * m2.f[0]  + m1.f[4] * m2.f[1]  + m1.f[8] * m2.f[2]   + m1.f[12] * m2.f[3];
	m.f[4]  = m1.f[0] * m2.f[4]  + m1.f[4] * m2.f[5]  + m1.f[8] * m2.f[6]   + m1.f[12] * m2.f[7];
	m.f[8]  = m1.f[0] * m2.f[8]  + m1.f[4] * m2.f[9]  + m1.f[8] * m2.f[10]  + m1.f[12] * m2.f[11];
	m.f[12] = m1.f[0] * m2.f[12] + m1.f[4] * m2.f[13] + m1.f[8] * m2.f[14]  + m1.f[12] * m2.f[15];
    
	m.f[1]  = m1.f[1] * m2.f[0]  + m1.f[5] * m2.f[1]  + m1.f[9] * m2.f[2]   + m1.f[13] * m2.f[3];
	m.f[5]  = m1.f[1] * m2.f[4]  + m1.f[5] * m2.f[5]  + m1.f[9] * m2.f[6]   + m1.f[13] * m2.f[7];
	m.f[9]  = m1.f[1] * m2.f[8]  + m1.f[5] * m2.f[9]  + m1.f[9] * m2.f[10]  + m1.f[13] * m2.f[11];
	m.f[13] = m1.f[1] * m2.f[12] + m1.f[5] * m2.f[13] + m1.f[9] * m2.f[14]  + m1.f[13] * m2.f[15];
    
	m.f[2]  = m1.f[2] * m2.f[0]  + m1.f[6] * m2.f[1]  + m1.f[10] * m2.f[2]  + m1.f[14] * m2.f[3];
	m.f[6]  = m1.f[2] * m2.f[4]  + m1.f[6] * m2.f[5]  + m1.f[10] * m2.f[6]  + m1.f[14] * m2.f[7];
	m.f[10] = m1.f[2] * m2.f[8]  + m1.f[6] * m2.f[9]  + m1.f[10] * m2.f[10] + m1.f[14] * m2.f[11];
	m.f[14] = m1.f[2] * m2.f[12] + m1.f[6] * m2.f[13] + m1.f[10] * m2.f[14] + m1.f[14] * m2.f[15];
    
	m.f[3]  = m1.f[3] * m2.f[0]  + m1.f[7] * m2.f[1]  + m1.f[11] * m2.f[2]  + m1.f[15] * m2.f[3];
	m.f[7]  = m1.f[3] * m2.f[4]  + m1.f[7] * m2.f[5]  + m1.f[11] * m2.f[6]  + m1.f[15] * m2.f[7];
	m.f[11] = m1.f[3] * m2.f[8]  + m1.f[7] * m2.f[9]  + m1.f[11] * m2.f[10] + m1.f[15] * m2.f[11];
	m.f[15] = m1.f[3] * m2.f[12] + m1.f[7] * m2.f[13] + m1.f[11] * m2.f[14] + m1.f[15] * m2.f[15];
	return m;
#endif
}
static __inline__ vec4_t vec4_mul_mat4(const vec4_t v, const mat4_t m) {
#ifdef USE_ACCELERATE_FRAMEWORK
	vec4_t out;
	vDSP_mmul((float*)v.f, 1, (float*)m.f, 1, out.f, 1, 1, 4, 4);
	return out;
#else
    return (vec4_t){ m.f[0]*v.f[0] + m.f[4]*v.f[1] + m.f[8]*v.f[2] + m.f[12]*v.f[3],
                     m.f[1]*v.f[0] + m.f[5]*v.f[1] + m.f[9]*v.f[2] + m.f[13]*v.f[3],
                     m.f[2]*v.f[0] + m.f[6] * v.f[1] + m.f[10] * v.f[2] + m.f[14]*v.f[3],
                     m.f[3]*v.f[0] + m.f[7]*v.f[1] + m.f[11]*v.f[2] + m.f[15]*v.f[3] };
#endif
}
static __inline__ mat4_t mat4_inverse(const mat4_t m) {
#ifdef USE_ACCELERATE_FRAMEWORK
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
#else
	bool status;
	mat4_t out = _calc_mat4_inverse(m, &status);
	if(!status) {
		printf("Could not invert 4x4 matrix!\n");
		out = kMat4_zero;
	}
	return out;
//#warning TODO: implement 4x4 matrix inverse
	//return kMat4_zero;
#endif
}
static __inline__ mat4_t mat4_transpose(const mat4_t m) {
#ifdef USE_ACCELERATE_FRAMEWORK
	mat4_t out;
	vDSP_mtrans((float*)m.f, 1, out.f, 1, 4, 4);
	return out;
#else
	return (mat4_t){ m.f[0], m.f[4], m.f[8],  m.f[12],
                     m.f[1], m.f[5], m.f[9],  m.f[13],
                     m.f[2], m.f[6], m.f[10], m.f[14],
                     m.f[3], m.f[7], m.f[11], m.f[15] };
#endif
}

static __inline__ float mat4_det(mat4_t m)
{
	float det, out = 0.0f, i = 1;
	mat3_t subMtx;
	for(int n = 0; n < 4; n++, i *= -1) {
		subMtx = _mat4_sub_mat3(m, 0, n);
		det     = mat3_det(subMtx);
		out += m.f[n] * det * i;
	}
	return out;
}

#pragma mark - Inversion functions

static mat3_t _calc_mat3_inverse(mat3_t m, bool *success_out) {
	float det = mat3_det(m);
	if(fabs(det) < 0.0005) {
		if(success_out != NULL) *success_out = false;
		return kMat3_identity;
	}
	mat3_t out;
	out.f[0] =    m.f[4]*m.f[8] - m.f[5]*m.f[7]   / det;
	out.f[1] = -( m.f[1]*m.f[8] - m.f[7]*m.f[2] ) / det;
	out.f[2] =    m.f[1]*m.f[5] - m.f[4]*m.f[2]   / det;
	out.f[3] = -( m.f[3]*m.f[8] - m.f[5]*m.f[6] ) / det;
	out.f[4] =    m.f[0]*m.f[8] - m.f[6]*m.f[2]   / det;
	out.f[5] = -( m.f[0]*m.f[5] - m.f[3]*m.f[2] ) / det;
	out.f[6] =    m.f[3]*m.f[7] - m.f[6]*m.f[4]   / det;
	out.f[7] = -( m.f[0]*m.f[7] - m.f[6]*m.f[1] ) / det;
	out.f[8] =    m.f[0]*m.f[4] - m.f[1]*m.f[3]   / det;
	
	if(success_out != NULL) *success_out = true;
	return out;
}


static mat3_t _mat4_sub_mat3(mat4_t m, int i, int j) {
	mat3_t out;
	int si, sj;
	// loop through 3x3 submatrix
	for(int di = 0; di < 3; di ++ ) {
		for(int dj = 0; dj < 3; dj ++ ) {
			// map 3x3 element (destination) to 4x4 element (source)
			si = di + ( ( di >= i ) ? 1 : 0 );
			sj = dj + ( ( dj >= j ) ? 1 : 0 );
			// copy element
			out.f[di * 3 + dj] = m.f[si * 4 + sj];
		}
	}
	return out;
}

static mat4_t _calc_mat4_inverse(mat4_t m, bool *success_out) {
	mat4_t out;
	float det = mat4_det(m);
	mat3_t mtemp;
	int sign;
	if(fabs(det) < 0.0005) {
		if(success_out != NULL) *success_out = false;		
		return kMat4_identity;
	}
	for(int i = 0; i < 4; i++ ) {
		for(int j = 0; j < 4; j++ ) {
			sign = 1 - ( (i +j) % 2 ) * 2;
			mtemp = _mat4_sub_mat3(m, i, j);
			out.f[i+j*4] = ( mat3_det(mtemp) * sign ) / det;
		}
	}
	if(success_out != NULL) *success_out = true;		
	return out;
}


#ifdef __cplusplus
}
#endif
#endif
