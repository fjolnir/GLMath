//
//  GLMathTests.h
//  GLMathTests
//
//  Created by Fjölnir Ásgeirsson on 6/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <SenTestingKit/SenTestingKit.h>
#import "GLMath.h"

@interface GLMathTests : SenTestCase {
@private
  vec2_t v2;
  vec3_t v3;
  vec4_t v4;
  
  mat4_t m4;

  quat_t q;
}

@end
