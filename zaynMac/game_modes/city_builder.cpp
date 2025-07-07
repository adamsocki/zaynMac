#include "city_builder.hpp"
#include "../zayn.hpp"
#include "../grid.hpp"
#include "../scene.hpp"

namespace CityBuilder {
    
    void Initialize(ZaynMemory* zaynMem) {
        printf("Initializing City Builder Mode\n");
        
        // Initialize city grid (20x20 tiles, 2 units per tile)
        zaynMem->cityGrid = (GridSystem*)AllocateMem(&zaynMem->permanentMemArena, sizeof(GridSystem));
        new (zaynMem->cityGrid) GridSystem();
        InitializeGrid(zaynMem->cityGrid, &zaynMem->permanentMemArena, 20, 20, 2.0f);
        
        // Initialize scene
        zaynMem->currentScene = (Scene*)AllocateMem(&zaynMem->permanentMemArena, sizeof(Scene));
        new (zaynMem->currentScene) Scene(&zaynMem->permanentMemArena);
        
        // Initialize camera for city builder
        zaynMem->camera.position = {0.0f, 10.0f, 10.0f};
        zaynMem->camera.forward = {0.0f, -0.5f, -1.0f};
        zaynMem->camera.up = {0.0f, 1.0f, 0.0f};
    }
    
    void Update(ZaynMemory* zaynMem, float deltaTime) {
        if (!zaynMem || !zaynMem->cityGrid || !zaynMem->currentScene) return;
        
        // Update camera movement based on input
        CameraUpdateMovement(&zaynMem->camera, zaynMem, deltaTime);
        CameraUpdateTest(&zaynMem->camera);
        
        // Update city builder game logic
        UpdateCityBuilder(zaynMem, deltaTime);
        
        // Update scene from grid state
        UpdateSceneFromGrid(zaynMem);
    }
    
    void GetInstanceData(ZaynMemory* zaynMem, InstanceData* instances, int maxInstances, int& instanceCount) {
        if (!zaynMem || !zaynMem->currentScene) {
            instanceCount = 0;
            return;
        }
        
        // Get instance data from scene
        zaynMem->currentScene->GetInstanceData(instances, maxInstances, instanceCount);
        printf("City Builder: Scene provided %d instances\n", instanceCount);
    }
    
    void Shutdown(ZaynMemory* zaynMem) {
        printf("Shutting down City Builder Mode\n");
        // Grid and scene are in permanent arena, no explicit cleanup needed
    }
    
} // namespace CityBuilder
