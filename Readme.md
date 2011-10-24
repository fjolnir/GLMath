# GLMath - A math toolkit for OpenGL

This is a basic math toolkit which includes support for vectors(2,3&4 element), matrices(3x3&4x4) & quaternions as well as affine transforms and a matrix stack.

Most calculations are performed by vDSP(Accelerate.framework) so performance should be decent although I have not performed extensive benchmarks.
This is still very much a work in progress so please do let me know if you come across any particularly embarrassing oversights.

Designed for OS X & iOS, but does provide portable fallbacks.
