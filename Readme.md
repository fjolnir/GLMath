GLMath - A math toolkit for OpenGL

This is a basic math toolkit which includes support for vectors(2,3&4 element) 4x4 matrices & quaternions as well as affine transforms and a matrix stack intended to ease the transition for OpenGL ES 2.

Most calculations are performed by vDSP(Accelerate.framework) and the functions are mostly inlined so performance should be decent although I have not performed extensive benchmarks.
This is still very much a work in progress so please do let me know if you come across any particularly embarrassing oversights.

Designed for OS X & iOS (where it uses vectorized functions to perform it's calculations), but does provide portable fallbacks.
