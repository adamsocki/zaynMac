#include "cube_demo.hpp"
#include "../math/math.h"
#include "../memory.hpp"

using simd::float3;
using simd::float4;
using simd::float4x4;

namespace CubeDemo {
    
    static constexpr size_t kInstanceRows = 10;
    static constexpr size_t kInstanceColumns = 10;
    static constexpr size_t kInstanceDepth = 10;
    static constexpr size_t kNumInstances = (kInstanceRows * kInstanceColumns * kInstanceDepth);
    
    CubeDemoState* GetState(ZaynMemory* zaynMem) {
        // Store state in permanent memory arena
        static CubeDemoState* state = nullptr;
        if (!state) {
            state = (CubeDemoState*)AllocateMem(&zaynMem->permanentMemArena, sizeof(CubeDemoState));
            *state = {}; // Initialize to zero
        }
        return state;
    }
    
    void Initialize(ZaynMemory* zaynMem) {
        printf("Initializing Cube Demo Mode\n");
        
        CubeDemoState* state = GetState(zaynMem);
        state->angle = 0.0f;
        state->initialized = true;
        
        // Initialize camera for cube demo
        zaynMem->camera.position = {0.0f, 5.0f, 15.0f};
        zaynMem->camera.forward = {0.0f, 0.0f, -1.0f};
        zaynMem->camera.up = {0.0f, 1.0f, 0.0f};
    }
    
    void Update(ZaynMemory* zaynMem, float deltaTime) {
        CubeDemoState* state = GetState(zaynMem);
        if (!state->initialized) return;
        
        // Update rotation angle
        state->angle += deltaTime * 0.5f; // Slower rotation
        
        // Update camera movement based on input
        CameraUpdateMovement(&zaynMem->camera, zaynMem, deltaTime);
        CameraUpdateTest(&zaynMem->camera);
    }
    
