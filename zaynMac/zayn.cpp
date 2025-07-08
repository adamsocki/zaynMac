//
//  zayn.cpp
//  zaynMac
//
//  Created by socki on 11/18/24.
//

#include "zayn.hpp"
#include "constants.h"
#include <iostream>

#include "casette/casette_system.h"

// External game mode functions
extern "C" void InitializeGame(ZaynMemory* zaynMem);

void ZaynInit(ZaynMemory* zaynMem)
{

    // Initialize core engine systems
    AllocateMemoryArena(&zaynMem->permanentMemArena, Megabytes(256));
    AllocateMemoryArena(&zaynMem->frameMemArena, Megabytes(32));
    
    AllocateInputManager(&zaynMem->inputManager, &zaynMem->permanentMemArena, 4);
    
    // Initialize keyboard device
    zaynMem->keyboard = &zaynMem->inputManager.devices[0];
    zaynMem->inputManager.keyboard = zaynMem->keyboard;
    AllocateInputDevice(zaynMem->keyboard, InputDeviceType_Keyboard, Input_KeyboardDiscreteCount, 0);
    
    // Initialize mouse device
    zaynMem->inputManager.mouse = &zaynMem->inputManager.devices[1];
    AllocateInputDevice(zaynMem->inputManager.mouse, InputDeviceType_Mouse, MouseButton_Count, 2); // 2 analog for x,y
    
    // Initialize game mode-specific systems
    zaynMem->instanceCount = 0;
    zaynMem->instanceData = (InstanceData*)PushSizeMemoryArena(&zaynMem->permanentMemArena, kNumInstances * sizeof(InstanceData));
    for (int i = 0; i < kNumInstances; i++) {
        zaynMem->instanceData[i] = {}; // Zero-initialize each InstanceData
    }

    InitializeGame(zaynMem);
    
    // Initialize casette system
    InitCasette();
}

void ZaynUpdate(ZaynMemory* zaynMem)
{
    // Core engine update logic
}

void ZaynUpdateAndRender(ZaynMemory* zaynMem)
{
    // Update frame timing
    zaynMem->accumTime += zaynMem->deltaTime;
    zaynMem->accumFrames++;
    
    if (zaynMem->accumTime >= 1.0f)
    {
        float avgDt = zaynMem->accumTime / zaynMem->accumFrames;
        
        // Update window title with FPS
        // TODO: Implement window title update for macOS
        
        zaynMem->accumTime -= 1.0f;
        zaynMem->accumFrames = 0;
    }
    
    // Update and render casette
    UpdateAndRenderCasette();
}

