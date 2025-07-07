#pragma once

#include "../zayn.hpp"
#include "../data_types.h"

// Standard interface that all game projects must implement
// Each game project should provide these functions with their own implementations

// Game project function signatures
extern "C" {
    // Core game project functions
    void GameInit(ZaynMemory* zaynMem);
    void GameUpdate(ZaynMemory* zaynMem, float deltaTime);
    void GameGetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount);
    void GameShutdown(ZaynMemory* zaynMem);
    
    // Optional game project functions
    void GameHandleInput(ZaynMemory* zaynMem);
    void GameRender(ZaynMemory* zaynMem);
    void GamePause(ZaynMemory* zaynMem);
    void GameResume(ZaynMemory* zaynMem);
}

// Game project state management helpers
struct GameProjectState {
    bool initialized;
    bool paused;
    float totalTime;
    void* gameSpecificData;  // Pointer to game-specific state structure
};

// Helper macros for game project state management
#define GAME_PROJECT_STATE(zaynMem) ((GameProjectState*)((zaynMem)->gameProjectState))
#define GAME_SPECIFIC_DATA(zaynMem, type) ((type*)GAME_PROJECT_STATE(zaynMem)->gameSpecificData)