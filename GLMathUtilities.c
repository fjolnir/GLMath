#include "GLMathUtilities.h"
#include "GLMathVector.h"

// Generates a perspective viewing matrix
mat4_t mat4_perspective(float fovy, float aspect, float zNear, float zFar)
{
	mat4_t out;
	float cotan = 1.0f / tanf(fovy/2.0f);
	
	return (mat4_t){ cotan/aspect, 0.0f,  0.0f,                               0.0f,
		0.0f,         cotan, 0.0f,                               0.0f,
		0.0f,         0.0f,  (zFar+zNear) / (zNear-zFar),       -1.0f,
		0.0f,         0.0f,  2.0f * zFar * zNear / (zNear-zFar), 0.0f };
	
	return out;
}

// Generates lookat viewing matrix
mat4_t mat4_lookat(float eyeX, float eyeY, float eyeZ,
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

// Generates an orthogonal viewing matrix
mat4_t mat4_ortho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
	float ral = right + left;
	float rsl = right - left;
	float tsb = top - bottom;
	float tab = top + bottom;
	float fan = farZ + nearZ;
	float fsn = farZ - nearZ;
	
	return (mat4_t) { 2.0f / rsl, 0.0f,       0.0f,        0.0f,
		0.0f,        2.0f / tsb, 0.0f,        0.0f,
		0.0f,        0.0f,       -2.0f / fsn, 0.0f,
		-ral / rsl,  -tab / tsb, -fan / fsn,  1.0f };
}


void printVec2(vec2_t vec) {
	printf("Vec2: [%.2f, %.2f]\n", vec.f[0], vec.f[1]);
}
void printVec3(vec3_t vec) {
	printf("Vec3: [%.2f, %.2f, %.2f]\n", vec.f[0], vec.f[1], vec.f[2]);
}
void printVec4(vec4_t vec) {
	printf("Vec4: [%.2f, %.2f, %.2f, %.2f]\n", vec.f[0], vec.f[1], vec.f[2], vec.f[3]);
}
void printMat3(mat3_t mat) {
	printf("Mat3: [%.2f, %.2f, %.2f]\n", mat.m00, mat.m01, mat.m02);
	printf("      [%.2f, %.2f, %.2f]\n", mat.m10, mat.m11, mat.m12);
	printf("      [%.2f, %.2f, %.2f]\n", mat.m20, mat.m21, mat.m22);
}
void printMat4(mat4_t mat) {
	printf("Mat4: [%.2f, %.2f, %.2f, %.2f]\n", mat.m00, mat.m01, mat.m02, mat.m03);
	printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat.m10, mat.m11, mat.m12, mat.m13);
	printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat.m20, mat.m21, mat.m22, mat.m23);
	printf("      [%.2f, %.2f, %.2f, %.2f]\n", mat.m30, mat.m31, mat.m32, mat.m33);
}
void printQuat(quat_t quat) {
	printf("Quat: [%.2f, %.2f, %.2f, %.2f]\n", quat.f[0], quat.f[1], quat.f[2], quat.f[3]);
}
