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


struct ZaynMemory
{
    CameraData* cameraData;
    
    Camera camera;
    
    MemoryArena permanentMemArena;
    MemoryArena frameMemArena;
    
    InputManager inputManager;
    InputDevice* keyboard;

    ZaynTime time;
};

void ZaynInit(ZaynMemory* zaynMem);
