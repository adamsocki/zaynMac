#pragma once

#include "platformer.hpp"
#include "../input.hpp"
#include "../camera.hpp"
#include "../types.h"
#include <iostream>

// Utility functions for type conversion
mat4 ConvertToMat4(const simd::float4x4& m) {
    mat4 result;
    result.m00 = m.columns[0].x; result.m10 = m.columns[0].y; result.m20 = m.columns[0].z; result.m30 = m.columns[0].w;
    result.m01 = m.columns[1].x; result.m11 = m.columns[1].y; result.m21 = m.columns[1].z; result.m31 = m.columns[1].w;
    result.m02 = m.columns[2].x; result.m12 = m.columns[2].y; result.m22 = m.columns[2].z; result.m32 = m.columns[2].w;
    result.m03 = m.columns[3].x; result.m13 = m.columns[3].y; result.m23 = m.columns[3].z; result.m33 = m.columns[3].w;
    return result;
}

mat3 ConvertToMat3(const simd::float3x3& m) {
    mat3 result;
    result.m00 = m.columns[0].x; result.m10 = m.columns[0].y; result.m20 = m.columns[0].z;
    result.m01 = m.columns[1].x; result.m11 = m.columns[1].y; result.m21 = m.columns[1].z;
    result.m02 = m.columns[2].x; result.m12 = m.columns[2].y; result.m22 = m.columns[2].z;
    return result;
}

namespace Platformer {
    
    void Initialize(ZaynMemory* zaynMem) {
        std::cout << "Initializing Platformer Game Project" << std::endl;
        
        // Allocate game state
        PlatformerState* state = (PlatformerState*)AllocateMem(&zaynMem->permanentMemArena, sizeof(PlatformerState));
        zaynMem->gameProjectState = state;
        
        // Initialize player
        state->playerPosition = simd::make_float3(0.0f, 0.0f, 0.0f);
        state->playerVelocity = simd::make_float3(0.0f, 0.0f, 0.0f);
        state->isGrounded = false;
        state->isJumping = false;
        
        // Initialize game parameters
        state->jumpForce = 15.0f;
        state->gravity = -30.0f;
        state->moveSpeed = 10.0f;
        state->score = 0;
        state->levelWidth = 20.0f;
        state->levelHeight = 15.0f;
        
        // Initialize platforms
        GeneratePlatforms(state);
        
        // Initialize timing
        state->gameTime = 0.0f;
        state->initialized = true;
        
        // Set up camera
        zaynMem->camera.position = simd::make_float3(0.0f, 5.0f, 10.0f);
        zaynMem->camera.forward = simd::make_float3(0.0f, 0.0f, -1.0f);
        zaynMem->camera.up = simd::make_float3(0.0f, 1.0f, 0.0f);
    }
    
    void Update(ZaynMemory* zaynMem, float deltaTime) {
        PlatformerState* state = GetState(zaynMem);
        if (!state || !state->initialized) return;
        
        state->gameTime += deltaTime;
        
        // Update player
        UpdatePlayer(state, zaynMem, deltaTime);
        
        // Update physics
        UpdatePhysics(state, deltaTime);
        
        // Check collisions
        CheckCollisions(state);
        
        // Update camera to follow player
        simd::float3 targetPos = state->playerPosition;
        targetPos.z = 10.0f;
        zaynMem->camera.position = targetPos;
    }
    
