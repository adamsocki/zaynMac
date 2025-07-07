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
    
    // Camera movement
    simd::float3 position;
    simd::float3 forward;
    simd::float3 right;
    simd::float3 up;
    
    float moveSpeed;
    
    // Initialize with default values positioned for city builder (top-down angled view)
    inline Camera() : 
        dif(0.0f),
        position(simd::make_float3(0.0f, 25.0f, 15.0f)),
        forward(simd::make_float3(0.0f, -0.6f, -0.8f)),
        right(simd::make_float3(1.0f, 0.0f, 0.0f)),
        up(simd::make_float3(0.0f, 1.0f, 0.0f)),
        moveSpeed(15.0f) {}
};

void CameraUpdateTest(Camera* cam);
void CameraUpdateMovement(Camera* cam, struct ZaynMemory* zaynMem, float deltaTime);

// Screen-to-world conversion for mouse interaction
simd::float3 ScreenToWorldPosition(struct ZaynMemory* zaynMem, float screenX, float screenY, float screenWidth, float screenHeight);

#endif /* camera_hpp */