    void GetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount) {
        CubeDemoState* state = GetState(zaynMem);
        if (!state->initialized) {
            instanceCount = 0;
            return;
        }
        
        instanceCount = 0;
        
        const float scl = 0.2f;
        const float scl2 = 0.9f;
        float3 objectPosition = { 0.f, 0.f, -10.f };

        float4x4 rt = math::makeTranslate( objectPosition );
        float4x4 rr1 = math::makeYRotate( -state->angle );
        float4x4 rr0 = math::makeXRotate( state->angle * 0.5 );
        float4x4 rtInv = math::makeTranslate( { -objectPosition.x, -objectPosition.y, -objectPosition.z } );
        float4x4 fullObjectRot = rt * rr1 * rr0 * rtInv;

        size_t ix = 0;
        size_t iy = 0;
        size_t iz = 0;
        
        for ( size_t i = 0; i < kNumInstances && instanceCount < maxInstances; ++i )
        {
            if ( ix == kInstanceRows )
            {
                ix = 0;
                iy += 1;
            }
            if ( iy == kInstanceRows )
            {
                iy = 0;
                iz += 1;
            }

            float4x4 scale = math::makeScale( (float3){ scl, scl, scl } );
            float4x4 zrot = math::makeZRotate( state->angle * sinf((float)ix) );
            float4x4 yrot = math::makeYRotate( state->angle * cosf((float)iy));

            float x = ((float)ix - (float)kInstanceRows/2.f) * (2.f * scl) + scl;
            float y = ((float)iy - (float)kInstanceColumns/2.f) * (2.f * scl) + scl2;
            float z = ((float)iz - (float)kInstanceDepth/2.f) * (2.f * scl2);
            float4x4 translate = math::makeTranslate( math::add( objectPosition, { x, y, z } ) );

            // Convert to InstanceData format
            simd::float4x4 transformSIMD = fullObjectRot * translate * yrot * zrot * scale;
            
            // Convert simd::float4x4 to mat4
            mat4 transform;
            // Copy column-major data
            transform.m00 = transformSIMD.columns[0][0]; transform.m01 = transformSIMD.columns[1][0]; transform.m02 = transformSIMD.columns[2][0]; transform.m03 = transformSIMD.columns[3][0];
            transform.m10 = transformSIMD.columns[0][1]; transform.m11 = transformSIMD.columns[1][1]; transform.m12 = transformSIMD.columns[2][1]; transform.m13 = transformSIMD.columns[3][1];
            transform.m20 = transformSIMD.columns[0][2]; transform.m21 = transformSIMD.columns[1][2]; transform.m22 = transformSIMD.columns[2][2]; transform.m23 = transformSIMD.columns[3][2];
            transform.m30 = transformSIMD.columns[0][3]; transform.m31 = transformSIMD.columns[1][3]; transform.m32 = transformSIMD.columns[2][3]; transform.m33 = transformSIMD.columns[3][3];
            
            // Copy transform matrix (column-major)
            instances[instanceCount].transform.m00 = transform.m00;
            instances[instanceCount].transform.m01 = transform.m01;
            instances[instanceCount].transform.m02 = transform.m02;
            instances[instanceCount].transform.m03 = transform.m03;
            instances[instanceCount].transform.m10 = transform.m10;
            instances[instanceCount].transform.m11 = transform.m11;
            instances[instanceCount].transform.m12 = transform.m12;
            instances[instanceCount].transform.m13 = transform.m13;
            instances[instanceCount].transform.m20 = transform.m20;
            instances[instanceCount].transform.m21 = transform.m21;
            instances[instanceCount].transform.m22 = transform.m22;
            instances[instanceCount].transform.m23 = transform.m23;
            instances[instanceCount].transform.m30 = transform.m30;
            instances[instanceCount].transform.m31 = transform.m31;
            instances[instanceCount].transform.m32 = transform.m32;
            instances[instanceCount].transform.m33 = transform.m33;
            
            // Normal transform (3x3 part of transform)
            simd::float3x3 normalTransformSIMD = math::discardTranslation( transformSIMD );
            
            // Convert simd::float3x3 to mat3
            mat3 normalTransform;
            normalTransform.m00 = normalTransformSIMD.columns[0][0]; normalTransform.m01 = normalTransformSIMD.columns[1][0]; normalTransform.m02 = normalTransformSIMD.columns[2][0];
            normalTransform.m10 = normalTransformSIMD.columns[0][1]; normalTransform.m11 = normalTransformSIMD.columns[1][1]; normalTransform.m12 = normalTransformSIMD.columns[2][1];
            normalTransform.m20 = normalTransformSIMD.columns[0][2]; normalTransform.m21 = normalTransformSIMD.columns[1][2]; normalTransform.m22 = normalTransformSIMD.columns[2][2];
            instances[instanceCount].normalTransform.m00 = normalTransform.m00;
            instances[instanceCount].normalTransform.m01 = normalTransform.m01;
            instances[instanceCount].normalTransform.m02 = normalTransform.m02;
            instances[instanceCount].normalTransform.m10 = normalTransform.m10;
            instances[instanceCount].normalTransform.m11 = normalTransform.m11;
            instances[instanceCount].normalTransform.m12 = normalTransform.m12;
            instances[instanceCount].normalTransform.m20 = normalTransform.m20;
            instances[instanceCount].normalTransform.m21 = normalTransform.m21;
            instances[instanceCount].normalTransform.m22 = normalTransform.m22;

            // Color
            float iDivNumInstances = i / (float)kNumInstances;
            float r = iDivNumInstances;
            float g = 1.0f - r;
            float b = sinf( M_PI * 2.0f * iDivNumInstances );
            instances[instanceCount].color = V4(r, g, b, 1.0f);

            instanceCount++;
            ix += 1;
        }
        
        printf("Cube Demo: Generated %d instances\n", instanceCount);
    }
    
    void Shutdown(ZaynMemory* zaynMem) {
        printf("Shutting down Cube Demo Mode\n");
        // State is in permanent arena, no explicit cleanup needed
    }
    
} // namespace CubeDemo