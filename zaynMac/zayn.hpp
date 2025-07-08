//
//  zayn.hpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#pragma once
#import "camera.hpp"
#import "memory.hpp"
#import "input.hpp"
#import "time.hpp"
#import "scene.hpp"
#import "grid.hpp"

#include "entity.hpp"
#include "constants.h"

struct ZaynMemory
{
    CameraData* cameraData;
    
    Camera camera;
    
    MemoryArena permanentMemArena;
    MemoryArena frameMemArena;
    
    InputManager inputManager;
    InputDevice* keyboard;

    ZaynTime time;
    float deltaTime;
    float accumTime;
    int accumFrames;
    
    Scene* currentScene;
    GridSystem* cityGrid;
    
    // Game project state
    void* gameProjectState;  // Pointer to game-specific state structure
    
    int instanceCount;
    InstanceData* instanceData;
};

void ZaynInit(ZaynMemory* zaynMem);
void ZaynUpdate(ZaynMemory* zaynMem);
void ZaynUpdateAndRender(ZaynMemory* zaynMem);