    void GetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount) {
        PlatformerState* state = GetState(zaynMem);
        if (!state || !state->initialized) {
            instanceCount = 0;
            return;
        }
        
        instanceCount = 0;
        
        // Add player instance
        if (instanceCount < maxInstances) {
            simd::float4x4 playerTransform = math::makeTranslate(state->playerPosition);
            
            // Convert simd::float4x4 to mat4
            instances[instanceCount].transform = ConvertToMat4(playerTransform);
            instances[instanceCount].normalTransform = ConvertToMat3(math::discardTranslation(playerTransform));
            instances[instanceCount].color = V4(0.0f, 1.0f, 0.0f, 1.0f); // Green player
            instanceCount++;
        }
        
        // Add platform instances
        for (int i = 0; i < state->platformCount && instanceCount < maxInstances; i++) {
            simd::float4x4 platformTransform = math::makeTranslate(state->platforms[i]);
            simd::float4x4 scaleMatrix = math::makeScale(simd::make_float3(2.0f, 0.5f, 1.0f));
            platformTransform = simd_mul(platformTransform, scaleMatrix);
            
            instances[instanceCount].transform = ConvertToMat4(platformTransform);
            instances[instanceCount].normalTransform = ConvertToMat3(math::discardTranslation(platformTransform));
            instances[instanceCount].color = V4(0.5f, 0.3f, 0.1f, 1.0f); // Brown platforms
            instanceCount++;
        }
    }
    
    void Shutdown(ZaynMemory* zaynMem) {
        std::cout << "Shutting down Platformer Game Project" << std::endl;
        // Memory cleanup handled by arena system
    }
    
    PlatformerState* GetState(ZaynMemory* zaynMem) {
        return (PlatformerState*)zaynMem->gameProjectState;
    }
    
    void UpdatePlayer(PlatformerState* state, ZaynMemory* zaynMem, float deltaTime) {
        float moveInput = 0.0f;
        bool jumpInput = false;
        
        // Handle input
        if (InputHeld(zaynMem->keyboard, Input_A)) {
            moveInput -= 1.0f;
        }
        if (InputHeld(zaynMem->keyboard, Input_D)) {
            moveInput += 1.0f;
        }
        if (InputHeld(zaynMem->keyboard, Input_Space)) {
            jumpInput = true;
        }
        
        // Apply movement
        state->playerVelocity.x = moveInput * state->moveSpeed;
        
        // Apply jump
        if (jumpInput && state->isGrounded) {
            state->playerVelocity.y = state->jumpForce;
            state->isJumping = true;
            state->isGrounded = false;
        }
    }
    
    void UpdatePhysics(PlatformerState* state, float deltaTime) {
        // Apply gravity
        state->playerVelocity.y += state->gravity * deltaTime;
        
        // Update position
        state->playerPosition.x += state->playerVelocity.x * deltaTime;
        state->playerPosition.y += state->playerVelocity.y * deltaTime;
        
        // Ground check (simple)
        if (state->playerPosition.y <= 0.0f) {
            state->playerPosition.y = 0.0f;
            state->playerVelocity.y = 0.0f;
            state->isGrounded = true;
            state->isJumping = false;
        }
        
        // Keep player in bounds
        if (state->playerPosition.x < -state->levelWidth/2) {
            state->playerPosition.x = -state->levelWidth/2;
        }
        if (state->playerPosition.x > state->levelWidth/2) {
            state->playerPosition.x = state->levelWidth/2;
        }
    }
    
    void CheckCollisions(PlatformerState* state) {
        // Simple platform collision detection
        for (int i = 0; i < state->platformCount; i++) {
            simd::float3 platform = state->platforms[i];
            
            // Check if player is on platform
            if (state->playerPosition.x >= platform.x - 1.0f && 
                state->playerPosition.x <= platform.x + 1.0f &&
                state->playerPosition.y >= platform.y - 0.5f && 
                state->playerPosition.y <= platform.y + 0.5f &&
                state->playerVelocity.y <= 0.0f) {
                
                state->playerPosition.y = platform.y + 0.5f;
                state->playerVelocity.y = 0.0f;
                state->isGrounded = true;
                state->isJumping = false;
            }
        }
    }
    
    void GeneratePlatforms(PlatformerState* state) {
        state->platformCount = 8;
        
        // Create some basic platforms
        state->platforms[0] = simd::make_float3(-8.0f, 2.0f, 0.0f);
        state->platforms[1] = simd::make_float3(-4.0f, 4.0f, 0.0f);
        state->platforms[2] = simd::make_float3(0.0f, 6.0f, 0.0f);
        state->platforms[3] = simd::make_float3(4.0f, 4.0f, 0.0f);
        state->platforms[4] = simd::make_float3(8.0f, 2.0f, 0.0f);
        state->platforms[5] = simd::make_float3(-6.0f, 8.0f, 0.0f);
        state->platforms[6] = simd::make_float3(2.0f, 10.0f, 0.0f);
        state->platforms[7] = simd::make_float3(6.0f, 8.0f, 0.0f);
    }
}

// Game project implementation (automatically included when this project is active)
extern "C" {
    void GameInit(ZaynMemory* zaynMem) {
        Platformer::Initialize(zaynMem);
    }
    
    void GameUpdate(ZaynMemory* zaynMem, float deltaTime) {
        Platformer::Update(zaynMem, deltaTime);
    }
    
    void GameGetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount) {
        Platformer::GetInstanceData(zaynMem, instances, maxInstances, instanceCount);
    }
    
    void GameShutdown(ZaynMemory* zaynMem) {
        Platformer::Shutdown(zaynMem);
    }
}