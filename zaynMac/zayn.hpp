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


struct ZaynMemory
{
    CameraData* cameraData;
    
    Camera camera;
    
    MemoryArena permanentMemArena;
    MemoryArena frameMemArena;
    
    InputManager inputManager;
    InputDevice* keyboard;

    ZaynTime time;
    
    Scene* currentScene;
    GridSystem* cityGrid;
};

void ZaynInit(ZaynMemory* zaynMem);

// City builder functions
void UpdateCityBuilder(ZaynMemory* zaynMem, float deltaTime);
void UpdateSceneFromGrid(ZaynMemory* zaynMem);
