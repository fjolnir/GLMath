#ifndef GL_MATH_TYPES_H
#define GL_MATH_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

#pragma mark - Types

// Vectors
union _vec2_t {
	float f[2];
	struct { float x; float y; };
	struct { float w; float h; };
	struct { float u; float v; };

};
typedef union _vec2_t vec2_t;

union _vec3_t {
	float f[3];
	struct { float x; float y; float z; };
	struct { float r; float g; float b; };
};
typedef union _vec3_t vec3_t;

union _vec4_t {
	float f[4];
	struct { float x; float y; float z; float w; };
	struct { float r; float g; float b; float a; };
};
typedef union _vec4_t vec4_t;

// Matrices
union _mat3_t {
	float f[9];
	struct {
		float m00, m01, m02;
		float m10, m11, m12;
		float m20, m21, m22;
	};
};
typedef union _mat3_t mat3_t;

union _mat4_t {
	float f[16];
	struct {
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;
	};
};
typedef union _mat4_t mat4_t;

// Quaternions
union _quat_t {
	float f[4];
	struct { float x; float y; float z; float w; };
};
typedef union _quat_t quat_t;

// Rectangles (Origin: bottom left)
union _rect_t {
	float f[4];
	struct { vec2_t o; vec2_t s; };
	struct { vec2_t origin; vec2_t size; };
};
typedef union _rect_t rect_t;

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
