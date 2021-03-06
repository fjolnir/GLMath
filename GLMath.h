// GLMath
//
// A Math utility library intended for use with computer graphics
// Uses vDSP to perform most operations

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

#ifndef GL_MATH_H
#define GL_MATH_H

#ifdef __APPLE__
#define GLM_USE_ACCELERATE_FRAMEWORK
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <GLMath/GLMathTypes.h>
#include <GLMath/GLMathVector.h>
#include <GLMath/GLMathMatrix.h>
#include <GLMath/GLMathQuaternion.h>
#include <GLMath/GLMathBezierCurve.h>
#include <GLMath/GLMathMatrixStack.h>
#include <GLMath/GLMathUtilities.h>

#ifdef __cplusplus
}
#endif
#endif
