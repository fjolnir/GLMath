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

// Exports inlined functions for use with ffi

#include <GLMath/GLMath.h>

#if !defined(GLMath_GLMathExports_h)
#define GLMath_GLMathExports_h

#define EXPOSE(fun) __typeof__(fun) *_##fun = fun

EXPOSE(vec2_create);
EXPOSE(vec2_add);
EXPOSE(vec2_sub);
EXPOSE(vec2_mul);
EXPOSE(vec2_div);
EXPOSE(vec2_dot);
EXPOSE(vec2_magSquared);
EXPOSE(vec2_mag);
EXPOSE(vec2_normalize);
EXPOSE(vec2_dist);
EXPOSE(vec2_scalarMul);
EXPOSE(vec2_scalarDiv);
EXPOSE(vec2_scalarAdd);
EXPOSE(vec2_scalarSub);
EXPOSE(vec2_negate);
EXPOSE(vec2_floor);
EXPOSE(vec3_create);
EXPOSE(vec3_add);
EXPOSE(vec3_sub);
EXPOSE(vec3_mul);
EXPOSE(vec3_div);
EXPOSE(vec3_dot);
EXPOSE(vec3_magSquared);
EXPOSE(vec3_mag);
EXPOSE(vec3_normalize);
EXPOSE(vec3_dist);
EXPOSE(vec3_scalarMul);
EXPOSE(vec3_scalarDiv);
EXPOSE(vec3_scalarAdd);
EXPOSE(vec3_scalarSub);
EXPOSE(vec3_cross);
EXPOSE(vec3_negate);
EXPOSE(vec3_floor);
EXPOSE(vec4_create);
EXPOSE(vec4_add);
EXPOSE(vec4_sub);
EXPOSE(vec4_mul);
EXPOSE(vec4_div);
EXPOSE(vec4_dot);
EXPOSE(vec4_magSquared);
EXPOSE(vec4_mag);
EXPOSE(vec4_normalize);
EXPOSE(vec4_dist);
EXPOSE(vec4_scalarMul);
EXPOSE(vec4_scalarDiv);
EXPOSE(vec4_scalarAdd);
EXPOSE(vec4_scalarSub);
EXPOSE(vec4_cross);
EXPOSE(vec4_negate);
EXPOSE(vec4_floor);
EXPOSE(vec4_premultiplyAlpha);
EXPOSE(mat3_mul);
EXPOSE(vec3_mul_mat3);
EXPOSE(mat3_inverse);
EXPOSE(mat3_transpose);
EXPOSE(mat3_det);
EXPOSE(mat4_mul);
EXPOSE(vec3_mul_mat4);
EXPOSE(vec4_mul_mat4);
EXPOSE(mat4_inverse);
EXPOSE(mat4_transpose);
EXPOSE(mat4_extract_mat3);
EXPOSE(mat4_det);
EXPOSE(mat4_perspective);
EXPOSE(mat4_ortho);
EXPOSE(mat4_lookat);
EXPOSE(mat4_frustum);
EXPOSE(quat_createf);
EXPOSE(quat_createv);
EXPOSE(quat_to_mat4);
EXPOSE(mat4_to_quat);
EXPOSE(quat_to_ortho);
EXPOSE(ortho_to_quat);
EXPOSE(quat_magSquared);
EXPOSE(quat_mag);
EXPOSE(quat_computeW);
EXPOSE(quat_normalize);
EXPOSE(quat_multQuat);
EXPOSE(quat_rotatePoint);
EXPOSE(quat_rotateVec3);
EXPOSE(quat_inverse);
EXPOSE(quat_dotProduct);
EXPOSE(quat_slerp);
EXPOSE(bezier_create);
EXPOSE(bezier_getPoint);
EXPOSE(bezier_getCoordForAxis);
EXPOSE(bezier_firstDerivative);
EXPOSE(bezier_firstDerivativeRoots);
EXPOSE(bezier_extremes);
EXPOSE(bezier_getPointWithOffset);
EXPOSE(bezier_getLineSegments);
EXPOSE(bezier_getPointUsingLineSegments);
EXPOSE(mat4_create_translation);
EXPOSE(mat4_translate);
EXPOSE(mat4_create_rotation);
EXPOSE(mat4_rotate);
EXPOSE(mat4_create_scale);
EXPOSE(mat4_scale);
EXPOSE(matrix_stack_create);
EXPOSE(matrix_stack_destroy);
EXPOSE(matrix_stack_push_item);
EXPOSE(matrix_stack_push);
EXPOSE(matrix_stack_pop);
EXPOSE(matrix_stack_get_mat4);
EXPOSE(matrix_stack_get_mat3);
EXPOSE(matrix_stack_translate);
EXPOSE(matrix_stack_rotate);
EXPOSE(matrix_stack_scale);
EXPOSE(vec2_equals);
EXPOSE(vec3_equals);
EXPOSE(vec4_equals);
EXPOSE(mat4_equals);
EXPOSE(quat_equals);
EXPOSE(printVec2);
EXPOSE(printVec3);
EXPOSE(printVec4);
EXPOSE(printQuat);
EXPOSE(printMat3);
EXPOSE(printMat4);

#endif
