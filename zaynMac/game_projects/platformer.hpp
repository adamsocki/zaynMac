#pragma once

#include "game_project_interface.hpp"
#include "../math/math.h"

// Platformer Game Project
// Simple 2D platformer with player movement and basic physics

struct PlatformerState {
    // Player state
    simd::float3 playerPosition;
    simd::float3 playerVelocity;
    bool isGrounded;
    bool isJumping;
    
    // Game state
    float jumpForce;
    float gravity;
    float moveSpeed;
    int score;
    float levelWidth;
    float levelHeight;
    
    // Platform data
    int platformCount;
    simd::float3 platforms[64];  // Simple platform positions
    
    // Timing
    float gameTime;
    
    // Flags
    bool initialized;
};

// Platformer-specific functions
namespace Platformer {
    void Initialize(ZaynMemory* zaynMem);
    void Update(ZaynMemory* zaynMem, float deltaTime);
    void GetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount);
    void Shutdown(ZaynMemory* zaynMem);
    
    
    // Internal functions
    PlatformerState* GetState(ZaynMemory* zaynMem);
    void UpdatePlayer(PlatformerState* state, ZaynMemory* zaynMem, float deltaTime);
    void UpdatePhysics(PlatformerState* state, float deltaTime);
    void CheckCollisions(PlatformerState* state);
    void GeneratePlatforms(PlatformerState* state);
}

// Game project implementation (automatically included when this project is active)
// Note: Implementation moved to platformer_impl.hpp to avoid separate compilation
