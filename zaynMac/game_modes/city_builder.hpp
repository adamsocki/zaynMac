#pragma once

#include "../zayn.hpp"
#include "../data_types.h"

// City Builder Game Mode
// Grid-based city building with scene system

namespace CityBuilder {
    
    // Game mode interface
    void Initialize(ZaynMemory* zaynMem);
    void Update(ZaynMemory* zaynMem, float deltaTime);
    void GetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount);
    void Shutdown(ZaynMemory* zaynMem);
    
}