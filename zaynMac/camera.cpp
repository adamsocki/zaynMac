//
//  camera.cpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#include "camera.hpp"
#include "zayn.hpp"
#include "math/math.h"

void CameraUpdateTest(Camera* cam)
{
    cam->dif += 0.01f;
}

void CameraUpdateMovement(Camera* cam, ZaynMemory* zaynMem, float deltaTime)
{
    if (!zaynMem || !zaynMem->keyboard) return;
    
    InputDevice* keyboard = zaynMem->keyboard;
    float speed = cam->moveSpeed * deltaTime;
    
    simd::float3 movement = simd::make_float3(0.0f, 0.0f, 0.0f);
    
    // WASD movement
    if (InputHeld(keyboard, Input_W)) {
        movement += cam->forward * speed;
    }
    if (InputHeld(keyboard, Input_S)) {
        movement -= cam->forward * speed;
    }
    if (InputHeld(keyboard, Input_A)) {
        movement -= cam->right * speed;
    }
    if (InputHeld(keyboard, Input_D)) {
        movement += cam->right * speed;
    }
    
    // QE for up/down movement
    if (InputHeld(keyboard, Input_Q)) {
        movement -= cam->up * speed;
    }
    if (InputHeld(keyboard, Input_E)) {
        movement += cam->up * speed;
    }
    
    // Update camera position
    cam->position += movement;
}

simd::float3 ScreenToWorldPosition(ZaynMemory* zaynMem, float screenX, float screenY, float screenWidth, float screenHeight)
{
    if (!zaynMem || !zaynMem->cameraData) {
        return simd::make_float3(0.0f, 0.0f, 0.0f);
    }
    
    // Convert screen coordinates to normalized device coordinates (-1 to 1)
    float ndcX = (2.0f * screenX) / screenWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * screenY) / screenHeight; // Flip Y (screen Y goes down, NDC Y goes up)
    
    // Create ray in clip space
    simd::float4 rayClip = simd::make_float4(ndcX, ndcY, -1.0f, 1.0f);
    
    // Transform to view space
    simd::float4x4 invProjection = simd::inverse(zaynMem->cameraData->perspectiveTransform);
    simd::float4 rayView = invProjection * rayClip;
    rayView = simd::make_float4(rayView.x, rayView.y, -1.0f, 0.0f); // Set to direction
    
    // Transform to world space
    simd::float4x4 invView = simd::inverse(zaynMem->cameraData->worldTransform);
    simd::float4 rayWorld4 = invView * rayView;
    simd::float3 rayWorld = simd::normalize(simd::make_float3(rayWorld4.x, rayWorld4.y, rayWorld4.z));
    
    // Cast ray to ground plane (y = 0)
    simd::float3 rayOrigin = zaynMem->camera.position;
    
    // Calculate intersection with ground plane (y = 0)
    if (rayWorld.y != 0.0f) {
        float t = -rayOrigin.y / rayWorld.y;
        if (t > 0.0f) {
            return rayOrigin + rayWorld * t;
        }
    }
    
    // Fallback: project forward from camera
    return rayOrigin + zaynMem->camera.forward * 10.0f;
}
