//
//  camera.hpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#ifndef camera_hpp
#define camera_hpp

#include <Metal/Metal.hpp>
//#include <stdio.h>
//#include "math/math.h"
#include <simd/simd.h>

struct CameraData
{
    simd::float4x4 perspectiveTransform;
    simd::float4x4 worldTransform;
    simd::float3x3 worldNormalTransform;
};

struct Camera
{
    float dif;
};

void CameraUpdateTest(Camera* cam);

#endif /* camera_hpp */
