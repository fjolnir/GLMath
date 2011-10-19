#ifndef GL_MATH_TYPES_H
#define GL_MATH_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Types

// Vectors
typedef union {
	float f[2];
	struct { float x; float y; };
	struct { float w; float h; };
} vec2_t;

typedef union {
	float f[3];
	struct { float x; float y; float z; };
	struct { float r; float g; float b; };
} vec3_t;
typedef union {
	float f[4];
	struct { float x; float y; float z; float w; };
	struct { float r; float g; float b; float a; };
} vec4_t;

// Matrices
typedef union {
	float f[9];
	struct {
		float m00, m01, m02;
		float m10, m11, m12;
		float m20, m21, m22;
	};
} mat3_t;

typedef union {
	float f[16];
	struct {
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;
	};
} mat4_t;

// Quaternions
typedef union {
	float f[4];
	struct { float x; float y; float z; float w; };
} quat_t;

// Matrix stack
typedef struct {
	mat4_t *items;
	unsigned int capacity;
	unsigned int count;
} matrix_stack_t;

#pragma mark - Constants

// Zero vectors
extern const vec2_t kVec2_zero;
extern const vec3_t kVec3_zero;
extern const vec4_t kVec4_zero;

extern const mat3_t kMat3_identity;
extern const mat3_t kMat3_zero;
extern const mat4_t kMat4_identity;
extern const mat4_t kMat4_zero;

#ifdef __cplusplus
}
#endif
#endif
