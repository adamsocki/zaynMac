#pragma once

#include "../zayn.hpp"
#include "../data_types.h"

// Cube Demo Game Mode
// Original rotating cube grid with textures for testing

namespace CubeDemo {
    
    struct CubeDemoState {
        float angle;
        bool initialized;
    };
    
    // Game mode interface
    void Initialize(ZaynMemory* zaynMem);
    void Update(ZaynMemory* zaynMem, float deltaTime);
    void GetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount);
    void Shutdown(ZaynMemory* zaynMem);
    
    // Internal functions
    CubeDemoState* GetState(ZaynMemory* zaynMem);
}