#pragma once

#include "../zayn.hpp"
#include "../data_types.h"

// Lighting Test Game Mode
// Simple scene for lighting experiments

namespace LightingTest {
    
    struct LightingTestState {
        float time;
        bool initialized;
    };
    
    // Game mode interface
    void Initialize(ZaynMemory* zaynMem);
    void Update(ZaynMemory* zaynMem, float deltaTime);
    void GetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount);
    void Shutdown(ZaynMemory* zaynMem);
    
    // Internal functions
    LightingTestState* GetState(ZaynMemory* zaynMem);
}