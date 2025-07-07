#include "lighting_test.hpp"
#include "../math/math.h"
#include "../memory.hpp"

namespace LightingTest {
    
    LightingTestState* GetState(ZaynMemory* zaynMem) {
        // Store state in permanent memory arena
        static LightingTestState* state = nullptr;
        if (!state) {
            state = (LightingTestState*)AllocateMem(&zaynMem->permanentMemArena, sizeof(LightingTestState));
            *state = {}; // Initialize to zero
        }
        return state;
    }
    
    void Initialize(ZaynMemory* zaynMem) {
        printf("Initializing Lighting Test Mode\n");
        
        LightingTestState* state = GetState(zaynMem);
        state->time = 0.0f;
        state->initialized = true;
        
        // Initialize camera for lighting tests
        zaynMem->camera.position = {0.0f, 2.0f, 5.0f};
        zaynMem->camera.forward = {0.0f, 0.0f, -1.0f};
        zaynMem->camera.up = {0.0f, 1.0f, 0.0f};
    }
    
    void Update(ZaynMemory* zaynMem, float deltaTime) {
        LightingTestState* state = GetState(zaynMem);
        if (!state->initialized) return;
        
        state->time += deltaTime;
        
        // Update camera movement based on input
        CameraUpdateMovement(&zaynMem->camera, zaynMem, deltaTime);
        CameraUpdateTest(&zaynMem->camera);
    }
    
    void GetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount) {
        LightingTestState* state = GetState(zaynMem);
        if (!state->initialized) {
            instanceCount = 0;
            return;
        }
        
        instanceCount = 0;
        
        // Create a simple test scene with a few objects for lighting experiments
        if (instanceCount < maxInstances) {
            // Central cube
            instances[instanceCount].transform = Identity4();
            instances[instanceCount].transform.m30 = 0.0f;  // x position
            instances[instanceCount].transform.m31 = 0.0f;  // y position  
            instances[instanceCount].transform.m32 = -3.0f; // z position
            
            instances[instanceCount].normalTransform = Identity3();
            instances[instanceCount].color = V4(1.0f, 0.5f, 0.2f, 1.0f); // Orange
            instanceCount++;
        }
        
        // Left cube
        if (instanceCount < maxInstances) {
            instances[instanceCount].transform = Identity4();
            instances[instanceCount].transform.m30 = -2.0f; // x position
            instances[instanceCount].transform.m31 = 0.0f;  // y position
            instances[instanceCount].transform.m32 = -3.0f; // z position
            
            instances[instanceCount].normalTransform = Identity3();
            instances[instanceCount].color = V4(0.2f, 1.0f, 0.2f, 1.0f); // Green
            instanceCount++;
        }
        
        // Right cube
        if (instanceCount < maxInstances) {
            instances[instanceCount].transform = Identity4();
            instances[instanceCount].transform.m30 = 2.0f;  // x position
            instances[instanceCount].transform.m31 = 0.0f;  // y position
            instances[instanceCount].transform.m32 = -3.0f; // z position
            
            instances[instanceCount].normalTransform = Identity3();
            instances[instanceCount].color = V4(0.2f, 0.2f, 1.0f, 1.0f); // Blue
            instanceCount++;
        }
        
        printf("Lighting Test: Generated %d instances\n", instanceCount);
    }
    
    void Shutdown(ZaynMemory* zaynMem) {
        printf("Shutting down Lighting Test Mode\n");
        // State is in permanent arena, no explicit cleanup needed
    }
    
} // namespace LightingTest